/*
 * glmodel.cc
 * Author: Samuel Vargas
 * Date: 05/03/2017
 *
 * Models are wrappers around tinyobj + friends
 * and represent a single object that can be rendered
 * onscreen
 */

#include "glmodel.h"

GLModel::GLModel(std::string name) {
   this->name = name;
}
