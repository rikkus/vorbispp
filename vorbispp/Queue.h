// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_QUEUE_H
#define OGG_VORBIS_PLUS_PLUS_QUEUE_H

#include <cc++/thread.h>

#include "vorbispp/Filter.h"

namespace Ogg
{
  namespace Vorbis
  {
    class Queue : public Filter, public Thread
    {
      public:

        Queue(DataSink *);

        Queue(unsigned int length, DataSink *);

        virtual bool write(const DataBlock &);

        virtual void blockUntilReady();

      protected:

        virtual void Run();

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
