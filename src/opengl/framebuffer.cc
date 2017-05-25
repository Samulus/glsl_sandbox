/*
 * framebuffer.cc
 * Author: Samuel Vargas
 * Date: 05/04/2017
 *
 * The framebuffer represents an on (or offscreen)
 * target for directing all OpenGL rendering calls to.
 * You can use this module for implementing deferred
 * lighting or other post processing effects in your
 * creations.
 */

#include <SDL.h>
#include "framebuffer.h"
#include "util.h"
#include "video.h"

Framebuffer::Framebuffer() :
   buffer(GPUBuffer(4, std::vector<GLVec>{GLVec::Vec3, GLVec::Vec2})),
   video(Video::getInstance()) {
   /// init fbo
   glGenFramebuffers(1, &this->fbo);
   glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
   /// init rbo
   glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, video.width(), video.height());
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
}

void Framebuffer::bind() {
   glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
   glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
}

void Framebuffer::unbind() {
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::render() {
}

/*
 * Appends and binds a new fullscreen texture for offscreen
 * rendering / post processing effects.
 */

void Framebuffer::addTexture(sol::table table) {

   /*
      table = {
         name     = 'example',
         location = 0,
         options  = {
            gpuFormat   = GL_RGB16F,
            cpuFormat   = GL_RGB,
            cpuDataType = GL_FLOAT
         },
      }
   */

   sol::optional<std::string> name = table["name"];
   sol::optional<size_t> location = table["location"];
   sol::optional<sol::table> options = table["options"];

   if (!name || !location || !options) {
      SDL_Log("gpuFormat:   %d\n", (bool)name);
      SDL_Log("cpuFormat:   %d\n", (bool)location);
      SDL_Log("cpuDataType: %d\n", (bool)options);
      throw std::runtime_error("Missing Argument");
   }

   sol::optional<size_t> gpuFormat   = table["options"]["gpuFormat"];
   sol::optional<size_t> cpuFormat   = table["options"]["cpuFormat"];
   sol::optional<size_t> cpuDataType = table["options"]["cpuDataType"];

   if (!gpuFormat || !cpuFormat || !cpuDataType) {
      SDL_Log("gpuFormat:   %d\n", (bool)gpuFormat);
      SDL_Log("cpuFormat:   %d\n", (bool)cpuFormat);
      SDL_Log("cpuDataType: %d\n", (bool)cpuDataType);
      throw std::runtime_error("Missing Argument");
   }

   /// create fullscreen texture with specified cpu / gpu formats
   this->textures.push_back(0);
   glGenTextures(1, &this->textures.back());
   glBindTexture(GL_TEXTURE_2D, this->textures.back());
   glTexImage2D(GL_TEXTURE_2D, 0, gpuFormat.value(),
                video.width(), video.height(), 0, cpuFormat.value(), cpuDataType.value(), NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   /// ensure user's gpu is allowed to create another GL_COLOR_ATTACHMENTN
   int colorAttachment = GL_COLOR_ATTACHMENT0 + this->attachments.size();
   assert(colorAttachment >= GL_COLOR_ATTACHMENT0  &&
          colorAttachment <= GL_COLOR_ATTACHMENT15 &&
          strFormat("OpenGL only supports %d GL_COLOR_ATTACHMENTS", GL_MAX_COLOR_ATTACHMENTS).c_str());

   /// append to list of color attachments and update
   this->attachments.push_back(colorAttachment);
   glFramebufferTexture2D(GL_FRAMEBUFFER, colorAttachment, GL_TEXTURE_2D, this->textures.back(), 0);
   glDrawBuffers(this->attachments.size(), &this->attachments[0]);
}
