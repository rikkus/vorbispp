// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream> // REMOVE

#include <vorbis/vorbisenc.h>

#include "vorbispp/Encoder.h"
#include "vorbispp/VorbisDataSink.h"

using namespace std;

namespace Ogg
{
  namespace Vorbis
  {
    class Encoder::Settings::Private
    {
      public:

        int           serialNumber;
        BitrateSpec   bitrateSpec;
        CommentList   commentList;
        unsigned int  nominalBitrate;
        unsigned int  channels;
        unsigned int  minBitrate;
        unsigned int  maxBitrate;
        unsigned int  bytesPerSample;
        unsigned int  inputBitrate;
    };

    Encoder::Settings::Settings()
    {
      d = new Private;

      d->serialNumber     = 42;
      d->nominalBitrate   = 128000;
      d->channels         = 2;
      d->bytesPerSample   = 2;
      d->inputBitrate     = 44100;
      d->minBitrate       = 0;
      d->maxBitrate       = 0;
      d->bitrateSpec      = Nominal;
    }

    Encoder::Settings::~Settings()
    {
      delete d;
      d = 0;
    }

    Encoder::Settings::Settings
      (
       int                   serialNumber,
       unsigned int          nominalBitrate,
       unsigned int          channels,
       unsigned int          bytesPerSample,
       unsigned int          inputBitrate,
       const CommentList  &  commentList
      )
    {
      d = new Private;

      d->serialNumber   = serialNumber;
      d->nominalBitrate = nominalBitrate;
      d->channels       = channels;
      d->bytesPerSample = bytesPerSample;
      d->inputBitrate   = inputBitrate;
      d->commentList    = commentList;
      d->minBitrate     = 0;
      d->maxBitrate     = 0;
      d->bitrateSpec    = Nominal;
    }

    Encoder::Settings::Settings
      (
       int                   serialNumber,
       unsigned int          minBitrate,
       unsigned int          maxBitrate,
       unsigned int          channels,
       unsigned int          bytesPerSample,
       unsigned int          inputBitrate,
       const CommentList  &  commentList
      )
    {
      d = new Private;

      d->serialNumber   = serialNumber;
      d->nominalBitrate = 0;
      d->channels       = channels;
      d->bytesPerSample = bytesPerSample;
      d->inputBitrate   = inputBitrate;
      d->commentList    = commentList;
      d->minBitrate     = minBitrate;
      d->maxBitrate     = maxBitrate;
      d->bitrateSpec    = Range;
    }

    Encoder::Settings::Settings(const Encoder::Settings & other)
    {
      d = new Private;

      d->serialNumber   = other.d->serialNumber;
      d->nominalBitrate = other.d->nominalBitrate;
      d->channels       = other.d->channels;
      d->bytesPerSample = other.d->bytesPerSample;
      d->inputBitrate   = other.d->inputBitrate;
      d->commentList    = other.d->commentList;
      d->minBitrate     = other.d->minBitrate;
      d->maxBitrate     = other.d->maxBitrate;
      d->bitrateSpec    = other.d->bitrateSpec;
    }

      Encoder::Settings &
    Encoder::Settings::operator = (const Encoder::Settings & other)
    {
      if (this == &other)
        return *this;

      d->serialNumber   = other.d->serialNumber;
      d->nominalBitrate = other.d->nominalBitrate;
      d->channels       = other.d->channels;
      d->bytesPerSample = other.d->bytesPerSample;
      d->inputBitrate   = other.d->inputBitrate;
      d->commentList    = other.d->commentList;
      d->minBitrate     = other.d->minBitrate;
      d->maxBitrate     = other.d->maxBitrate;
      d->bitrateSpec    = other.d->bitrateSpec;

      return *this;
    }

      int
    Encoder::Settings::serialNumber() const
    {
      return d->serialNumber;
    }

      Encoder::Settings::BitrateSpec
    Encoder::Settings::bitrateSpec() const
    {
      return d->bitrateSpec;
    }

      CommentList
    Encoder::Settings::commentList() const
    {
      return d->commentList;
    }

      unsigned int
    Encoder::Settings::nominalBitrate() const
    {
      return d->nominalBitrate;
    }

      unsigned int
    Encoder::Settings::channels() const
    {
      return d->channels;
    }

      unsigned int
    Encoder::Settings::minBitrate() const
    {
      return d->minBitrate;
    }

      unsigned int
    Encoder::Settings::maxBitrate() const
    {
      return d->maxBitrate;
    }

      unsigned int
    Encoder::Settings::bytesPerSample() const
    {
      return d->bytesPerSample;
    }

      unsigned int
    Encoder::Settings::inputBitrate() const
    {
      return d->inputBitrate;
    }

      void
    Encoder::Settings::setSerialNumber(int i)
    {
      d->serialNumber = i;
    }

      void
    Encoder::Settings::setCommentList(const CommentList & l)
    {
      d->commentList = l;
    }

      void
    Encoder::Settings::setNominalBitrate(unsigned int i)
    {
      d->nominalBitrate = i;
    }

      void
    Encoder::Settings::setBitrateRange(unsigned int min, unsigned int max)
    {
      d->minBitrate = min;
      d->maxBitrate = max;
    }

      void
    Encoder::Settings::setChannels(unsigned int i)
    {
      d->channels = i;
    }

      void
    Encoder::Settings::setBytesPerSample(unsigned int i)
    {
      d->bytesPerSample = i;
    }

      void
    Encoder::Settings::setInputBitrate(unsigned int i)
    {
      d->inputBitrate = i;
    }

    class Encoder::Private
    {
      public:

        Private()
          : dataSink  (0L)
        {
          // Empty.
        }

        Settings            settings;

        ::ogg_stream_state  oggStreamState;
        ::ogg_page          oggPage;
        ::ogg_packet        oggPacket;

        ::vorbis_info       vorbisInfo;
        ::vorbis_comment    vorbisComment;
        ::vorbis_dsp_state  vorbisDSPState;
        ::vorbis_block      vorbisBlock;

        VorbisDataSink    * dataSink;
    };

    Encoder::Encoder(VorbisDataSink * dataSink)
    {
      d = new Private;
      d->dataSink = dataSink;
    }

    Encoder::~Encoder()
    {
      delete d;
      d = 0;
    }

      bool
    Encoder::init(const Settings & settings)
    {
      int err = 0;

      d->settings = settings;

      ::vorbis_info_init(&d->vorbisInfo);

      if (Settings::Nominal == d->settings.bitrateSpec())
      {
        err = ::vorbis_encode_init
          (
           &d->vorbisInfo,
           d->settings.channels(),
           d->settings.inputBitrate(),
           -1,
           d->settings.nominalBitrate(),
           -1
          );
      }
      else
      {
        err = ::vorbis_encode_init
          (
           &d->vorbisInfo,
           d->settings.channels(),
           d->settings.inputBitrate(),
           d->settings.maxBitrate(),
           -1,
           d->settings.minBitrate()
          );
      }

      if (0 != err)
      {
        cerr << "vorbis_encode_init failed" << endl;
        return false;
      }

      ::vorbis_comment_init(&d->vorbisComment);

      ::vorbis_comment_add(&d->vorbisComment, "encoder=vorbis++");

      err = ::vorbis_analysis_init(&d->vorbisDSPState, &d->vorbisInfo);

      if (0 != err)
      {
        cerr << "vorbis_analysis_init failed" << endl;
        return false;
      }

      err = ::vorbis_block_init(&d->vorbisDSPState, &d->vorbisBlock);

      if (0 != err)
      {
        cerr << "vorbis_block_init failed" << endl;
        return false;
      }

      err = ::ogg_stream_init(&d->oggStreamState, d->settings.serialNumber());

      if (0 != err)
      {
        cerr << "ogg_stream_init failed" << endl;
        return false;
      }

      {
        ::ogg_packet initialHeader;
        ::ogg_packet commentHeader;
        ::ogg_packet codebookHeader;

        err = ::vorbis_analysis_headerout
          (
           &d->vorbisDSPState,
           &d->vorbisComment,
           &initialHeader,
           &commentHeader,
           &codebookHeader
          );

        if (0 != err)
        {
          cerr << "vorbis_analysis_headerout failed" << endl;
          return false;
        }

        err = ::ogg_stream_packetin(&d->oggStreamState, &initialHeader);

        if (0 != err)
        {
          cerr << "ogg_stream_packetin failed" << endl;
          return false;
        }

        err = ::ogg_stream_packetin(&d->oggStreamState, &commentHeader);

        if (0 != err)
        {
          cerr << "ogg_stream_packetin failed" << endl;
          return false;
        }

        err = ::ogg_stream_packetin(&d->oggStreamState, &codebookHeader);

        if (0 != err)
        {
          cerr << "ogg_stream_packetin failed" << endl;
          return false;
        }

        while (true)
        {
          err = ::ogg_stream_flush(&d->oggStreamState, &d->oggPage);

          if (0 == err)
            break;

          if
            (
             !d->dataSink->write
             (DataBlock(d->oggPage.header, d->oggPage.header + d->oggPage.header_len))
            )
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }

          if
            (
             !d->dataSink->write
             (DataBlock(d->oggPage.body, d->oggPage.body + d->oggPage.header_len))
            )
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }
        }
      }

      return true;
    }

      float **
    Encoder::analysisBuffer(unsigned long sampleCount)
    {
      return ::vorbis_analysis_buffer(&d->vorbisDSPState, sampleCount);
    }

      bool
    Encoder::encode(unsigned long sampleCount)
    {
      ::vorbis_analysis_wrote(&d->vorbisDSPState, sampleCount);

      while
        (1 == ::vorbis_analysis_blockout(&d->vorbisDSPState, &d->vorbisBlock))
      {
        ::vorbis_analysis(&d->vorbisBlock, &d->oggPacket);

        int err = ::ogg_stream_packetin(&d->oggStreamState, &d->oggPacket);

        if (0 != err)
        {
          cerr << "ogg_stream_packetin failed" << endl;
          return false;
        }

        bool endOfStream = false;

        while (!endOfStream)
        {
          err = ::ogg_stream_pageout(&d->oggStreamState, &d->oggPage);

          if (0 == err)
            break;

          if (!d->dataSink->write
            (DataBlock(d->oggPage.header, d->oggPage.header + d->oggPage.header_len)))
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }

          if (!d->dataSink->write
            (DataBlock(d->oggPage.body, d->oggPage.body + d->oggPage.body_len)))
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }

          if (::ogg_page_eos(&d->oggPage))
            endOfStream = true;
        }
      }

      return true;
    }

      bool
    Encoder::close()
    {
      int err = 0;
      bool endOfStream = false;

      ::vorbis_analysis_wrote(&d->vorbisDSPState, 0);

      while
        (1 == ::vorbis_analysis_blockout(&d->vorbisDSPState, &d->vorbisBlock))
      {
        ::vorbis_analysis(&d->vorbisBlock, &d->oggPacket);

        err = ::ogg_stream_packetin(&d->oggStreamState, &d->oggPacket);

        if (0 != err)
        {
          cerr << "ogg_stream_packetin failed" << endl;
          return false;
        }

        while (!endOfStream)
        {
          err = ::ogg_stream_pageout(&d->oggStreamState, &d->oggPage);

          if (0 == err)
            break;

          if
            (
             !d->dataSink->write
             (DataBlock(d->oggPage.header, d->oggPage.header + d->oggPage.header_len))
            )
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }

          char * body = reinterpret_cast<char *>(d->oggPage.body);

          if
            (
             !d->dataSink->write
             (DataBlock(d->oggPage.body, d->oggPage.body + d->oggPage.body_len))
            )
          {
            cerr << "Output handler did not accept data" << endl;
            return false;
          }

          if (::ogg_page_eos(&d->oggPage))
            endOfStream = true;
        }
      }

      ::ogg_stream_clear      (&d->oggStreamState);
      ::vorbis_block_clear    (&d->vorbisBlock);
      ::vorbis_dsp_clear      (&d->vorbisDSPState);
      ::vorbis_comment_clear  (&d->vorbisComment);
      ::vorbis_info_clear     (&d->vorbisInfo);

      return true;
    }

      Encoder::Settings
    Encoder::settings()
    {
      return d->settings;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
