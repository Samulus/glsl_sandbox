/*
 * glmodel.h
 * Author: Samuel Vargas
 * Date: 05/03/2017
 *
 * Models are wrappers around tinyobj + friends
 * and represent a single object that can be rendered
 * onscreen
 */

#pragma once
#include "tiny_obj_loader.h"
#include "objwavefront.h"
#include <iostream>

#pragma once
class GLModel {
   private:
      std::string name;
   public:
      GLModel(std::string);
};
