#!/usr/bin/env python3
#
# Copyright 2020 WebAssembly Community Group participants
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys

import test.shared as shared


COPYRIGHT = '''\
/*
 * Copyright 2020 WebAssembly Community Group participants
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
'''

NOTICE = '''\
//=============================================================================
// This is an AUTOGENERATED file, even though it looks human-readable! Do not
// edit it by hand, instead edit what it is generated from. You can and should
// treat it like human-written code in all other ways, though, like reviewing
// it in a PR, etc.
//=============================================================================
'''


def generate_defs():
    target = shared.in_binaryen('src', 'wasm-instructions.generated.h')
    with open(target, 'w') as out:
        out.write(COPYRIGHT + '\n' + NOTICE)


def main():
    if sys.version_info.major != 3:
        import datetime
        print("It's " + str(datetime.datetime.now().year) + "! Use Python 3!")
        sys.exit(1)
    generate_defs()


if __name__ == "__main__":
    main()
