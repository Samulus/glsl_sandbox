/*
 * filebrowser.cc
 * Author: Samuel Vargas
 */

#include "filebrowser.h"

FileBrowser::FileBrowser(const std::string& path) {
   this->path = path;
}

std::vector<std::string> FileBrowser::ls() const {
   tinydir_dir dir;
   tinydir_open(&dir, this->path.c_str());

   std::vector<std::string> fileListing;

   while (dir.has_next) {
      tinydir_file file;
      tinydir_readfile(&dir, &file);
      if (file.is_dir)
         fileListing.push_back(std::string(file.name) + "/");
      tinydir_next(&dir);
   }
   tinydir_close(&dir);

   return fileListing;
}
