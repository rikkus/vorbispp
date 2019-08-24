// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_FILTER_H
#define OGG_VORBIS_PLUS_PLUS_FILTER_H

#include "vorbispp/DataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    class Filter : public DataSink
    {
      public:

        Filter(DataSink *);
        virtual ~Filter();

        virtual bool open(const string & url, const OptionMap & optionMap);
        virtual bool close();

        virtual bool write(const DataBlock &) = 0;

      protected:

        DataSink * output();

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
