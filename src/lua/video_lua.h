/*
 * video_lua.h
 * Author: Samuel Vargas
 */

#pragma once
#include "sol.h"
#include "video.h"

namespace VideoWrapper {
   void bind(sol::state&, const Video& );
}
