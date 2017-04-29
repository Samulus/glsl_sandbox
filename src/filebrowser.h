/*
 * filebrowser.h
 * Author: Samuel Vargas
 */

#pragma once
#include "lib/tinydir.h"
#include <iostream>
#include <vector>

class FileBrowser {
   private:
      tinydir_dir directory;
      std::string path;
   public:
      FileBrowser(const std::string& path);
      std::vector<std::string> ls() const;
//std::vector<std::string> ls(const std::string& path) const;
};
