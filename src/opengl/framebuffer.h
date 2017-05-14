/*
 * framebuffer.h
 * Author: Samuel Vargas
 * Date: 05/04/2017
 *
 * The framebuffer represents an on (or offscreen)
 * target for directing all OpenGL rendering calls to.
 * You can use this module for implementing deferred
 * lighting or other post processing effects in your
 * creations.
 */

#pragma once

#include <glew.h>
#include <iostream>
#include "gpubuffer.h"
#include "video.h"

class Framebuffer {
   private:
      GLuint fbo, rbo;
      std::vector<GLuint> textures, attachments;
      GPUBuffer buffer;
      const Video& video;
   public:
      Framebuffer();
      void bind();
      void unbind();
      void addTexture(sol::table);
};
