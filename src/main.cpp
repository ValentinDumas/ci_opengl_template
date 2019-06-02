//
// Created by Spark on 27/04/2019.
//

#include <SFML/OpenGL.hpp>
#include <cstdio>

#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "utils/typ.h"

#include "lua/LuaScript.h"

int main(int argc, char** argv)
{
    sf::Sound sound;

    sf::SoundBuffer soundBuffer;

    if(!soundBuffer.loadFromFile("assets/audio/getout.ogg"))
    {
        return 3;
    }
    else
    {
        sound.setLoop(true);
        sound.setBuffer(soundBuffer);
        sound.play();
    }

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display

//    sf::Texture texture;
//    if (!texture.loadFromFile("cute_image.jpg"))
//        return EXIT_FAILURE;
//    sf::Sprite sprite(texture);
//    // Create a graphical text to display
//
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf"))
//        return EXIT_FAILURE;
//    sf::Text text("Hello SFML", font, 50);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        // window.draw(sprite);
        // Draw the string
        // window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
