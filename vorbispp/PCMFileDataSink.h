// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_PCM_FILE_DATA_SINK_H
#define OGG_VORBIS_PLUS_PLUS_PCM_FILE_DATA_SINK_H

#include "vorbispp/PCMDataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    class PCMFileDataSink : public PCMDataSink
    {
      public:

        PCMFileDataSink();
        virtual ~PCMFileDataSink();

        virtual bool open(const string & filename, const OptionMap &);
        virtual bool close();
        virtual bool write(const DataBlock &);

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
