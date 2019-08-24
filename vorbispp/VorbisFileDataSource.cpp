// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/VorbisFileDataSource.h"

#include <iostream>
#include <fstream>
#include <string.h> // For strncmp.

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisFileDataSource::Private
    {
      public:

        ifstream stream;
    };

    VorbisFileDataSource::VorbisFileDataSource()
      : VorbisDataSource()
    {
      d = new Private;
    }

    VorbisFileDataSource::~VorbisFileDataSource()
    {
      delete d;
    }

      bool
    VorbisFileDataSource::open(const string & _filename)
    {
      string filename(_filename);

      if ("file:" == filename.substr(0, 5))
        filename.erase(0, 5);

      d->stream.open(filename.c_str());

      if (!d->stream.is_open())
      {
        cerr << "VorbisFileDataSource::open: fail" << endl;
        return false;
      }

      return vorbisOpen();
    }

      DataBlock
    VorbisFileDataSource::read(unsigned int bytes)
    {
      DataBlock b;

      if (!d->stream.is_open())
      {
        cerr << "VorbisFileDataSource::read: file not open" << endl;
        return b;
      }

      copy_n(istream_iterator<char>(d->stream), bytes, back_inserter<DataBlock>(b));

      return b;
    }

      bool
    VorbisFileDataSource::seek(unsigned long position)
    {
      cerr << "VorbisFileDataSource::seek " << position << endl;

      if (!d->stream.is_open())
      {
        cerr << "VorbisFileDataSource::seek: file not open" << endl;
        return false;
      }

      d->stream.seekg(position);

      cerr << "VorbisFileDataSource::seek: done seekg, assuming ok" << endl;

      return true;
    }

      void
    VorbisFileDataSource::close()
    {
      d->stream.close();
    }

      unsigned long
    VorbisFileDataSource::position() const
    {
      if (!d->stream.is_open())
      {
        cerr << "VorbisFileDataSource::position: file not open" << endl;
        return 0;
      }

      unsigned long l = d->stream.tellg();
      cerr << "VorbisFileDataSource::position: returning " << l << endl;

      return l;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
