// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/MetaData.h"

namespace Ogg
{
  namespace Vorbis
  {
    class MetaData::Private
    {
      public:

        long time;
        long bitRate;
        long tag;
    };

    MetaData::MetaData()
    {
      d = new Private;
    }

    MetaData::MetaData(long time, long bitRate, long tag)
    {
      d = new Private;

      d->time     = time;
      d->bitRate  = bitRate;
      d->tag      = tag;
    }

    MetaData::~MetaData()
    {
      delete d;
      d = 0;
    }

      long
    MetaData::time() const
    {
      return d->time;
    }

      long
    MetaData::bitRate() const
    {
      return d->bitRate;
    }

      long
    MetaData::tag() const
    {
      return d->tag;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
