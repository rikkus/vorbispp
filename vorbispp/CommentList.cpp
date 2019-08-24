// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/CommentList.h"

namespace Ogg
{
  namespace Vorbis
  {
    class CommentList::Private
    {
      public:

        Private()
        {
        }

        ~Private()
        {
        }
    };

    CommentList::CommentList()
    {
      d = new Private;
    }

    CommentList::~CommentList()
    {
      delete d;
      d = 0;
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
