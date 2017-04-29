/*
 * error.h
 * Author: Samuel Vargas
 * Date: 04/17/2017
 */

#pragma once
#include <iostream>

class SDL_Exception : public std::runtime_error {
   public:
      SDL_Exception(std::string msg) : std::runtime_error(msg) {} 
};

class GL_Exception : public std::runtime_error {
   public:
      GL_Exception(std::string msg) : std::runtime_error(msg) {}
};
