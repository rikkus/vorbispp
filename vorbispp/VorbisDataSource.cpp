// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include "vorbispp/VorbisDataSource.h"

#include <vorbis/vorbisfile.h>

#include <string.h> // For memset.

namespace Ogg
{
  namespace Vorbis
  {
    class VorbisDataSourceProxy
    {
      public:

        VorbisDataSourceProxy(VorbisDataSource * ds);
        ~VorbisDataSourceProxy();
        
        OggVorbis_File * vorbisFile();

        bool    open  ();
        size_t  read  (void * ptr, size_t size, size_t nmemb);
        int     seek  (int64_t offset, int whence);
        int     close ();
        long    tell  ();

      private:

        VorbisDataSource  * dataSource_;
        OggVorbis_File      vorbisFile_;
    };
  }
}

extern "C"
{
    static size_t
  ogg_vorbis_plus_plus_data_source_read
  (
   void     * ptr,
   size_t     size,
   size_t     nmemb,
   void     * obj
  )
  {
    Ogg::Vorbis::VorbisDataSourceProxy * source =
      reinterpret_cast<Ogg::Vorbis::VorbisDataSourceProxy *>(obj);

    return source->read(ptr, size, nmemb);
  }

    static int
  ogg_vorbis_plus_plus_data_source_seek
  (
   void     * obj,
   int64_t    offset,
   int        whence
  )
  {
    Ogg::Vorbis::VorbisDataSourceProxy * source =
      reinterpret_cast<Ogg::Vorbis::VorbisDataSourceProxy *>(obj);

    return source->seek(offset, whence);
  }

    static int
  ogg_vorbis_plus_plus_data_source_close(void * obj)
  {
    Ogg::Vorbis::VorbisDataSourceProxy * source =
      reinterpret_cast<Ogg::Vorbis::VorbisDataSourceProxy *>(obj);

    return source->close();
  }

    static long
  ogg_vorbis_plus_plus_data_source_tell(void * obj)
  {
    Ogg::Vorbis::VorbisDataSourceProxy * source =
      reinterpret_cast<Ogg::Vorbis::VorbisDataSourceProxy *>(obj);

    return source->tell();
  }
}

namespace Ogg
{
  namespace Vorbis
  {

    VorbisDataSourceProxy::VorbisDataSourceProxy(VorbisDataSource * ds)
      : dataSource_(ds)
    {
      memset(&vorbisFile_, 0, sizeof(::OggVorbis_File));
    }

    VorbisDataSourceProxy::~VorbisDataSourceProxy()
    {
      ::ov_clear(&vorbisFile_);
    }

      OggVorbis_File *
    VorbisDataSourceProxy::vorbisFile()
    {
      return &vorbisFile_;
    }

      bool
    VorbisDataSourceProxy::open()
    {
      ::ov_callbacks callbacks;

      callbacks.read_func   = ogg_vorbis_plus_plus_data_source_read;
      callbacks.seek_func   = ogg_vorbis_plus_plus_data_source_seek;
      callbacks.close_func  = ogg_vorbis_plus_plus_data_source_close;
      callbacks.tell_func   = ogg_vorbis_plus_plus_data_source_tell;

      int err =
        ::ov_open_callbacks(this, &(vorbisFile_), 0, 0, callbacks);

      if (err < 0)
      {
        cerr << "ov_open_callbacks failed" << endl;
        return false;
      }

      return true;
    }

      size_t
    VorbisDataSourceProxy::read(void * ptr, size_t size, size_t nmemb)
    {
      unsigned long len(size * nmemb);
      cerr << "VorbisDataSourceProxy::read " << len << endl;

      char * p = reinterpret_cast<char *>(ptr);

      DataBlock block = dataSource_->read(len);

      copy(block.begin(), block.end(), p);

      cerr << "VorbisDataSourceProxy::read  -> " << block.size() << endl;

      copy_n(block.begin(), 4, ostream_iterator<char>(cout));

      return block.size() / size;
    }

      int
    VorbisDataSourceProxy::seek(int64_t offset, int whence)
    {
      cerr << "VorbisDataSourceProxy::seek -> " << offset << endl;

      switch (whence)
      {
        case SEEK_SET:
          return dataSource_->seek(offset) ? 0 : -1;
          break;

        case SEEK_CUR:
          return dataSource_->seek(dataSource_->position() + offset) ? 0 : -1;
          break;

        case SEEK_END:
          cerr << "SEEK_END unsupported" << endl;
          return -1;
          break;

        default:
          cerr << "whence type unsupported" << endl;
          return -1;
          break;
      }
    }

      int
    VorbisDataSourceProxy::close()
    {
      cerr << "VorbisDataSourceProxy::close()" << endl;
      dataSource_->close();
      return 0;
    }

      long
    VorbisDataSourceProxy::tell()
    {
      cerr << "VorbisDataSourceProxy::tell()" << endl;
      return dataSource_->position();
    }
 
    class VorbisDataSource::Private
    {
      public:

        string url;
        VorbisDataSourceProxy * proxy;
    };

    VorbisDataSource::VorbisDataSource()
      : DataSource()
    {
      d = new Private;

      d->proxy = new VorbisDataSourceProxy(this);
    }

    VorbisDataSource::~VorbisDataSource()
    {
      delete d->proxy;
      d->proxy = 0;

      delete d;
      d = 0;
    }

      bool
    VorbisDataSource::vorbisOpen()
    {
      bool ok = d->proxy->open();
      cerr << "VorbisDataSource::vorbisOpen()" << " -> " << (ok ? "true" :
        "false") << endl;
      return ok;
    }

      OggVorbis_File *
    VorbisDataSource::vorbisFile()
    {
      return d->proxy->vorbisFile();
    }
  }
}


// vim:ts=2:sw=2:tw=78:et
