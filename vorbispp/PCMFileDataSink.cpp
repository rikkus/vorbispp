// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>
#include <fstream>
#include <stdio.h>

#include "vorbispp/PCMFileDataSink.h"
#include "vorbispp/MetaData.h"

using namespace std;

namespace Ogg
{
  namespace Vorbis
  {
    class PCMFileDataSink::Private
    {
      public:

        Private()
        {
        }

        ofstream file;
    };

    PCMFileDataSink::PCMFileDataSink()
      : PCMDataSink()
    {
      d = new Private;
    }

    PCMFileDataSink::~PCMFileDataSink()
    {
      delete d;
      d = 0;
    }

      bool
    PCMFileDataSink::open(const string & filename, const OptionMap & /* unused */)
    {
      if (d->file.is_open())
      {
        cerr << "PCMFileDataSink: already have a file open" << endl;
        return false;
      }

      d->file.open(filename.c_str());

      if (!d->file.is_open())
      {
        cerr << "PCMFileDataSink: cannot open file " << filename << endl;
        return false;
      }

      return true;
    }

      bool
    PCMFileDataSink::close()
    {
      if (!d->file.is_open())
        return true;

      d->file.close();

      return d->file.is_open();
    }

      bool
    PCMFileDataSink::write(const DataBlock & dataBlock)
    {
      if (!d->file.is_open())
      {
        cerr << "PCMFileDataSink: file is not open" << endl;
        return false;
      }

      copy(dataBlock.begin(), dataBlock.end(), ostream_iterator<char>(d->file));

      return true; 
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
