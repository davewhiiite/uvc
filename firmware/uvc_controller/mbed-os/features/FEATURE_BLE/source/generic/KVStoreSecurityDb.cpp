/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if BLE_SECURITY_DATABASE_KVSTORE

#include "KVStoreSecurityDb.h"

namespace ble {
namespace generic {

#if BLE_SECURITY_DATABASE_MAX_ENTRIES > 9
#error "BLE_SECURITY_DATABASE_MAX_ENTRIES must be only one digit long"
#endif

#define ENTRY_INVALID (0xFF)

constexpr uint8_t KVStoreSecurityDb::KVSTORESECURITYDB_VERSION;
constexpr size_t KVStoreSecurityDb::DB_PREFIX_SIZE;
constexpr size_t KVStoreSecurityDb::DB_KEY_SIZE;
constexpr size_t KVStoreSecurityDb::DB_ENTRY_KEY_SIZE;
constexpr size_t KVStoreSecurityDb::DB_FULL_KEY_SIZE;
constexpr char KVStoreSecurityDb::DB_PREFIX[DB_PREFIX_SIZE+1];

constexpr char KVStoreSecurityDb::DB_ENTRIES[DB_KEY_SIZE];

constexpr char KVStoreSecurityDb::DB_ENTRY_PEER_IDENTITY[DB_ENTRY_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_ENTRY_LOCAL_KEYS[DB_ENTRY_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_ENTRY_PEER_KEYS[DB_ENTRY_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_ENTRY_PEER_SIGNING[DB_ENTRY_KEY_SIZE];

constexpr char KVStoreSecurityDb::DB_LOCAL_IDENTITY[DB_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_LOCAL_CSRK[DB_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_LOCAL_SIGN_COUNT[DB_KEY_SIZE];

constexpr char KVStoreSecurityDb::DB_VERSION[DB_KEY_SIZE];
constexpr char KVStoreSecurityDb::DB_RESTORE[DB_KEY_SIZE];

typedef SecurityDb::entry_handle_t entry_handle_t;

KVStoreSecurityDb::KVStoreSecurityDb()
    : SecurityDb() {
    memset(_entries, 0, sizeof(_entries));
    for (size_t i = 0; i < get_entry_count(); i++) {
        _entries[i].index = ENTRY_INVALID;
    }
}

KVStoreSecurityDb::~KVStoreSecurityDb() {
}

bool KVStoreSecurityDb::open_db() {
    uint8_t version = 0;
    char db_key[DB_FULL_KEY_SIZE];
    create_key(db_key, DB_VERSION);
    size_t size;
    int ret = kv_get(db_key, &version, sizeof(uint8_t), &size);

    /* kvstore problem (check if it's been successfully initialised before this call) */
    if (ret != MBED_ERROR_ITEM_NOT_FOUND && (ret != MBED_SUCCESS || size != sizeof(uint8_t))) {
        return false;
    }

    /* wipe the db if it's the wrong version or it doesn't exist */
    if (version != KVSTORESECURITYDB_VERSION) {
        return erase_db();
    }

    return true;
}

bool KVStoreSecurityDb::erase_db() {
    union zero_t {
        int dummy; /* we need a dummy for initialisation */
        uint8_t buffer[sizeof(SecurityEntryKeys_t)];
        entry_t entries[BLE_SECURITY_DATABASE_MAX_ENTRIES];
    } zero = { 0 };
    memset(&zero, 0, sizeof(zero));

    /* we zero the database and make sure we can fit all our keys */

    db_write(zero.entries, DB_ENTRIES);
    db_write((SecurityEntryIdentity_t*)zero.buffer, DB_LOCAL_IDENTITY);
    db_write((csrk_t*)zero.buffer, DB_LOCAL_CSRK);
    db_write((sign_count_t*)zero.buffer, DB_LOCAL_SIGN_COUNT);

    bool reload = false;
    db_write(&reload, DB_RESTORE);

    for (int index = 0; index < BLE_SECURITY_DATABASE_MAX_ENTRIES; ++index) {
        db_write_entry((SecurityEntryKeys_t*)zero.buffer, DB_ENTRY_LOCAL_KEYS, index);
        db_write_entry((SecurityEntryIdentity_t*)zero.buffer, DB_ENTRY_PEER_IDENTITY, index);
        db_write_entry((SecurityEntryKeys_t*)zero.buffer, DB_ENTRY_PEER_KEYS, index);
        db_write_entry((SecurityEntrySigning_t*)zero.buffer, DB_ENTRY_PEER_SIGNING, index);
    }

    /* now we write the version and read it back to see if was written succesfully */
    uint8_t version = KVSTORESECURITYDB_VERSION;
    db_write(&version, DB_VERSION);
    version = 0;
    db_read(&version, DB_VERSION);

    return (version == KVSTORESECURITYDB_VERSION);
}

SecurityDistributionFlags_t* KVStoreSecurityDb::get_distribution_flags(
    entry_handle_t db_handle
) {
    return reinterpret_cast<SecurityDistributionFlags_t*>(db_handle);
}

/* local keys */

/* set */
void KVStoreSecurityDb::set_entry_local_ltk(
    entry_handle_t db_handle,
    const ltk_t &ltk
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    entry->flags.ltk_sent = true;

    SecurityEntryKeys_t* current_entry = read_in_entry_local_keys(db_handle);
    current_entry->ltk = ltk;

    db_write_entry(current_entry, DB_ENTRY_LOCAL_KEYS, entry->index);
}

void KVStoreSecurityDb::set_entry_local_ediv_rand(
    entry_handle_t db_handle,
    const ediv_t &ediv,
    const rand_t &rand
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    SecurityEntryKeys_t* current_entry = read_in_entry_local_keys(db_handle);
    current_entry->ediv = ediv;
    current_entry->rand = rand;

    db_write_entry(current_entry, DB_ENTRY_LOCAL_KEYS, entry->index);
}

/* peer's keys */

/* set */

void KVStoreSecurityDb::set_entry_peer_ltk(
    entry_handle_t db_handle,
    const ltk_t &ltk
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    entry->flags.ltk_stored = true;

    SecurityEntryKeys_t* current_entry = read_in_entry_peer_keys(db_handle);
    current_entry->ltk = ltk;

    db_write_entry(current_entry, DB_ENTRY_PEER_KEYS, entry->index);
}

void KVStoreSecurityDb::set_entry_peer_ediv_rand(
    entry_handle_t db_handle,
    const ediv_t &ediv,
    const rand_t &rand
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    SecurityEntryKeys_t* current_entry = read_in_entry_peer_keys(db_handle);
    current_entry->ediv = ediv;
    current_entry->rand = rand;

    db_write_entry(current_entry, DB_ENTRY_PEER_KEYS, entry->index);
}

void KVStoreSecurityDb::set_entry_peer_irk(
    entry_handle_t db_handle,
    const irk_t &irk
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    entry->flags.irk_stored = true;

    SecurityEntryIdentity_t* current_entry = read_in_entry_peer_identity(db_handle);
    current_entry->irk = irk;

    db_write_entry(current_entry, DB_ENTRY_PEER_IDENTITY, entry->index);
}

void KVStoreSecurityDb::set_entry_peer_bdaddr(
    entry_handle_t db_handle,
    bool address_is_public,
    const address_t &peer_address
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    SecurityEntryIdentity_t* current_entry = read_in_entry_peer_identity(db_handle);
    current_entry->identity_address = peer_address;
    current_entry->identity_address_is_public = address_is_public;

    db_write_entry(current_entry, DB_ENTRY_PEER_IDENTITY, entry->index);
}

void KVStoreSecurityDb::set_entry_peer_csrk(
    entry_handle_t db_handle,
    const csrk_t &csrk
) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    entry->flags.csrk_stored = true;

    SecurityEntrySigning_t* current_entry = read_in_entry_peer_signing(db_handle);
    current_entry->csrk = csrk;

    db_write_entry(current_entry, DB_ENTRY_PEER_SIGNING, entry->index);
}

void KVStoreSecurityDb::set_entry_peer_sign_counter(
    entry_handle_t db_handle,
    sign_count_t sign_counter
) {
    entry_t *entry = as_entry(db_handle);
    if (entry) {
        entry->peer_sign_counter = sign_counter;
    }
}

void KVStoreSecurityDb::set_local_csrk(
    const csrk_t &csrk
) {
    this->SecurityDb::set_local_csrk(csrk);
    db_write(&_local_csrk, DB_LOCAL_CSRK);
}

void KVStoreSecurityDb::set_local_identity(
    const irk_t &irk,
    const address_t &identity_address,
    bool public_address
) {
    this->SecurityDb::set_local_identity(irk, identity_address, public_address);
    db_write(&_local_identity, DB_LOCAL_IDENTITY);
}

/* saving and loading from nvm */

void KVStoreSecurityDb::restore() {
    /* restore if requested */
    bool restore_toggle = false;
    db_read(&restore_toggle, DB_RESTORE);

    if (!restore_toggle) {
        erase_db();
        return;
    }

    db_read(&_entries, DB_ENTRIES);
    db_read(&_local_identity, DB_LOCAL_IDENTITY);
    db_read(&_local_csrk, DB_LOCAL_CSRK);
    db_read(&_local_sign_counter, DB_LOCAL_SIGN_COUNT);
}

void KVStoreSecurityDb::sync(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    /* all entries are stored in a single key so we store them all*/
    db_write(&_entries, DB_ENTRIES);
    db_write(&_local_identity, DB_LOCAL_IDENTITY);
    db_write(&_local_csrk, DB_LOCAL_CSRK);
    db_write(&_local_sign_counter, DB_LOCAL_SIGN_COUNT);
}

void KVStoreSecurityDb::set_restore(bool reload) {
    db_write(&reload, DB_RESTORE);
}

/* helper functions */

uint8_t KVStoreSecurityDb::get_entry_count() {
    return BLE_SECURITY_DATABASE_MAX_ENTRIES;
}

SecurityDistributionFlags_t* KVStoreSecurityDb::get_entry_handle_by_index(uint8_t index) {
    if (index < get_entry_count()) {
        return &_entries[index].flags;
    } else {
        return nullptr;
    }
}

void KVStoreSecurityDb::reset_entry(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return;
    }

    if (entry->index != ENTRY_INVALID) {
        uint8_t zero_buffer[sizeof(SecurityEntryKeys_t)] = {0};

        db_write_entry((SecurityEntryKeys_t*)zero_buffer, DB_ENTRY_LOCAL_KEYS, entry->index);
        db_write_entry((SecurityEntryIdentity_t*)zero_buffer, DB_ENTRY_PEER_IDENTITY, entry->index);
        db_write_entry((SecurityEntryKeys_t*)zero_buffer, DB_ENTRY_PEER_KEYS, entry->index);
        db_write_entry((SecurityEntrySigning_t*)zero_buffer, DB_ENTRY_PEER_SIGNING, entry->index);

        entry->index = ENTRY_INVALID;
    }

    entry->flags = SecurityDistributionFlags_t();
    entry->peer_sign_counter = 0;
}

SecurityEntryIdentity_t* KVStoreSecurityDb::read_in_entry_peer_identity(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return nullptr;
    }

    SecurityEntryIdentity_t* identity = reinterpret_cast<SecurityEntryIdentity_t*>(_buffer);
    db_read_entry(identity, DB_ENTRY_PEER_IDENTITY, entry->index);

    return identity;
};

SecurityEntryKeys_t* KVStoreSecurityDb::read_in_entry_peer_keys(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return nullptr;
    }

    SecurityEntryKeys_t* keys = reinterpret_cast<SecurityEntryKeys_t*>(_buffer);
    db_read_entry(keys, DB_ENTRY_PEER_KEYS, entry->index);

    return keys;
};

SecurityEntryKeys_t* KVStoreSecurityDb::read_in_entry_local_keys(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return nullptr;
    }

    SecurityEntryKeys_t* keys = reinterpret_cast<SecurityEntryKeys_t*>(_buffer);
    db_read_entry(keys, DB_ENTRY_LOCAL_KEYS, entry->index);

    return keys;
};

SecurityEntrySigning_t* KVStoreSecurityDb::read_in_entry_peer_signing(entry_handle_t db_handle) {
    entry_t *entry = as_entry(db_handle);
    if (!entry) {
        return nullptr;
    }

    /* only read in the csrk */
    csrk_t* csrk = reinterpret_cast<csrk_t*>(_buffer);
    db_read_entry(csrk, DB_ENTRY_PEER_SIGNING, entry->index);


    /* use the counter held in memory */
    SecurityEntrySigning_t* signing = reinterpret_cast<SecurityEntrySigning_t*>(_buffer);
    signing->counter = entry->peer_sign_counter;

    return signing;
};

} /* namespace ble */
} /* namespace generic */

#endif // BLE_SECURITY_DATABASE_KVSTORE
