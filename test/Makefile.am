INCLUDES = $(all_includes) -I$(top_srcdir)

LIBVORBISPP = $(top_builddir)/vorbispp/libvorbispp.la

noinst_PROGRAMS = decodertest encodertest dtest2

decodertest_SOURCES = decodertest.cpp
decodertest_LDFLAGS = $(all_libraries)
decodertest_LDADD = $(LIBVORBISPP)

encodertest_SOURCES = encodertest.cpp
encodertest_LDFLAGS = $(all_libraries)
encodertest_LDADD = $(LIBVORBISPP)

dtest2_SOURCES = dtest2.cpp
dtest2_LDFLAGS = $(all_libraries)
dtest2_LDADD = $(LIBVORBISPP)
