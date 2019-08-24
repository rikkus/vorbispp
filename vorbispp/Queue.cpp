// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>
#include <queue>

#include "vorbispp/Queue.h"

namespace Ogg
{
  namespace Vorbis
  {
    class Queue::Private
    {
      public:

        Semaphore         readyForDataSemaphore;
        Semaphore         readyToWriteSemaphore;
        queue<DataBlock>  buf;
        unsigned int      max;
    };

    Queue::Queue(DataSink * output)
      : Filter(output)
    {
      d = new Private;
      assert(d);
      d->max = 42;

      Start();
    }

    Queue::Queue(unsigned int length, DataSink * output)
      : Filter(output)
    {
      assert(d);
      d = new Private;
      d->max = length;

      Start();
    }

      bool
    Queue::write(const DataBlock & block)
    {
      assert(d);
      if (d->buf.size() == d->max)
        return false;

      d->buf.push(block);
      d->readyToWriteSemaphore.Post();
    }

      void
    Queue::Run()
    {
      while (true)
      {
        assert(d);
        d->readyToWriteSemaphore.Wait();

        if (0 == d->buf.size())
        {
          cerr << "Hmm, buf is empty. Quitting" << endl;
          break;
        }

        if (!output()->write(d->buf.front()))
        {
          cerr << "Hmm, can't write to output. Quitting" << endl;
          break;
        }
        else
        {
          d->buf.pop();
          d->readyForDataSemaphore.Post();
        }
      }
    }

      void
    Queue::blockUntilReady()
    {
      d->readyForDataSemaphore.Wait();
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
