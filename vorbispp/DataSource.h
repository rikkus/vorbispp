// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_DATA_SOURCE_H
#define OGG_VORBIS_PLUS_PLUS_DATA_SOURCE_H

#include <sys/types.h>

#include <string>

#include "vorbispp/DataBlock.h"

namespace Ogg
{
  namespace Vorbis
  {
    /**
     * ABC representing a source of digital data.
     */
    class DataSource
    {
      public:

        DataSource();
        virtual ~DataSource();

        virtual bool          open      (const string & url)      = 0;
        virtual DataBlock     read      (unsigned int bytes)      = 0;
        virtual bool          seek      (unsigned long position)  = 0;
        virtual void          close     ()                        = 0;
        virtual unsigned long position  () const                  = 0;
        virtual bool          seekable  () const                  = 0;

      protected:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
