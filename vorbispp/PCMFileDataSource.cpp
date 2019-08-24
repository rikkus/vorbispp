// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/PCMFileDataSource.h"

#include <iostream>
#include <fstream>
#include <string>

namespace Ogg
{
  namespace Vorbis
  {
    class PCMFileDataSource::Private
    {
      public:

        string url;
        ifstream stream;
    };

    PCMFileDataSource::PCMFileDataSource()
      : PCMDataSource()
    {
      d = new Private;
    }

    PCMFileDataSource::~PCMFileDataSource()
    {
      delete d;
      d = 0;
    }

      bool
    PCMFileDataSource::open(const string & filename)
    {
      if (d->stream.is_open())
      {
        cerr << "PCMFileDataSource::open(): Stream already open" << endl;
        return false;
      }

      string fn(filename);

      if ("file:" == fn.substr(0, 5))
        fn.erase(0, 5);

      d->stream.open(fn.c_str());

      if (!d->stream.is_open())
        return false;

      return true;
    }

      DataBlock
    PCMFileDataSource::read(unsigned int bytes)
    {
      DataBlock b;

      if (!d->stream.is_open())
        return b;

      copy_n(istream_iterator<int>(d->stream), bytes, back_inserter<DataBlock>(b));

      return b;
    }

      bool
    PCMFileDataSource::seek(unsigned long position)
    {
      if (!d->stream.is_open())
        return false;

      return false;// ??? position == d->stream.seekpos(position);
    }

      void
    PCMFileDataSource::close()
    {
      d->stream.close();
    }

      unsigned long
    PCMFileDataSource::position() const
    {
      if (!d->stream.is_open())
        return 0;

      // Er, dunno.
      return 0;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
