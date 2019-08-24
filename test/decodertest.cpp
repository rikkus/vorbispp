// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>

#include "vorbispp/Decoder.h"
#include "vorbispp/VorbisFileDataSource.h"
#include "vorbispp/Queue.h"
#include "vorbispp/PCMFileDataSink.h"

using namespace std;

int main(int argc, char ** argv)
{
  if (3 != argc)
  {
    cerr << "Usage: " << argv[0] << " <input> <output>" << endl;
    return 1;
  }

  Ogg::Vorbis::VorbisFileDataSource dataSource;

  Ogg::Vorbis::PCMFileDataSink dataSink;

  Ogg::Vorbis::Queue q(&dataSink);

  Ogg::Vorbis::Decoder decoder(&dataSource, &q);

  Ogg::Vorbis::OptionMap optionMap;

  if (!decoder.openInput(argv[1]))
  {
    cerr << "Couldn't load track: " << argv[1] << endl;
    return 1;
  }

  if (!decoder.openOutput(argv[2], optionMap))
  {
    cerr << "Couldn't open output file: " << argv[2] << endl;
    return 1;
  }

  double trackLength = decoder.length();

  double trackPosition = 0.0;

  const unsigned int bufSize = 4096;

  while (trackPosition < trackLength)
  {
    unsigned long bytesRead;
    double        time;
    long          bitRate;

    if (!decoder.read(bufSize, bytesRead, time, bitRate))
    {
      cerr << "Decoder failed" << endl;
      return 1;
    }

    trackPosition = time;
  }

  return 0;
}

// vim:ts=2:sw=2:tw=78:et
