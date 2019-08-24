// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "vorbispp/Encoder.h"
#include "vorbispp/VorbisFileDataSink.h"

using namespace std;

void toFloat
(
 const char * buf,
 float ** buffer,
 unsigned long samples,
 unsigned int channels,
 unsigned int bytesPerSample,
 bool bigEndian
)
{
  if (1 == bytesPerSample)
  {
    unsigned char *bufu = (unsigned char *)buf;

    for (int i = 0; i < samples; i++)
    {
      for (int j = 0; j < channels; j++)
      {
        buffer[j][i] = ((int)(bufu[i * channels + j]) - 128) / 128.0f;
      }
    }
  }
  else
  {
    if (!bigEndian)
    {
      for (int i = 0; i < samples; i++)
      {
        for (int j = 0; j < channels; j++)
        {
          buffer[j][i] =
            (
             (buf[i * 2 * channels + 2 * j + 1] << 8)
             |
             (buf[i * 2 * channels + 2 * j] & 0xff)
            ) / 32768.0f;
        }
      }
    }
    else
    {
      for (int i = 0; i < samples; i++)
      {
        for (int j = 0; j < channels; j++)
        {
          buffer[j][i] = 
            (
             (buf[i * 2 * channels + 2 * j] << 8)
             |
             (buf[i * 2 * channels + 2 * j + 1] & 0xff)
            ) / 32768.0f;
        }
      }
    }
  }
}

int main(int argc, char ** argv)
{
  if (3 != argc)
  {
    cerr << "Usage: " << argv[0] << " <input> <output>" << endl;
    return 1;
  }

  FILE * input;

  if (0 != strncmp(argv[1], "-", 1))
  {
    input = ::fopen(argv[1], "r");

    if (0 == input)
    {
      cerr << "Can't open input file `" << argv[1] << "'" << endl;
      return 1;
    }
  }
  else
  {
    input = stdin;
  }

  Ogg::Vorbis::VorbisFileDataSink dataSink;
  Ogg::Vorbis::OptionMap optionMap;

  if (!dataSink.open(argv[2], optionMap))
  {
    cerr << "Can't open output file " << argv[2] << endl;
    return 1;
  }

  Ogg::Vorbis::Encoder encoder(&dataSink);

  Ogg::Vorbis::Encoder::Settings settings;

  bool ok = encoder.init(settings);

  if (!ok)
  {
    cerr << "encoder.init failed" << endl;
    return 1;
  }

  const unsigned int channels = 2;
  const unsigned int bitsPerSample = 16;
  const unsigned int bytesPerSample = bitsPerSample / 8;
  bool bigEndian = false;

  const unsigned long bufSizeSamples = 4096;
  const unsigned long cbufSizeBytes =
    bufSizeSamples * channels * bytesPerSample;

  char * cbuf = new char[cbufSizeBytes];

  while (0 == ::feof(input))
  {
    float ** fbuf = encoder.analysisBuffer(bufSizeSamples);

    size_t bytesRead = ::fread(cbuf, 1, cbufSizeBytes, input);

    if (0 == bytesRead)
    {
      cerr << "bytesRead is 0" << endl;
      break;
    }

    unsigned long samplesRead = bytesRead / (channels * bytesPerSample);

    for (int i = 0; i < samplesRead; i++)
    {
      for (int j = 0; j < channels; j++)
      {
        fbuf[j][i] =
          (
           (cbuf[i * 2 * channels + 2 * j + 1] << 8)
           |
           (cbuf[i * 2 * channels + 2 * j] & 0xff)
          ) / 32768.0f;
      }
    }

    ok = encoder.encode(samplesRead);

    if (!ok)
    {
      cerr << "encode failed" << endl;
      return 1;
    }
  }

  ok = encoder.close();

  if (!ok)
  {
    cerr << "encoder.close failed" << endl;
    return 1;
  }

  ok = dataSink.close();

  if (!ok)
  {
    cerr << "dataSink.close failed" << endl;
    return 1;
  }

  return 0;
}

// vim:ts=2:sw=2:tw=78:et
