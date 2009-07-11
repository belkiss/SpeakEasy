#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <SFML/Window.hpp>
#include "SE_Screen.h"

int main()
{

    sf::WindowSettings settings;
    settings.DepthBits         = 24; // set 24 bits Z-buffer
    settings.StencilBits       = 8;  // set 8 bits stencil-buffer
//     settings.AntialiasingLevel = 2;  // set 2x antialiasing

    sf::Window app(sf::VideoMode(640, 480, 32), "SpeakEasy, v0.2.1", sf::Style::Resize | sf::Style::Close, settings);
    app.SetFramerateLimit(60);
    app.ShowMouseCursor(false);

    SE_Screen vl_screen;
    vl_screen.initializeGL();
    vl_screen.resizeGL(640, 480);

    while (app.IsOpened())
    {
        // Process events
        sf::Event event;
        while (app.GetEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                app.Close();

            // Escape key : exit
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
            {
                app.Close();
            }
            else if ((event.Type == sf::Event::KeyPressed))
            {
                vl_screen.keyPressEvent(event.Key.Code);
            }

            if (event.Type == sf::Event::KeyReleased)
            {
                vl_screen.keyReleaseEvent(event.Key.Code);
            }

            if (event.Type == sf::Event::MouseMoved)
            {
                vl_screen.mouseMoveEvent(&app, event.MouseMove.X, event.MouseMove.Y);
            }

            // Adjust the viewport when the window is resized
            if (event.Type == sf::Event::Resized)
            {
                vl_screen.resizeGL(event.Size.Width, event.Size.Height);
            }
        }

        vl_screen.paintGL();
        app.Display();
    }

    return EXIT_SUCCESS;

}
