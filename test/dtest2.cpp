// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>

#include "vorbispp/Decoder.h"
#include "vorbispp/VorbisFileDataSource.h"
#include "vorbispp/PCMPlayDataSink.h"
#include "vorbispp/Queue.h"

using namespace std;

int main(int argc, char ** argv)
{
  if (2 != argc)
  {
    cerr << "Usage: " << argv[0] << " <input>" << endl;
    return 1;
  }

  using namespace Ogg::Vorbis;

  // This object grabs vorbis data from a file. We don't open it here -
  // we just pass it to a decoder and then the decoder opens it when
  // we ask the decoder to open the input.

  VorbisFileDataSource  dataSource;

  // This object plays PCM data to an audio device. As above, we don't
  // try to open it here - the object which is writing to it will try
  // to open it itself.

  PCMPlayDataSink       dataSink;

  // This object sits between dataSource and dataSink, buffering
  // the data. It lives in a thread, to make things nice and smooth.
  // The second argument attaches the output to the dataSink object
  // created above.

  // We tell the queue that it may hold up to 128 DataBlocks.

  Queue                 dataQueue (128, &dataSink);

  // The decoder ctor takes two arguments - a DataSource * and a
  // DataSink *. Notice we pass the dataQueue object as the DataSink.

  Decoder               decoder   (&dataSource, &dataQueue);

  // Options to pass to the output device.

  OptionMap optionMap;
  
//  optionMap["sampleRate"] = "22050";
//  optionMap["hello"] = "blah";

  // Now ask the decoder to open its input and output.

  if (!decoder.openInput(argv[1]))
  {
    cerr << "Couldn't load track: " << argv[1] << endl;
    return 1;
  }

  if (!decoder.openOutput("", optionMap))
  {
    cerr << "Couldn't open output device" << endl;
    return 1;
  }

  // Find out the length of the decoder's current track.

  double trackLength = decoder.length();

  double trackPosition = 0.0;

  const unsigned int bufSize = 4096;

  // While we haven't reached the end of the current track...

  while (trackPosition < trackLength)
  {
    unsigned long bytesRead;
    double        time;
    long          bitRate;

    // Ask the decoder to read. It will read from its DataSource
    // and write to its DataSink. Perhaps read() should be renamed
    // to transfer() ?

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
