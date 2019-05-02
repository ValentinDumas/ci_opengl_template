//
// Created by Spark on 01/05/2019.
//

#include "FileSystem.h"

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

extern "C"
{
    int external_number = 0;
};

static std::string current_working_path = "";
//static cppfs::FileHandle current_working_dir; // private scope

std::vector<std::string> selected_paths; // Note: stores all the previous (and the current ?) selected path

std::string get_filename(const std::string &path) {
    return (cppfs::fs::open(path)).fileName();
}

bool utils::filesystem::set_working_path(const std::string &path) {
    cppfs::FileHandle file_handle = cppfs::fs::open(path);

    if (!file_handle.exists())
    {
        std::cout << "[Error] Path " << path << " does not exists on the current filesystem" << std::endl;
        return false;
    }

    current_working_path = path;
    return true;
}

void utils::filesystem::get_tree_filepaths(std::unique_ptr<cppfs::Tree> & file_tree) {
    // TODO: while tree children size > 0 ? continue getting into children ?
    std::vector<std::unique_ptr<cppfs::Tree> > &tree_children = file_tree->children();

//    if(!tree_children.empty())
//    {
        for(auto & tree_child : tree_children)
        {
            std::string tree_child_path = tree_child->path();
            // Process this tree level
            for(auto & child : tree_child->listFiles())
            {
                std::string tree_child_complete_path;
                tree_child_complete_path += tree_child_path += "\\" + child;
                std::cout << tree_child_complete_path << std::endl;
                std::cout << cppfs::fs::open(tree_child_complete_path).readFile() << std::endl;
            }

            // Look for deeper levels from this tree node
            utils::filesystem::get_tree_filepaths(tree_child);
        }
//    }
}

void utils::filesystem::get_tree(const std::string &path, bool include_hash) {
    cppfs::FileHandle file_handle = cppfs::fs::open(path);
    std::unique_ptr<cppfs::Tree> file_tree;

    std::vector<std::string> root_entries;

    if (file_handle.exists()) {
        // Read the whole tree from the given path
        file_tree = file_handle.readTree(path, include_hash);

        // Get the root path
        std::cout << "TREE root path: " << file_tree->path() << std::endl;

        utils::filesystem::get_tree_filepaths(file_tree);

//        for(auto &tree_child : tree_children)
//        {
//            std::cout << "TREE children path: " << tree_child.get()->path() << std::endl;
//            for(auto & tree_child_entry : tree_child.get()->listFiles())
//            {
//                std::cout << " ----------> " << tree_child_entry.c_str() << std::endl;
//            }
//        }
    }
}

std::string utils::filesystem::get_current_path() {
    char path[FILENAME_MAX];

    GetCurrentDir(path, FILENAME_MAX);

    printf("Current working (binary) dir: %s\n", path);

    return std::string(path);
}

cppfs::FileHandle utils::filesystem::get_entry(const std::string &path) {
    cppfs::FileHandle entry = cppfs::fs::open(path);

    if (entry.isFile()) {
        std::cout << "[info] entry is a file" << std::endl;
    } else if (entry.isDirectory()) {
        std::cout << "[info] entry is a directory" << std::endl;
    } else if (!entry.exists()) {
        std::cout << "[info] Entry does not exists (at path " << path << ")" << std::endl;
    }

    return entry; // Not sure about this behaviour ! # TODO: check what happens when cppfs::FileHandle is "null"
}

std::vector<std::string> utils::filesystem::get_directory_entries(const std::string &path) {
    std::vector<std::string> entries;
    cppfs::FileHandle directory = cppfs::fs::open(path);

    for (std::string directory_entry : directory.listFiles()) {
        entries.push_back(directory_entry);
    }

    return entries;
}

void utils::filesystem::print_directory_entries(const std::string &path) {
    std::vector<std::string> entries = utils::filesystem::get_directory_entries(path);

    std::cout << "List of directory entries (" << path << "):" << std::endl;

    for (auto entry : entries) {
        std::cout << "-> " << entry << std::endl;
    }

    external_number += 10;
}

void utils::filesystem::list_recursive_directory_entries(const std::string &path) {
    // ...
    external_number += 10;
}

// list all files

