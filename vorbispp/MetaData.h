// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_META_DATA_H
#define OGG_VORBIS_PLUS_PLUS_META_DATA_H

namespace Ogg
{
  namespace Vorbis
  {
    class MetaData
    {
      public:

        MetaData();
        MetaData(long time, long bitRate, long tag = 0L);
        virtual ~MetaData();

        long time()     const;
        long bitRate()  const;
        long tag()      const;

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
