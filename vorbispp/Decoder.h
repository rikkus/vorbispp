// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_DECODER_H
#define OGG_VORBIS_PLUS_PLUS_DECODER_H

#include <sys/types.h> // For int64_t.

#include <string>

#include "vorbispp/OptionMap.h"

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisDataSource;
    class DataSink;

    /**
     * Decodes Vorbis data.
     */
    class Decoder
    {
      public:

        /**
         * @param dataSource Used for retrieving Vorbis data.
         */
        Decoder(VorbisDataSource * dataSource, DataSink * dataSink);

        virtual ~Decoder();

        /**
         * Open a Vorbis data source (e.g. file)
         */
        virtual bool    openInput(const string & url);

        /**
         * Open a data sink (e.g. file)
         */
        virtual bool    openOutput(const string & url, const OptionMap &);

        /**
         * Close the current data source. Usually not needed.
         */
        virtual void    close();

        /**
         * @return Version of the data source in use.
         */
        virtual int     version()   const;

        /**
         * @return Number of channels of the data source in use.
         */
        virtual int     channels()  const;

        /**
         * @return Bitrate of the data source in use.
         */
        virtual long    rate()      const;

        /**
         * @return Length (time) of the data source in use.
         */
        virtual double  length()    const;

        /**
         * Seek to a location.
         * @param pos byte offset.
         */
        bool rawSeek      (long     pos);

        /**
         * Seek to a location.
         * @param pos sample offset.
         */
        bool pcmSeek      (int64_t  pos);

        /**
         * Seek to the nearest page to pos.
         * @param pos sample offset.
         */
        bool pcmSeekPage  (int64_t  pos);

        /**
         * Seek to a location.
         * @param pos seconds offset.
         */
        bool timeSeek     (double   pos);

        /**
         * Seek to the nearest page to pos.
         * @param pos seconds offset.
         */
        bool timeSeekPage (double   pos);

        /**
         * @return current offset in bytes.
         */
        int64_t rawTell()   const;

        /**
         * @return current offset in samples.
         */
        int64_t pcmTell()   const;

        /**
         * @return current offset in seconds.
         */
        double  timeTell()  const;

        /**
         * Read (and decode) a chunk of Vorbis data to audio.
         *
         * @param buf An allocated block of memory which will be filled
         * with decoded audio.
         *
         * @param maxBytes The maximum number of bytes that you want to
         * be read by this call. More than the allocated size of buf is
         * asking for trouble.
         *
         * @param bytesRead Return value - number of bytes actually read
         * from the data source.
         *
         * @param time Return value - time offset of data source after
         * decoding has been performed.
         *
         * @param bitRate Return value - average bit rate of the data
         * that has been decoded by this call.
         */
        virtual bool read
          (
           unsigned long    maxBytes,
           unsigned long  & bytesRead,
           double         & time,
           long           & bitRate,
           long             tag = 0
          );

      private:

        Decoder(const Decoder &);
        Decoder & operator = (const Decoder &);

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
