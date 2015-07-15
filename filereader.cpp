#include <string>
#include <vector>
#include <fstream>
#include "filereader.hpp"

/**
 * Returns a string containing the contents of a file
 * @param path the path of the file to be read
 * @return contents of the file
 */
std::string readFile(const std::string &path) {
    std::string text;
    std::ifstream file(path);
    std::string str;
    while (getline(file, str)) {
        text += str;
    }
    return text;
}

/**
 * Returns a vector with each element containing the path of a file
 * @param path the path of the file list
 * @return list of files
 */
std::vector<std::string> getFileList(const std::string &path) {
    std::vector<std::string> fileList;
    std::string str;
    std::ifstream file(path);
    while (getline(file, str)) {
        fileList.push_back(str);
    }
    return fileList;
}