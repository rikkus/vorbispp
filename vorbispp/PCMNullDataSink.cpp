// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/PCMNullDataSink.h"

namespace Ogg
{
  namespace Vorbis
  {
    PCMNullDataSink::PCMNullDataSink()
      : PCMDataSink()
    {
      // Empty.
    }

    PCMNullDataSink::~PCMNullDataSink()
    {
      // Empty.
    }

      bool
    PCMNullDataSink::write(const DataBlock &)
    {
      return true;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
