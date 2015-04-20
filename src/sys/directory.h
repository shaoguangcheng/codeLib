#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

namespace csg {
    typedef vector<string> strVec;

	bool isFileExist(const char* filename);

/**
     * @brief isDir test if dir is a directory
     * @param dir
     * @return
     */
    bool isDir(const char* dir);

    /// return the current path
    /// @param path  return value
    int pwd(string& path);

    /// return the current directory name
    int currentDirectoryName(string& directoryName);

    /// enter a directory
    void cd(const string& path);

    /// return the files name in specified directory,recursively
    int getFiles(const string path,strVec& fileName);

}//end of namespace csg

#endif // DIRECTORY_H
