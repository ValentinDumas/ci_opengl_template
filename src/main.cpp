#include <iostream>

#include "mathematics/complex.hpp"

#include "lua/LuaScript.h"

//#include "utils/typ.h"

#include "utils/FileSystem.hpp"

#include "entities/Entity.h"

#include "events/Events.h"
#include "events/EventSubscriber.h"

#include "components/Sprite.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SFML/Audio.hpp>
#include "GLFWEnvironment.h"

#include "components/Texture.h"
#include "components/Sprite.h"
#include "components/Input.h"
#include "components/BoxPhysics.h"
#include "components/ContactListener.h"
#include "components/Shader.h"

#include "SpriteRenderer.h"

#include "scenes/SceneManager.h"

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void test_components()
{
    Input input = Input();
    BoxPhysics boxPhysics = BoxPhysics();
    ContactListener contactListener = ContactListener();
}

// TODO: always check if glad is initialized when making a "glad related call"

class Engine
{
public:
    void Start()
    {
        //GLFWEnvironment* m_glfw_environment = new GLFWEnvironment("DreamIn Engine", 1920, 1080, GL_FALSE);
        GLFWEnvironment* m_glfw_environment = new GLFWEnvironment(false);
        m_glfw_environment->init();

        // TODO: Move all GL/GLEW options/parameters to a GLEWEnvironment/GLEWContext class
        bool err = gladLoadGL() == 0;
        if (err) {
            fprintf(stderr, "Failed to initialize OpenGL loader!\n");
            return;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_SMOOTH);

        // Load shaders & count
        unsigned int shader_count = ResourceManager::LoadShaders("assets\\shaders");
        std::cout << "Shaders Loaded: " << shader_count << std::endl;

        // Load textures & count
        unsigned int texture_count = ResourceManager::LoadTextures("assets\\textures");
        std::cout << "Textures Loaded: " << texture_count << std::endl;

        SceneManager* sm = new SceneManager(m_glfw_environment);

        // Create a new Scene and add it to the Scene Manager
        sm->createScene("Aloha");

        // Select a scene to be marked as active
        sm->select_scene("Aloha");

        sm->start();

        delete sm; sm = nullptr;
    }
};

int main(int argc, char** argv) {
    sf::Sound sound;

    sf::SoundBuffer soundBuffer;

    if(!soundBuffer.loadFromFile("assets\\audio\\getout.ogg"))
    {
        return 3;
    }
    else
    {
        sound.setLoop(true);
        sound.setBuffer(soundBuffer);
        sound.play();
    }

    Engine *DreamInEngine = new Engine();
    DreamInEngine->Start();

    delete DreamInEngine;
    DreamInEngine = nullptr;

    return 0;
}

//
///// Main program function
//int mainXP(int argc, char **argv)
//{
//    auto path = utils::filesystem::get_current_path();
//    std::cout << "Current main path: " << path << std::endl;
//
//    utils::filesystem::print_directory_entries(path);
//
//    //auto a = utils::filesystem::get_entry(path + "\\DreamInEngine.exe");
//
////    utils::filesystem::print_directory_entries("");
//
//    //TODO : remove "#include <utils/typ.h>" call from Scene.h && refactor Scene.h...
////    auto t_index = getTypeIndex<int>();
//
//    std::vector<std::string> assets_paths;
//    utils::filesystem::get_tree(path, assets_paths);
//
//    std::cout << "Setup status: SUCCESS !" << std::endl;
//    // std::cin.get();
//
//    GLFWEnvironment *glfw = new GLFWEnvironment();
//    glfw->init();
//
//    bool err = gladLoadGL() == 0;
//    if (err) {
//        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
//        return 0;
//    }
//
//    test_components(); // Note: processed only if glad is initialized
//
//    ResourceManager::LoadShader("C:\\Users\\Spark\\Desktop\\apps\\cppprojects\\DreamInEngine\\assets\\shaders\\sprite2D.vert", "C:\\Users\\Spark\\Desktop\\apps\\cppprojects\\DreamInEngine\\assets\\shaders\\sprite2D.frag", nullptr, "sprite2D");
//    ResourceManager::LoadTexture(std::string("C:\\Users\\Spark\\Desktop\\apps\\cppprojects\\DreamInEngine\\assets\\textures\\awesomeface.png").c_str(), true, "awesomeface");
//    Sprite sprite(ResourceManager::GetTexture("awesomeface"), glm::vec2(0.0f, 0.0f));
//
//    SpriteRenderer *spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite2D"));
//
//    // Main loop
//    while (!glfw->quit())
//    {
//        // Poll and handle events (inputs, window resize, etc.)
//        glfwPollEvents(); // poll glfw events
//        glfw->process_input(); // inputs related to glfw
//
//        int display_w, display_h;
//        glfwMakeContextCurrent(glfw->get_window());
//        glfwGetFramebufferSize(glfw->get_window(), &display_w, &display_h);
//
//        glViewport(0, 0, display_w, display_h);
//        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(glfw->get_width()), static_cast<GLfloat>(glfw->get_height()), 0.0f, -1.0f, 1.0f);
//        // Configure shaders
//        ResourceManager::GetShader("sprite2D").Use().SetInteger("image", 0);
//        ResourceManager::GetShader("sprite2D").SetMatrix4("projection", projection);
//        spriteRenderer->DrawSprite(sprite.m_texture, sprite.Position);
//
//        sprite.Position.x += 1;
//        sprite.Position.y += 1;
//
//
//        glfwMakeContextCurrent(glfw->get_window());
//        glfwSwapBuffers(glfw->get_window());
//    }
//
//    glfw->close();
//
//    return 0;
//}