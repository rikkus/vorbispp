// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_COMMENT_LIST_H
#define OGG_VORBIS_PLUS_PLUS_COMMENT_LIST_H

namespace Ogg
{
  namespace Vorbis
  {
    /**
     * Encapsulates a list of comments.
     */
    class CommentList
    {
      public:

        CommentList();
        virtual ~CommentList();

      private:

        class Private;
        Private * d;
    };
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
