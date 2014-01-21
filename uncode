#!/usr/bin/env python
from __future__ import print_function  # script works in Py2 and 3

import unidecode  # pip install unidecode
import fileinput
import sys

# unicode/str issues between Py2 and 3
if sys.version < '3':
    import codecs
    def u(x):
        return codecs.unicode_escape_decode(x)[0]
else:
    def u(x):
        return x

for line in fileinput.input():
    print(unidecode.unidecode(u(line)), end='')
