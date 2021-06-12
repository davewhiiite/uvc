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
import socket

ECHO_SERVER_ADDRESS = "10.2.202.45"
ECHO_PORT = 7

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((ECHO_SERVER_ADDRESS, ECHO_PORT))

s.sendall('Hello, world')
data = s.recv(1024)
s.close()
print 'Received', repr(data)
