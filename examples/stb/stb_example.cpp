//
// Created by Spark on 28/04/2019.
//

#include <iostream>

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef MSVC_PLATFORM
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int main(int argc, char **argv)
{
    char binary_path[FILENAME_MAX];
    GetCurrentDir( binary_path, FILENAME_MAX );
    printf("Current working (binary) dir: %s\n", binary_path);

    int w = 0;
    int h = 0;
    int comp = 0;
    std::string filepath = "";

    filepath = std::string(binary_path);
    filepath += std::string("\\");
    filepath += std::string("assets\\images\\jenkins-logo.png");

    std::cout << filepath << std::endl;

    unsigned char *image = stbi_load(filepath.c_str(), &w, &h, &comp, STBI_rgb);
    if (image == nullptr) {
        std::cout << "Image at path " << filepath << "was loaded wrong !" << std::endl;
        throw (std::string("Failed to load texture"));
    } else
        std::cout << "Image at path " << filepath << "was loaded successfully !" << std::endl;

    stbi_image_free(image);

    return 0;
}
