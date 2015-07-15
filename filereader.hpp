#ifndef __FILEREADER_HPP__
#define __FILEREADER_HPP__
#include <vector>

std::string readFile(const std::string &path);
std::vector<std::string> getFileList(const std::string &path);

#endif