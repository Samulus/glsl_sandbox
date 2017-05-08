/*
 * util_lua.h
 * Author: Samuel Vargas
 * Date: 05/04/2017
 */

#pragma once
#include <iostream>
#include <vector>
#include "sol.h"

template <typename T>
std::vector<T> tableToVector(sol::table table) {
   std::vector<T> output;
   for (size_t i=1; i <= table.size(); ++i) {
      output.push_back((T)table[i]);
   }
   return output;
}

template <typename T>
sol::table arrayToTable(const T* array, size_t n) {
   sol::table output;
   for (size_t i=0; i < n; ++i) {
      output[i+1] = array[i];
   }
   return output;
}

namespace Lua {
   template <typename T>
   void throwIfMissingArgument(const sol::table& table, std::string arg) {
      sol::optional<T> argumentExists = table[arg];
      if (!argumentExists) {
         std::runtime_error("Expected Argument: %s, \n"
                            "It was missing or the wrong data type.");
      }
   }
}
