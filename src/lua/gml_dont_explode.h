/*
 * gml_dont_explode.h
 * Author: Samuel Vargas
 * Date: 06/05/2017
 *
 * Template specializations to prevent sol2 from exploding
 * when it tries to return or use any of the datatypes in gml.
 */

#pragma once
#include "sol.h"
#include "gml.hpp"

template <> struct sol::is_container<gml::vec2> : std::false_type {};
template <> struct sol::is_container<gml::vec3> : std::false_type {};
template <> struct sol::is_container<gml::vec4> : std::false_type {};
template <> struct sol::is_container<gml::mat4> : std::false_type {};
