// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_PCM_PLAY_DATA_SINK_H
#define OGG_VORBIS_PLUS_PLUS_PCM_PLAY_DATA_SINK_H

#include <list>

#include "vorbispp/PCMDataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    class PCMPlayDataSink : public PCMDataSink
    {
      public:

        PCMPlayDataSink();
        virtual ~PCMPlayDataSink();

        virtual bool open(const string & url, const OptionMap &);
        virtual bool close();

        virtual bool write(const DataBlock &);

      protected:

        list<string> tokenise(const string &);

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
