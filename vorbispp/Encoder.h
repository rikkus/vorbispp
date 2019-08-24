// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_ENCODER_H
#define OGG_VORBIS_PLUS_PLUS_ENCODER_H

#include <sys/types.h> // For int64_t.

#include "vorbispp/CommentList.h"

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisDataSink;

    /**
     * Encodes Vorbis data.
     */
    class Encoder
    {
      public:

        class Settings
        {
          public:

            enum BitrateSpec { Nominal, Range };

            Settings();

            ~Settings();

            Settings
              (
               int                   serialNumber,
               unsigned int          nominalBitrate,
               unsigned int          channels            = 2,
               unsigned int          bytesPerSample      = 2,
               unsigned int          inputBitrate        = 44100,
               const CommentList  &  commentList         = CommentList()
              );

            Settings
              (
               int                   serialNumber,
               unsigned int          minBitrate,
               unsigned int          maxBitrate,
               unsigned int          channels            = 2,
               unsigned int          bytesPerSample      = 2,
               unsigned int          inputBitrate        = 44100,
               const CommentList  &  commentList         = CommentList()
              );

            Settings(const Settings &);
            Settings & operator = (const Settings &);
 
            int           serialNumber()    const;
            BitrateSpec   bitrateSpec()     const;
            CommentList   commentList()     const;
            unsigned int  nominalBitrate()  const;
            unsigned int  channels()        const;
            unsigned int  minBitrate()      const;
            unsigned int  maxBitrate()      const;
            unsigned int  bytesPerSample()  const;
            unsigned int  inputBitrate()    const;

            void setSerialNumber    (int);
            void setCommentList     (const CommentList &);
            void setNominalBitrate  (unsigned int);
            void setBitrateRange    (unsigned int min, unsigned int max);
            void setChannels        (unsigned int);
            void setBytesPerSample  (unsigned int);
            void setInputBitrate    (unsigned int);

          private:

            class Private;
            Private * d;
        };

        Encoder(VorbisDataSink *);
        virtual ~Encoder();

        bool init(const Settings &);

        virtual float ** analysisBuffer(unsigned long sampleCount);

        virtual bool encode(unsigned long sampleCount);

        bool close();

        Settings settings();

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
