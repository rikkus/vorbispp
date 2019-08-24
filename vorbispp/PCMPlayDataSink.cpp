// Copyright (C) 2001 Rik Hemsley (rikkus) <rik@kde.org>
//
// BSD license. See COPYING.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h> // For strtoul

#include "vorbispp/PCMPlayDataSink.h"
#include "vorbispp/MetaData.h"
#include "aopp/AOPP.h"

using namespace std;

namespace Ogg
{
  namespace Vorbis
  {
    class PCMPlayDataSink::Private
    {
      public:

        Private()
          : manager(0L)
        {
        }

        AudioOutput::Manager  * manager;
        AudioOutput::Device   * device;
    };

    PCMPlayDataSink::PCMPlayDataSink()
      : PCMDataSink()
    {
      d = new Private;
      d->manager = new AudioOutput::Manager;
    }

    PCMPlayDataSink::~PCMPlayDataSink()
    {
      assert(d->manager);

      delete d->manager;
      d->manager = 0;

      delete d;
      d = 0;
    }

      bool
    PCMPlayDataSink::open(const string & url, const OptionMap & optionMap)
    {
      assert(d->manager);

      if (0 != d->device)
      {
        cerr << "PCMPlayDataSink: already have a device open" << endl;
        return false;
      }

      // Sample format...

      AudioOutput::SampleFormat sampleFormat;

      // Take defaults from SampleFormat object.

      unsigned int bitsPerSample          = sampleFormat.bitsPerSample();
      unsigned int sampleRate             = sampleFormat.sampleRate();
      unsigned int channelCount           = sampleFormat.channelCount();
      AudioOutput::Endianness endianness  = sampleFormat.endianness();

      AudioOutput::OptionMap aoOptionMap;

      OptionMap::const_iterator it;

      for (it = optionMap.begin(); it != optionMap.end(); ++it)
      {
        string key    ((*it).first);
        string value  ((*it).second);

        if (string("bitsPerSample") == key)
        {
          sampleFormat.setBitsPerSample(strtoul(value.c_str(), 0, 10));
          continue;
        }

        if (string("sampleRate") == key)
        {
          sampleFormat.setSampleRate(strtoul(value.c_str(), 0, 10));
          continue;
        }

        if (string("channelCount") == key)
        {
          sampleFormat.setChannelCount(strtoul(value.c_str(), 0, 10));
          continue;
        }

        if (string("endianness") == key)
        {
          sampleFormat.setEndianness
            (
             string("big") == value
             ?
             AudioOutput::EndianBig
             :
             AudioOutput::EndianLittle
            );

          continue;
        }

        aoOptionMap[key] = value;
      }

      AudioOutput::DriverInfo info;

      if (url.empty())
      {
        if (!d->manager->haveDefaultDriver())
        {
          cerr << "PCMPlayDataSink: no default driver" << endl;
          return false;
        }
        else
        {
          cerr << "PCMPlayDataSink: using default driver" << endl;
          info = d->manager->defaultDriver();
        }
      }
      else
      {
        list<AudioOutput::DriverInfo> driverInfoList =
          d->manager->driverInfoList();

        list<AudioOutput::DriverInfo>::const_iterator it;

        for (it = driverInfoList.begin(); it != driverInfoList.end(); ++it)
        {
          if ((*it).shortName() == url)
          {
            info = *it;
            break;
          }
        }
      }

      cerr << "PCMPlayDataSink: Driver name: " << info.shortName() << endl;

      cerr << "Sample format: " << sampleFormat.bitsPerSample()
        << ":" << sampleFormat.sampleRate()
        << ":" << sampleFormat.channelCount() << endl;

      AudioOutput::Device * dev =
        d->manager->open(info, aoOptionMap, sampleFormat);

      if (0 == dev)
      {
        cerr << "PCMPlayDataSink: can't open device" << endl;
        return false;
      }

      d->device = dev;

      return true;
    }

      bool
    PCMPlayDataSink::close()
    {
      assert(d->manager);

      delete d->device;
      d->device = 0;

      return true;
    }

      bool
    PCMPlayDataSink::write(const DataBlock & dataBlock)
    {
      assert(d->manager);

      if (0 == d->device)
      {
        cerr << "PCMPlayDataSink: device is not open" << endl;
        return false;
      }

      char blah[dataBlock.size()];

      copy(dataBlock.begin(), dataBlock.end(), blah);

      return d->device->play(blah, dataBlock.size());
    }
  }
}

// vim:ts=2:sw=2:tw=78:et
