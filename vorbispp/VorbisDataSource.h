// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_VORBIS_DATA_SOURCE_H
#define OGG_VORBIS_PLUS_PLUS_VORBIS_DATA_SOURCE_H

#include <vorbis/vorbisfile.h>  // For OggVorbis_File.

#include "vorbispp/DataSource.h"

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisDataSource : public DataSource
    {
      public:

        VorbisDataSource();
        virtual ~VorbisDataSource();

        OggVorbis_File * vorbisFile();

        virtual bool          open      (const string & url)      = 0;
        virtual DataBlock     read      (unsigned int bytes)      = 0;
        virtual bool          seek      (unsigned long position)  = 0;
        virtual void          close     ()                        = 0;
        virtual unsigned long position  () const                  = 0;
        virtual bool          seekable  () const                  = 0;

      protected:

        bool vorbisOpen();

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
