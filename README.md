ungreek
=======

`ungreek` is a simple C99 script to expand Greek letters in **UTF-8** encoding to their Latin names.
In addition, `uncode` is a Python 2.6+ and 3.0+ script to [normalize][NIH] non-ASCII characters to ASCII.
Both scripts accept input from `<stdin>` or as file arguments and write to `<stdout>`.

To compile `ungreek`, a C99 compiler has to be available; type `make` to compile using GNU Make.
To use `uncode`, the PyPI `unidecode` package has to be installed (`pip install unidecode` or `easy_install unidecode`). 

[NIH]: http://lexsrv2.nlm.nih.gov/LexSysGroup/Projects/lvg/2011/docs/designDoc/UDF/unicode/unicodeToAscii.html
