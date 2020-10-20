CHMLIB 0.41a
============

-------
Summary
-------
chmlib is a small library designed for accessing MS ITSS files.  The ITSS file
format is used for Microsoft Html Help files (.chm), which have been the
predominant medium for software documentation from Microsoft during the past
several years, having superceded the previously used .hlp file format.

Note that this is NOT the same as the OLE structured storage file format used
by MS Excel, Word, and so on.  Instead, it is a different file format which
fulfills a similar purpose.  Both file formats may be accessed via instances
of the IStorage COM interface, which is essentially an "acts like a
filesystem" interface.

-------
File Format Support
-------

Lookup of files in the archive is supported, and should be relatively quick.
Reading of files in the archive is also supported.
Writing is not supported, but may be added in the future.

In terms of support for the ITSS file format, there are a few places in which
the support provided by this library is not fully general:

1. ITSS files whose names contain UTF-8 characters which are not part of the
   ASCII subset will not currently be dealt with gracefully.  Currently, the
   filenames are not converted from UTF-8, but are instead returned as-is.  I'm
   very interested in hearing any suggestions as to the "right" way to handle
   this.

2. Only version 3 ITSS files are supported at present, though some work has
   gone towards divining the differences between different versions of the
   file format.  It is possible that version 2 ITSS files might work properly
   with this library, but unconfirmed.

3. Archives larger than 4 GB should be supported just fine, but if they
   contain files larger than 4GB, this library may break.  Fortunately, this
   seems somewhat unlikely.

If you run into .chm files (or files you suspect are ITSS files) that this
library doesn't work with, please contact me so I can fix the library.

-------
Portability
-------

This software is maintained on an x86-64 Debian GNU/Linux machine using gcc
7.x. Win32 support is provided but not tested.

The original version worked on multiple systems, so this one will probably 
work on most systems that have Meson and GCC support.

-------
CREDITS
-------

Check the AUTHORS file.

