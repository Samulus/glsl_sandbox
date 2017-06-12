/*
 * gml_lua.cc
 * Author: Samuel vargas
 * Date: 06/03/2017
 */

#include "gml_lua.h"
#include "gml.hpp"
#include "sol.h"
#include "gml_dont_explode.h"
#include <iostream>
#include <sstream>
#include <string>

void GMLWrapper::bind(sol::state& lua) {
   auto gml = lua.create_named_table("gml");

   /// Vectors
   gml.new_usertype<gml::vec3>("vec3",
         sol::constructors<gml::vec3(), gml::vec3(float, float, float)>(),
         sol::meta_function::addition,       [] (const gml::vec3& lhs, const gml::vec3& rhs) { return lhs + rhs; },
         sol::meta_function::subtraction,    [] (const gml::vec3& lhs, const gml::vec3& rhs) { return lhs - rhs; },
         sol::meta_function::multiplication, sol::overload(
                                                [] (const gml::vec3& lhs, const gml::vec3& rhs) { return lhs * rhs; },
                                                [] (const gml::vec3& lhs, const float& rhs)     { return lhs * rhs; }
                                             ),
         sol::meta_function::division,       [] (const gml::vec3& lhs, const gml::vec3& rhs) { return lhs / rhs; },
         sol::meta_function::length,         [] (const gml::vec3& self) { return self.size(); },
         sol::meta_function::to_string,      [] (const gml::vec3& self) { return gml::to_string(self); },
         sol::meta_function::index,          [] (gml::vec3& self, int i) { return &self[i-1]; },
         sol::meta_function::new_index,      [] (gml::vec3& self, int i, float rhs) { return self[i-1] = rhs; }
   );

   gml.new_usertype<gml::vec4>("vec4",
         sol::constructors<gml::vec4(), gml::vec4(float, float, float, float)>(),
         sol::meta_function::addition,       [] (const gml::vec4& lhs, const gml::vec4& rhs) { return lhs + rhs; },
         sol::meta_function::subtraction,    [] (const gml::vec4& lhs, const gml::vec4& rhs) { return lhs - rhs; },
         sol::meta_function::multiplication, sol::overload(
                                                [] (const gml::vec4& lhs, const gml::vec4& rhs) { return lhs * rhs; },
                                                [] (const gml::vec4& lhs, const float& rhs)     { return lhs * rhs; }
                                             ),
         sol::meta_function::division,       [] (const gml::vec4& lhs, const gml::vec4& rhs) { return lhs / rhs; },
         sol::meta_function::length,         [] (const gml::vec4& self) { return self.size(); },
         sol::meta_function::to_string,      [] (const gml::vec4& self) { return gml::to_string(self); },
         sol::meta_function::index,          [] (gml::vec4& self, int i) -> float* { return &self[i-1]; },

         /// Assignment
         sol::meta_function::new_index,      [] (gml::vec4& self, int i, float v ) {
                                                  self[i-1] = v;
                                             }
   );

   /// Matrices
   gml.new_usertype<gml::mat4>("mat4",
         sol::constructors<gml::mat4(), gml::mat4(const float&)>(),
         sol::meta_function::addition,       [] (const gml::mat4& lhs, const gml::mat4& rhs) { return lhs + rhs; },
         sol::meta_function::multiplication, [] (const gml::mat4& lhs, const gml::mat4& rhs) { return lhs * rhs; },
         sol::meta_function::subtraction,    [] (const gml::mat4& lhs, const gml::mat4& rhs) { return lhs - rhs; },
         sol::meta_function::division,       [] (const gml::mat4& lhs, const gml::mat4& rhs) { return gml::inverse(lhs) * rhs; },
         sol::meta_function::to_string,      [] (const gml::mat4& self) {
                                                const void * address = static_cast<const void*>(&self);
                                                std::stringstream ss;
                                                ss << "Address: " << address;
                                                return ss.str() + "\nData: " + gml::to_string(self);
                                             },

         sol::meta_function::index,          [] (gml::mat4& self, int i) { return &self[i-1]; },
         sol::meta_function::new_index, sol::overload(
                                             [] (gml::mat4& self, int i, gml::vec4 rhs) {
                                                gml::vec4& mut = self[i-1];
                                                mut = rhs;
                                             },
                                             [] (gml::mat4& self, std::string op, gml::mat4& rhs) {
                                                if (op != "assign") {
                                                   assert(false && "Only 'assign' is a valid operation");
                                                }
                                                self = rhs;
                                             }
                                       ),
         "address",                          [] (const gml::mat4& self) {
                                                const void * address = static_cast<const void*>(&self);
                                                std::stringstream ss;
                                                ss << address;
                                                return ss.str();
                                             }
   );

   /// Copying Functions
   gml["deepcopy"] = sol::overload(
         [] (gml::mat4 copy) { return copy; }
   );

   /// Matrix Functions
   gml["perspective"] = [] (float fov, float aspect, float near, float far) -> gml::mat4 {
      return gml::perspective(fov, aspect, near, far);
   };

   gml["lookAt"] = [] (gml::vec3 eye, gml::vec3 center, gml::vec3 up) {
      return gml::lookAt(eye, center, up);
   };

   gml["transpose"] = [] (gml::mat4 mat) {
      return gml::transpose(mat);
   };

   gml["rotate"]    = [] (const gml::vec3 factor) -> gml::mat4 { return gml::rotate(factor); };
   gml["translate"] = [] (gml::vec3 factor) -> gml::mat4 { return gml::translate(factor); };
   gml["scale"]     = [] (gml::vec3 factor) -> gml::mat4 { return gml::scale(factor); };

   /// Bleh
   auto cc = lua.create_named_table("cc");
   cc["float"]      = [] (float f) -> float* { float *out = new float(f); return out; };
}
