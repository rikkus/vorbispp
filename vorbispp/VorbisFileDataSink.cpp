// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>
#include <stdio.h>

#include "vorbispp/VorbisFileDataSink.h"
#include "vorbispp/MetaData.h"

using namespace std;

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisFileDataSink::Private
    {
      public:

        Private()
          : file(0L)
        {
        }

        FILE * file;
    };

    VorbisFileDataSink::VorbisFileDataSink()
      : VorbisDataSink()
    {
      d = new Private;
    }

    VorbisFileDataSink::~VorbisFileDataSink()
    {
      delete d;
      d = 0;
    }

      bool
    VorbisFileDataSink::open(const string & filename, const OptionMap & /* unused */)
    {
      if (0 != d->file)
      {
        cerr << "VorbisFileDataSink: already have a file open" << endl;
        return false;
      }

      FILE * f = ::fopen(filename.c_str(), "w+");

      if (0 == f)
      {
        cerr << "VorbisFileDataSink: cannot open file " << filename << endl;
        return false;
      }

      d->file = f;

      return true;
    }

      bool
    VorbisFileDataSink::close()
    {
      if (0 == d->file)
        return true;

      int ok = ::fclose(d->file);

      if (0 != ok)
        return false;

      return true;
    }

      bool
    VorbisFileDataSink::write(const DataBlock & dataBlock)
    {
      if (0 == d->file)
      {
        cerr << "VorbisFileDataSink: file is not open" << endl;
        return false;
      }

      size_t blocksWritten = 0;

      do
      {
#if 0
        blocksWritten =
          ::fwrite
          (
           const_cast<char *>(dataBlock.data()),
           1,
           dataBlock.size(),
           d->file
          );
#endif

        if (0 == blocksWritten)
        {
          cerr << "Failed write" << endl;
        }

      } while (1 != blocksWritten);

      return true; 
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
