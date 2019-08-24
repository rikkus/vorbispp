// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_PCM_FILE_DATA_SOURCE_H
#define OGG_VORBIS_PLUS_PLUS_PCM_FILE_DATA_SOURCE_H

#include "vorbispp/PCMDataSource.h"

namespace Ogg
{
  namespace Vorbis
  {
    /**
     * Simple FILE-based data source, for convenience.
     */
    class PCMFileDataSource : public PCMDataSource
    {
      public:

        PCMFileDataSource();
        virtual ~PCMFileDataSource();

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
