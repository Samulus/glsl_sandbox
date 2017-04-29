/*
 * lua_test.cc
 * Author: Samuel Vargas
 * Date: 04/29/2017
 */

#include "sol.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE("Call method from C++", "[lua]") {

   struct Rect {
      private:
         double x,y,w,h;
      public:
         Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}
         double width() const {
            return w;
         }
         double height() const {
            return h;
         }
         double area() const {
            return w * h;
         }
   };

   // bind Rect class to Lua
   sol::state lua;
   lua.open_libraries(sol::lib::base, sol::lib::package);
   lua.new_usertype<Rect>("Rect",  sol::constructors<Rect(double, double, double, double)>(),
                                   /* Methods */
                                   "width",  &Rect::width,
                                   "height", &Rect::height,
                                   "area",   &Rect::area);

   WHEN("Rect methods are invoked") {
      lua.script("r = Rect.new(32,64,128,256)");
      lua.script("width  = r:width()");
      lua.script("height = r:height()");
      lua.script("area   = r:area()");
      double width  = lua["width"].get_or<double>(-1);
      double height = lua["height"].get_or<double>(-1);
      double area   = lua["area"].get_or<double>(-1);
      REQUIRE(width  == 128);
      REQUIRE(height == 256);
      REQUIRE(area == (128 * 256));
   }
}
