/*
 * script.h
 * Author: Samuel Vargas
 * Date: 05/04/2017
 */

#pragma once
#include "sol.h"
#include "video.h"
#include <iostream>

class Script {
   private:
      sol::state lua;
   public:
      Script(const std::string&, const Video&);
      sol::global_table operator[](std::string key) const;

      template <typename... T>
      std::tuple<T...> fn(std::string key) {
         return this->lua[key]();
      }
};
