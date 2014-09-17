[![Build Status](https://travis-ci.org/jacob-hegna/open8080.svg?branch=master)](https://travis-ci.org/jacob-hegna/open8080)
# open8080
open8080 is a full-service Intel 8080 emulation suite.  It includes an 8080 assembler, a disassembler, and (of course) an 8080 emulator.  All three of these tools are built into the same executable - for example, to assemble a file named `main.S`, you would run `open8080 -a main.S`.  And then to emulate it, you would type `open8080 -e a.out`.

## Installing
```
git clone https://github.com/jacob-hegna/basicpp.git
cd open8080
make
make install
```

It will install to `/usr/local/bin/open8080`.

To remove `open8080`, simply run `make remove`.

## Copyright and License
open8080 is Copyright 2014 Jacob Hegna.

This file is a part of open8080.

open8080 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
