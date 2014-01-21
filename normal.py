#!/usr/bin/env python

import unidecode  # pip install unidecode
import fileinput

for line in fileinput.input():
    print(unidecode.unidecode(line), end='')
