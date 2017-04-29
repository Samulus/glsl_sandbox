/*
 * lua_test.cc
 * Author: Samuel Vargas
 * Date: 04/29/2017
 */

#include "sol.h"

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

TEST_CASE ("sol2", "[lua]") {

   WHEN("Hello World") {
       sol::state lua;
       lua.open_libraries(sol::lib::base, sol::lib::package);
       lua.script( "print('bark bark bark!')" );
   }
}
