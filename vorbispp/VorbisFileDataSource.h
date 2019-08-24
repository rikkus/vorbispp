// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_VORBIS_FILE_DATA_SOURCE_H
#define OGG_VORBIS_PLUS_PLUS_VORBIS_FILE_DATA_SOURCE_H

#include "vorbispp/VorbisDataSource.h"

#include <stdio.h>      // For FILE.
#include <sys/types.h>  // For int64_t.

namespace Ogg
{
  namespace Vorbis
  {
    /**
     * Simple FILE-based data source, for convenience.
     */
    class VorbisFileDataSource : public VorbisDataSource
    {
      public:

        VorbisFileDataSource();
        virtual ~VorbisFileDataSource();

      protected:

        /**
         * fopen(3), but strips "file:" from beginning of string
         * if it exists, and returns bool.
         */
        virtual bool          open      (const string & url);
        virtual DataBlock     read      (unsigned int bytes);
        virtual bool          seek      (unsigned long position);
        virtual void          close     ();
        virtual unsigned long position  () const;
        virtual bool          seekable  () const { return true; }

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
