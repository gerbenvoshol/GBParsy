# GBParsy
GBParsy is a library of functions that parses the GenBank flatfile, which is a representative and popular sequence format. The library is optimized for speed and efficient use of memory so it can rapidly parse large sequence such as Arabidopsis chromosome for genomic analysis. GBParsyPy is additional version of GBParsy for the Python. GBParsyPy adopted GBParsy as a core parser so GBParsyPy inherited all of its features from GBParsy.

## How to install GBParsy and GBParsyPy

### Common Process

   1. Download the compressed library

   2. Uncompress the file into a directory which you want.

      $ unzip gbfp-master.zip

### Install GBFP

   1. Make and install the library

      $ cd gbfp-master
      $ make
      $ make install (as a root)
      $ cd ..

### Install GBFPY

   1. Make and install the module

      $ cd gbfp-0.6.1/gbfpy
      $ python setup.py build
      $ python setup.py install (as a root)
      $ cd ../..


## Publication

T.-H. Lee, Y.-K. Kim and B.H. Nahm (2008) GBParsy: A GenBank flatfile parser library with high speed. BMC Bioinformatics, 9:321.

## Contact

If you have comments, questions and suggestions about GBParsy, please send a mail to gpvoshol@gmail.com.

## Credits
### Orignal author
* Tae-Ho Lee <thlee@bio.mju.ac.kr>
### Current Maintainer
* Gerben Voshol <gpvoshol@gmail.com>
