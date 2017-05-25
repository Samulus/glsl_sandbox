/*
 * video_lua.cc
 * Author: Samuel Vargas
 */

#include "video_lua.h"
#include "video.h"

static const Video* video = nullptr;

void VideoWrapper::bind(sol::state& state, const Video& v) {
   video = &v;

   auto videoTable = state.create_named_table("video");
   videoTable["present"]     = [&] { video->present(); };
   videoTable["setViewport"] = [&] { video->setViewport(); };
   videoTable["clear"]       = [&] (float r, float g, float b) { video->clear(r,g,b); };
}
