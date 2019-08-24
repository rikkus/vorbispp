// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/Filter.h"

namespace Ogg
{
  namespace Vorbis
  {
    class Filter::Private
    {
      public:

        DataSink * output;
    };

    Filter::Filter(DataSink * sink)
      : DataSink()
    {
      d = new Private;
      d->output = sink;
    }

    Filter::~Filter()
    {
      close();
      delete d;
    }

      bool
    Filter::open(const string & url, const OptionMap & optionMap)
    {
      return d->output->open(url, optionMap);
    }

      bool
    Filter::close()
    {
      return d->output->close();
    }

      bool
    Filter::write(const DataBlock & block)
    {
      return d->output->write(block);
    }

      DataSink *
    Filter::output()
    {
      return d->output;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
