#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    int lives = 3;
    int lives2 = 3;
    // Create a bat at the bottom center of the screen
    Bat bat(20, 1080 / 2);
    Bat bat2(1900, 1080 / 2);
    bool paused = true;
    bool go = false;
    bool spaused = false;

    // Create a ball
    Ball ball(1920 / 2, 1080 / 2);
    
    // Create a Text object called HUD
    Text hud;
    // A cool retro-style font
    Font font;
    font.loadFromFile("Fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    hud.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(75);
    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    // Here is our clock for timing everything

    Text startHud;
    // A cool retro-style font
    Font startFont;
    startFont.loadFromFile("Fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    startHud.setFont(font);
    // Make it nice and big
    startHud.setCharacterSize(75);
    // Choose a color
    startHud.setFillColor(Color::White);
    startHud.setPosition(1920/2, 1080/2);

    Text GOHud;
    // A cool retro-style font
    Font GOFont;
    startFont.loadFromFile("Fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    GOHud.setFont(font);
    // Make it nice and big
    GOHud.setCharacterSize(75);
    // Choose a color
    GOHud.setFillColor(Color::White);
    GOHud.setPosition(1920 / 2, 1080 / 2);
   
    Text pHud;
    // A cool retro-style font
    Font pFont;
    pFont.loadFromFile("Fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    pHud.setFont(font);
    // Make it nice and big
    pHud.setCharacterSize(75);
    // Choose a color
    pHud.setFillColor(Color::White);
    pHud.setPosition(1920 / 2 - 500, 1080 / 2);

    Clock clock;


    while (window.isOpen())
    {
        /*
        Handle the player input
        ****************************
        ****************************
        ****************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
            spaused = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Return) &&( lives < 1 || lives2 < 1))
        {
            lives = 3;
            lives2 = 3;
        }

        std::stringstream sss;
        sss << "Press enter to start";
        startHud.setString(sss.str());

        if (!paused)
        {

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                paused = true;
                spaused = true;
            }

            // Handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            // Handle the pressing and releasing of the arrow keys
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                bat.moveUp();
            }
            else
            {
                bat.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                bat.moveDown();
            }
            else
            {
                bat.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                bat2.moveUp();
            }
            else
            {
                bat2.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                bat2.moveDown();
            }
            else
            {
                bat2.stopDown();
            }
            /*
            Update the bat, the ball and the HUD
            *****************************
            *****************************
            *****************************
            */

            // Update the delta time
            Time dt = clock.restart();

            bat.update(dt);
            bat2.update(dt);
            ball.update(dt);

            // Update the HUD text
            std::stringstream ss;
            ss << "Lives:" << lives << "        Lives2:" << lives2;
            hud.setString(ss.str());
            
            std::stringstream pss;
            pss << "Paused, press return to continue";
            pHud.setString(pss.str());

            std::stringstream goss;
            goss << "Game Over";
            GOHud.setString(goss.str());
            // Handle ball hitting the bottom
            if (ball.getPosition().top < 0 || ball.getPosition().top + ball.getPosition().height > window.getSize().y)
            {
                // reverse the ball direction
                ball.reboundBottomOrTop();
                // Remove a life

            }

            /*/ Handle ball hitting
            if (ball.getPosition().top < 0)
            {
                ball.reboundBat();
                // Add a point to the players scoreball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x
                score++;
            }
            */
            // Handle ball hitting sides
            if (ball.getPosition().left < 0)
            {
                ball.reboundSides();

                lives--;
                // Check for zero lives
                if (lives < 1) {

                    go = true;
                    paused = true;

                    // reset the lives
                    //lives = 3;
                }
            }

            if (
                ball.getPosition().left + ball.getPosition().width >
                window.getSize().x)
            {
                ball.reboundSides();

                lives2--;
                // Check for zero lives
                if (lives2 < 1) {

                    go = true;
                    paused = true;
                    // reset the lives
                    //lives2 = 3;
                }
            }
            // Has the ball hit the bat?
            if (ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition()))
            {
                // Hit detected so reverse the ball and score a point
                ball.reboundBat();
            }
        }
        
        /*
        Draw the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        window.clear();
        window.draw(hud);
        if (paused && !go && !spaused)
        {
            window.draw(startHud);
        }
        if (paused && spaused)
        {
            window.draw(pHud);
        }
        if (paused && go && !spaused)
        {
            window.draw(GOHud);
        }
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());
        window.display();
    }
    return 0;
}