"""
mbed SDK
Copyright (c) 2014-2016 ARM Limited
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
from os.path import splitext, basename
from os import remove

from tools.export.exporters import Exporter, deprecated_exporter


@deprecated_exporter
class CoIDE(Exporter):
    NAME = 'CoIDE'
    TOOLCHAIN = 'GCC_ARM'

    TARGETS = [
        'KL25Z',
        'LPC1768',
        'ARCH_PRO',
        'ARCH_MAX',
        'NUCLEO_L152RE',
        'NUCLEO_F070RB',
        'NUCLEO_F072RB',
        'NUCLEO_F091RC',
        'NUCLEO_F103RB',
        'NUCLEO_F303K8',
        'NUCLEO_F303RE',
        'NUCLEO_F401RE',
        'NUCLEO_F411RE',
        'NUCLEO_F446RE',
        'DISCO_F429ZI',
        'MTS_MDOT_F411RE',
        'MOTE_L152RC',
        'NZ32_SC151',
    ]

    # seems like CoIDE currently supports only one type
    FILE_TYPES = {
        'c_sources':'1',
        'cpp_sources':'1',
        's_sources':'1'
    }
    FILE_TYPES2 = {
        'headers':'1'
    }

    def generate(self):
        self.resources.win_to_unix()
        source_files = []
        for r_type, n in CoIDE.FILE_TYPES.items():
            for file in getattr(self.resources, r_type):
                source_files.append({
                    'name': basename(file), 'type': n, 'path': file
                })
        header_files = []
        for r_type, n in CoIDE.FILE_TYPES2.items():
            for file in getattr(self.resources, r_type):
                header_files.append({
                    'name': basename(file), 'type': n, 'path': file
                })

        libraries = []
        for lib in self.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])

        if self.resources.linker_script is None:
            self.resources.linker_script = ''
            
        ctx = {
            'name': self.project_name,
            'source_files': source_files,
            'header_files': header_files,
            'include_paths': self.resources.inc_dirs,
            'scatter_file': self.resources.linker_script,
            'library_paths': self.resources.lib_dirs,
            'object_files': self.resources.objects,
            'libraries': libraries,
            'symbols': self.toolchain.get_symbols()
        }
        target = self.target.lower()

        # Project file
        self.gen_file('coide/%s.coproj.tmpl' % target, ctx, '%s.coproj' % self.project_name)

    @staticmethod
    def clean(project_name):
        remove('%s.coproj' % project_name)
