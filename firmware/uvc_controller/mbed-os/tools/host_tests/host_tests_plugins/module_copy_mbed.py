"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited
SPDX-License-Identifier: Apache-2.0

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
from __future__ import print_function

from shutil import copy
from .host_test_plugins import HostTestPluginBase
from time import sleep


class HostTestPluginCopyMethod_Mbed(HostTestPluginBase):

    def generic_mbed_copy(self, image_path, destination_disk):
        """ Generic mbed copy method for "mbed enabled" devices.
            It uses standard python shuitl function to copy
            image_file (target specific binary) to device's disk.
        """
        result = True
        if not destination_disk.endswith('/') and not destination_disk.endswith('\\'):
            destination_disk += '/'
        try:
            copy(image_path, destination_disk)
        except Exception as e:
            self.print_plugin_error("shutil.copy('%s', '%s')"% (image_path, destination_disk))
            self.print_plugin_error("Error: %s"% str(e))
            result = False
        return result

    # Plugin interface
    name = 'HostTestPluginCopyMethod_Mbed'
    type = 'CopyMethod'
    stable = True
    capabilities = ['shutil', 'default']
    required_parameters = ['image_path', 'destination_disk', 'program_cycle_s']

    def setup(self, *args, **kwargs):
        """ Configure plugin, this function should be called before plugin execute() method is used.
        """
        return True

    def execute(self, capability, *args, **kwargs):
        """ Executes capability by name.
            Each capability may directly just call some command line
            program or execute building pythonic function
        """
        result = False
        if self.check_parameters(capability, *args, **kwargs) is True:
            # Capability 'default' is a dummy capability
            if capability == 'shutil':
                image_path = kwargs['image_path']
                destination_disk = kwargs['destination_disk']
                program_cycle_s = kwargs['program_cycle_s']
                # Wait for mount point to be ready
                self.check_mount_point_ready(destination_disk)  # Blocking
                result = self.generic_mbed_copy(image_path, destination_disk)

                # Allow mbed to cycle
                sleep(program_cycle_s)

        return result


def load_plugin():
    """ Returns plugin available in this module
    """
    return HostTestPluginCopyMethod_Mbed()
