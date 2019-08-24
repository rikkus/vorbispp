// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <vorbis/vorbisfile.h>
#include <vorbis/codec.h>

#include "vorbispp/VorbisDataSource.h"
#include "vorbispp/Decoder.h"
#include "vorbispp/DataSink.h"

#include <iostream>
#include <string.h> // For memset
#include <assert.h>

namespace Ogg
{
  namespace Vorbis
  {
    class Decoder::Private
    {
      public:

        Private()
          : source    (0L),
            sink      (0L),
            bitStream (0),
            rate      (0),
            channels  (0),
            version   (0),
            length    (0.0)
        {
          // Empty.
        }

        VorbisDataSource  * source;
        DataSink          * sink;
        int                 bitStream;
        long                rate;
        int                 channels;
        int                 version;
        double              length;
    };

    Decoder::Decoder(VorbisDataSource * source, DataSink * sink)
    {
      d = new Private;
      assert(d);

      d->source = source;
      d->sink = sink;

      assert(d->source);
      assert(d->sink);
    }

    Decoder::~Decoder()
    {
      close();

      assert(d);
      delete d;
      d = 0;
    }

      bool
    Decoder::rawSeek(long pos)
    {
      assert(d);
      assert(d->source);

      int err = ::ov_raw_seek(d->source->vorbisFile(), pos);

      return err < 0;
    }

      bool
    Decoder::pcmSeek(int64_t pos)
    {
      assert(d);
      assert(d->source);

      int err = ::ov_pcm_seek(d->source->vorbisFile(), pos);

      return err < 0;
    }

      bool
    Decoder::pcmSeekPage(int64_t pos)
    {
      assert(d);
      assert(d->source);

      int err = ::ov_pcm_seek_page(d->source->vorbisFile(), pos);

      return err < 0;
    }

      bool
    Decoder::timeSeek(double pos)
    {
      assert(d);
      assert(d->source);

      int err = ::ov_time_seek(d->source->vorbisFile(), pos);

      return err < 0;
    }

      bool
    Decoder::timeSeekPage(double pos)
    {
      assert(d);
      assert(d->source);

      int err = ::ov_time_seek_page(d->source->vorbisFile(), pos);

      return err < 0;
    }

      bool
    Decoder::read
    (
     unsigned long    maxBytes,
     unsigned long  & bytesRead,
     double         & time,
     long           & bitRate,
     long             tag
    )
    {
      char * buf = new char[maxBytes];

      if (0 == buf)
        return false;

      bytesRead =
        static_cast<unsigned long>
        (
         ::ov_read
         (
          d->source->vorbisFile(),
          buf,
          maxBytes,
          0,
          2,
          1,
          &d->bitStream
         )
        );

      time    = ::ov_time_tell        (d->source->vorbisFile());
      bitRate = ::ov_bitrate_instant  (d->source->vorbisFile());

      DataBlock data(buf, buf + bytesRead);

      if (!d->sink->write(data))
      {
        d->sink->blockUntilReady();
      }

      delete [] buf;
      buf = 0;

      return true;
    }

      bool
    Decoder::openInput(const string & url)
    {
      assert(d);
      assert(d->source);

      bool ok = d->source->open(url);

      if (!ok)
        return false;

      d->length = ::ov_time_total(d->source->vorbisFile(), -1);

      d->bitStream = 0;

      ::vorbis_info * vi = ::ov_info(d->source->vorbisFile(), -1);

      if (0 == vi)
      {
        return false;
      }

      d->rate     = vi->rate;
      d->channels = vi->channels;

      return true;
    }

      bool
    Decoder::openOutput(const string & url, const OptionMap & optionMap)
    {
      cerr << "Decoder::openOutput" << endl;
      assert(d);
      assert(d->sink);
      return d->sink->open(url, optionMap);
    }

      double
    Decoder::length() const
    {
      return d->length;
    }

      int
    Decoder::version() const
    {
      return d->version;
    }

      int
    Decoder::channels() const
    {
      return d->channels;
    }

      long
    Decoder::rate() const
    {
      return d->rate;
    }

      void
    Decoder::close()
    {
      assert(d);
      assert(d->source);
      ::ov_clear(d->source->vorbisFile());
    }

      int64_t
    Decoder::rawTell() const
    {
      assert(d);
      assert(d->source);
      return ::ov_raw_tell(d->source->vorbisFile());
    }

      int64_t
    Decoder::pcmTell() const
    {
      assert(d);
      assert(d->source);
      return ::ov_pcm_tell(d->source->vorbisFile());
    }

      double
    Decoder::timeTell() const
    {
      assert(d);
      assert(d->source);
      return ::ov_time_tell(d->source->vorbisFile());
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
