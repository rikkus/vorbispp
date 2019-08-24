INCLUDES = @VORBIS_CFLAGS@ @AOPP_CXXFLAGS@

lib_LTLIBRARIES = libvorbispp.la

libvorbispp_la_SOURCES = \
  DataSource.cpp \
  VorbisDataSource.cpp \
  VorbisFileDataSource.cpp \
  PCMDataSource.cpp \
  PCMFileDataSource.cpp \
  Decoder.cpp \
  Encoder.cpp \
  CommentList.cpp \
  DataSink.cpp \
  VorbisDataSink.cpp \
  VorbisFileDataSink.cpp \
  PCMDataSink.cpp \
  PCMNullDataSink.cpp \
  PCMFileDataSink.cpp \
  PCMPlayDataSink.cpp \
  Filter.cpp \
  Queue.cpp \
  MetaData.cpp

libvorbispp_la_LIBADD   = \
  @VORBISFILE_LIBS@ \
  @VORBISENC_LIBS@ \
  @VORBIS_LIBS@ \
  @AOPP_LIBS@

include_HEADERS = \
  DataSource.h \
  VorbisDataSource.h \
  VorbisFileDataSource.h \
  PCMDataSource.h \
  PCMFileDataSource.h \
  Decoder.h \
  Encoder.h \
  CommentList.h \
  DataSink.h \
  VorbisDataSink.h \
  VorbisFileDataSink.h \
  PCMDataSink.h \
  PCMNullDataSink.h \
  PCMFileDataSink.h \
  PCMPlayDataSink.h \
  Filter.h \
  Queue.h \
  MetaData.h

includedir = $(prefix)/include/vorbispp

