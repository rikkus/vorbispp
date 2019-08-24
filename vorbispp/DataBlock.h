// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#ifndef OGG_VORBIS_PLUS_PLUS_DATA_BLOCK_H
#define OGG_VORBIS_PLUS_PLUS_DATA_BLOCK_H

#include <vector>
#include <string.h> // For memcpy.

#include "vorbispp/OptionMap.h"

namespace Ogg
{
  namespace Vorbis
  {
    typedef vector<char> DataBlock;
#if 0
    class DataBlock 
    {
      public:

        DataBlock()
          : data_   (0L),
            length_ (0L)
        {
        }

        DataBlock(const DataBlock & other)
        {
          data_   = new char[other.length_];
          length_ = other.length_;

          ::memcpy(data_, other.data_, length_);
        }

        DataBlock & operator = (const DataBlock & other)
        {
          if (this == &other)
            return *this;

          data_   = new char[other.length_];
          length_ = other.length_;

          ::memcpy(data_, other.data_, length_);

          return *this;
        }

        DataBlock
          (
           const char * data,
           unsigned long length
          )
          : length_(length)
        {
          ::memcpy(data_, data, length);
        }

        DataBlock
          (
           const unsigned char * data,
           unsigned long length
          )
          : length_(length)
        {
          ::memcpy(data_, data, length);
        }

        DataBlock
          (
           const char * data,
           unsigned long length,
           const OptionMap & optionMap
          )
          : length_     (length),
            optionMap_  (optionMap)
        {
          ::memcpy(data_, data, length);
        }

        DataBlock
          (
           const unsigned char * data,
           unsigned long length,
           const OptionMap & optionMap
          )
          : length_     (length),
            optionMap_  (optionMap)
        {
          ::memcpy(data_, data, length);
        }
        virtual ~DataBlock()
        {
          delete [] data_;
        }

        const char *  data()      const { return data_;       }
        unsigned long length()    const { return length_;     }
        OptionMap     optionMap() const { return optionMap_;  }

      private:

        char          * data_;
        unsigned long   length_;
        OptionMap       optionMap_;
    };
#endif
  }
}

#endif
// vim:ts=2:sw=2:tw=78:et
