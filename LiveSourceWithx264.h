/*===============================================================================

  Project: H264LiveStreamer
  Module: LiveSourceWithx264.h

  Copyright (c) 2014-2015, Rafael Palomar <rafaelpalomaravalos@gmail.com>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

  =============================================================================*/

#ifndef __LIVE_SOURCE_WITH_X264_H
#define __LIVE_XOURCE_WITH_X264_H

#include "x264Encoder.h"

#include <queue>
#include <opencv2/opencv.hpp>
#include <FramedSource.hh>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <malloc.h>

#include "capture.h"

class LiveSourceWithx264:public FramedSource
{
 public:
  static LiveSourceWithx264* createNew(UsageEnvironment& env);
  static EventTriggerId eventTriggerId;
 protected:
  LiveSourceWithx264(UsageEnvironment& env);
  virtual ~LiveSourceWithx264(void);
 private:
  virtual void doGetNextFrame();
  static void deliverFrame0(void* clientData);
  void deliverFrame();
  void encodeNewFrame();
  static unsigned referenceCount;
  std::queue<x264_nal_t> nalQueue;
  timeval currentTime;
  // videoCaptureDevice is my BGR data source. You can have according to your need
  struct camera *cam = NULL;
  //uint8_t * yuv_frame
  // Remember the x264 encoder wrapper we wrote in the start
  x264Encoder *encoder;
};

#endif
