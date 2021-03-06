
####################
# UNIT TESTS
####################

set(unittest-includes ${unittest-includes}
  .
  ..
)

set(unittest-sources
  ../features/storage/blockdevice/ProfilingBlockDevice.cpp
  ../features/storage/blockdevice/HeapBlockDevice.cpp
  stubs/mbed_atomic_stub.c
  stubs/mbed_assert_stub.cpp
)

set(unittest-test-sources
  features/storage/blockdevice/ProfilingBlockDevice/test_ProfilingBlockDevice.cpp
  stubs/mbed_error.c
)
