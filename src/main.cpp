#include "hello.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include all GLM core / GLSL features
//#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/mat4x4.hpp>
// Include all GLM extensions
#include <glm/ext.hpp> // perspective, translate, rotate

glm::mat4 transform(glm::vec2 const& Orientation, glm::vec3 const& Translate, glm::vec3 const& Up)
{
	glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
	glm::mat4 Model = glm::mat4(1.0f);
	return Proj * View * Model;
}

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

/// Main program function
int main(int argc, char **argv)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile("e",
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	glm::mat4 test_glm(1.f);
	test_glm = transform(glm::vec2(1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));

	//    int result = add(1, 2);
	//    std::cout << "Result = " << result << std::endl;

	int w;
	int h;
	int comp;
	std::string filename_abs = "C:\\Users\\Spark\\Desktop\\apps\\cppprojects\\ci_opengl_template\\src\\jenkins-logo.png";
	unsigned char* image = stbi_load(filename_abs.c_str(), &w, &h, &comp, STBI_rgb);
	if (image == nullptr)
		throw(std::string("Failed to load texture"));
	else
		std::cout << "Image " << filename_abs.c_str() << " loaded successfully !" << std::endl;

    int width, height;
    GLFWwindow* window;

    /* Init GLFW */
    if( !glfwInit() )
        exit( EXIT_FAILURE );

    window = glfwCreateWindow( 400, 400, "GLFW demo window", NULL, NULL );
    if (!window)
    {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwSetWindowAspectRatio(window, 1, 1);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    glfwGetFramebufferSize(window, &width, &height);

    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    std::cout << "Setup status: SUCCESS" << std::endl;
    // std::cin.get();

    return 0;
}
