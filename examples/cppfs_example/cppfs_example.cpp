//
// Created by Spark on 27/04/2019.
//

#include <cppfs/fs.h>
#include <cppfs/FilePath.h>
#include <cppfs/FileHandle.h>
#include <cppfs/Tree.h>

#include <iostream>
#include <string>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef MSVC_PLATFORM
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

void open_file(const std::string& filename)
{
    cppfs::FileHandle fh = cppfs::fs::open(filename);

    if (fh.isFile())
    {
        /* File ... */
        std::cout << "File > " << fh.fileName() << std::endl;
    }
    else if (fh.isDirectory())
    {
        /* Directory ... */
        std::cout << "File > " << fh.fileName() << std::endl;
    }
    else if (!fh.exists())
    {
        /* Not there ... */
        std::cout << "File > " << fh.fileName() << std::endl;
    }
}

int main(int argc, char**argv)
{
    char binary_path[FILENAME_MAX];
    GetCurrentDir( binary_path, FILENAME_MAX );
    printf("Current working (binary) dir: %s\n", binary_path);

    // Get project root path
    cppfs::FilePath project_root_path = (std::string(binary_path) + "\\").c_str();
    project_root_path = project_root_path.resolved();
    printf("Current working (project) dir: %s\n", project_root_path.fullPath().c_str());

    cppfs::FileHandle project_root_handle = cppfs::fs::open(project_root_path.fullPath());
    for(auto r : project_root_handle.listFiles())
    {
        std::cout << "under parent dir  ==>  " << r.c_str() << std::endl;
    }

    std::cout << "----------------------------" << std::endl;
    open_file("assets\\images\\jenkins-logo.png");
    std::cout << "----------------------------" << std::endl;

    return 0;
}