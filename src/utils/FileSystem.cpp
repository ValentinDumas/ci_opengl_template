//
// Created by Spark on 01/05/2019.
//

#include <cppfs/FilePath.h>

#include <cppfs/fs.h>

#include "FileSystem.hpp"

#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef MSVC_PLATFORM
#include <direct.h>
#define GetCurrentDir _getcwd
#else

#include <unistd.h>


#define GetCurrentDir getcwd
#endif

// TODO: Keep track of current/ old(s) selected paths in private (static) values ?
static std::string current_working_path = "";

static cppfs::FileHandle get_entry(const std::string &path)
{
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

std::string utils::filesystem::get_filename(const std::string &path)
{
    cppfs::FilePath filePath(path);
    return filePath.fileName();
}

bool utils::filesystem::exists(const std::string &path)
{
    cppfs::FileHandle entry = cppfs::fs::open(path);

    return entry.exists();
}

bool utils::filesystem::has_extension(const std::string &path)
{
    return !utils::filesystem::get_file_extension(path).empty();
}

// If entry "has children" -> it's a directory. If not -> it's a file.
bool utils::filesystem::has_children(const std::string& path)
{
    cppfs::FileHandle entry = cppfs::fs::open(path);
    return entry.exists() && (entry.listFiles().size() > 0);
}

std::string utils::filesystem::get_file_extension(const std::string &filepath)
{
    long long int found = -1;

    found = filepath.find_last_of('.');

    if (found == -1)
    {
        std::cout << "[Info] extension not found for file: " << filepath.c_str() << std::endl;
        return ""; // folder = no filename
    }

    return filepath.substr(found); // At least one "." char found => return all after the lasrt dot "."
}

// TODO: watch the behavior of this function when path does not exists in owner's FileSystem
std::string utils::filesystem::get_filename_without_extension(const std::string &path)
{
    std::string filename = get_filename(path);

    int found = -1;
    found = filename.find_last_of(".");

    std::string filename_without_extension;

    if (found == -1) {
        std::cout << "[Info] extension not found for file: " << filename.c_str() << std::endl;
        return ""; // folder = no filename
    } else // at least one "." char found
    {
        filename_without_extension = filename.substr(0, found); // return all before the lasrt dot "."
    }

    return filename_without_extension;
}

std::string utils::filesystem::get_filepath_without_extension(const std::string &path)
{
    int found = -1;
    found = path.find_last_of(".");

    std::string filepath_without_extension;

    if (found == -1) {
        std::cout << "[Info] extension not found for file: " << path.c_str() << std::endl;
        return ""; // folder = no filename
    } else // at least one "." char found
    {
        filepath_without_extension = path.substr(0, found); // return all before the lasrt dot "."
    }

    return filepath_without_extension;
}


bool utils::filesystem::is_file(const std::string &path)
{
    return !utils::filesystem::get_filename_without_extension(path).empty(); // is_file if not empty
}

bool utils::filesystem::is_directory(const std::string &path)
{
    return utils::filesystem::get_filename_without_extension(path).empty(); // is_directory if empty
}

bool utils::filesystem::set_working_path(const std::string &path)
{
    cppfs::FileHandle file_handle = cppfs::fs::open(path);

    if (!file_handle.exists())
    {
        std::cout << "[Error] Path " << path << " does not exists on the current filesystem" << std::endl;
        return false;
    }

    current_working_path = path;

    return true;
}

// Process a tree level
void utils::filesystem::get_tree_filepaths(std::unique_ptr<cppfs::Tree> &file_tree, std::vector<std::string> &paths, bool tidy)
{
    if(tidy) // The registered file paths follow their direct parent directory path
    {
        for (auto &child : file_tree->listFiles())
        {
            std::string tree_child_complete_path = (file_tree.get()->path() + "\\" + child); // file path (absolute)
            paths.push_back(tree_child_complete_path);
            if(utils::filesystem::is_directory(tree_child_complete_path))
            {
                std::vector<std::unique_ptr<cppfs::Tree> > &tree_children = file_tree->children();

                for (auto &tree_child : tree_children) // if at least one children
                {
                    utils::filesystem::get_tree_filepaths(tree_child, paths); // Look for deeper levels from this tree node
                }
            }
        }
    }
    else // not tidy => The registered paths (files and directories) are ordered alphabetically
    {
        for (auto &child : file_tree->listFiles())
        {
            std::string tree_child_complete_path = (file_tree.get()->path() + "\\" + child); // file path (absolute)
            paths.push_back(tree_child_complete_path);
        }

        std::vector<std::unique_ptr<cppfs::Tree> > &tree_children = file_tree->children();

        for (auto &tree_child : tree_children) // if at least one children
        {
            utils::filesystem::get_tree_filepaths(tree_child, paths); // Look for deeper levels from this tree node
        }
    }
}

void utils::filesystem::get_tree(const std::string &path, std::vector<std::string> &paths, bool tidy, bool include_hash)
{
    cppfs::FileHandle file_handle = cppfs::fs::open(path);
    std::unique_ptr<cppfs::Tree> tree; // tree pointing to given (root) path

    if (file_handle.exists()) // (root) path exists => tree opened
    {
        tree = file_handle.readTree(path, include_hash); // Read the tree from the given path

        paths.push_back(tree->path()); // Get & Register the root path for this tree

        utils::filesystem::get_tree_filepaths(tree, paths);
    }
}

std::string utils::filesystem::get_current_path()
{
    char path[FILENAME_MAX];

    GetCurrentDir(path, FILENAME_MAX);

    return std::string(path);
}

std::vector<std::string> utils::filesystem::get_directory_entries(const std::string &path)
{
    std::vector<std::string> entries;
    cppfs::FileHandle directory = cppfs::fs::open(path);

    for (std::string directory_entry : directory.listFiles())
    {
        entries.push_back(directory_entry);
    }

    return entries;
}

void utils::filesystem::print_directory_entries(const std::string &path)
{
    std::vector<std::string> entries = utils::filesystem::get_directory_entries(path);

    std::cout << "List of directory entries (" << path << "):" << std::endl;

    for (auto entry : entries)
    {
        std::cout << "-> " << entry << std::endl;
    }
}

// TODO: Read/Write functions (with native and/or cppfs)