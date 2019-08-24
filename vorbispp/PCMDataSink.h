// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_PCM_DATA_SINK_H
#define OGG_VORBIS_PLUS_PLUS_PCM_DATA_SINK_H

#include <string>

#include "vorbispp/DataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    class PCMDataSink : public DataSink
    {
      public:

        PCMDataSink();
        virtual ~PCMDataSink();

        virtual bool open(const string & url, const OptionMap & optionMap)  = 0;
        virtual bool close()                                                = 0;
        virtual bool write(const DataBlock &)                               = 0;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
