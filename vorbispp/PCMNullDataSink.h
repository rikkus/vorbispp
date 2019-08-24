// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_PCM_NULL_DATA_SINK_H
#define OGG_VORBIS_PLUS_PLUS_PCM_NULL_DATA_SINK_H

#include "vorbispp/PCMDataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    class PCMNullDataSink : public PCMDataSink
    {
      public:

        PCMNullDataSink();
        virtual ~PCMNullDataSink();

        virtual bool write(const DataBlock &);
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
