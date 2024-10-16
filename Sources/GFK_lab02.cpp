﻿#include "SFML/Graphics.hpp"
#include "Hexagon.h"
#include <numeric>
#include <iostream>
#include "Scrollbar.h"

//Tak – dobrze państwo widzą – TO jest zmienna globalna! Czytanie i przetwarzanie fontów w SFML jest bardzo kosztowne. Dlatego zrobimy to raz. 
//Co nie zmienia faktu, że można by to zrobić bez zmiennej globalnej i to całkiem ładnie. Jak? To już dla Państwa :-)



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    
    hexagon_RGB h_RGB(window.getSize());
    hexagon_CMY h_CMY(window.getSize());
    hexagon_HSL h_HSL(window.getSize());
    hexagon_HSB h_HSB(window.getSize());
    Scrollbar bar(window.getSize());

    sf::Clock frame_clock, around_half_secound_clock;
    sf::Int64 mean_frames_time = 0;
    std::vector<sf::Int64> frame_times;
    sf::Text text;

    float current_lightness;
    bool isMousePressed = false;

    
    text.setFont(*h_RGB.font);
    text.setCharacterSize(21);
    text.setFillColor(sf::Color::Black);

    text.setPosition(10, 10);


    around_half_secound_clock.restart();

    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color::White);

        frame_clock.restart(); // Start pomiaru czasu.

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            // Tu trzeba obsłużyć zdarzenia: zmianę rozmiaru okna oraz klikanie w „suwaczek”. 
            if (event.type == sf::Event::Resized)
            {
                float width = static_cast<float>(event.size.width);
                float height = static_cast<float>(event.size.height);
                window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
                h_RGB.SetDrawParameters(window.getSize());
                h_CMY.SetDrawParameters(window.getSize());
                h_HSL.SetDrawParameters(window.getSize());
                h_HSB.SetDrawParameters(window.getSize());
                bar.SetDrawParamiters(window.getSize());
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (bar.isHitBox(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), current_lightness))
                {
                    h_RGB.updateLightness(current_lightness);
                    h_CMY.updateLightness(current_lightness);
                    h_HSL.updateLightness(current_lightness);
                    h_HSB.updateLightness(current_lightness);
                    isMousePressed = true;
                }     
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                isMousePressed = false;
            }
            if (event.type == sf::Event::MouseMoved)
            {
                if (isMousePressed && bar.isHitBox(sf::Vector2f(event.mouseMove.x, event.mouseMove.y), current_lightness))
                {
                    h_RGB.updateLightness(current_lightness);
                    h_CMY.updateLightness(current_lightness);
                    h_HSL.updateLightness(current_lightness);
                    h_HSB.updateLightness(current_lightness);
                }
            }
        }

        window.draw(h_RGB);
        window.draw(h_CMY);
        window.draw(h_HSL);
        window.draw(h_HSB);
        window.draw(bar);
        // Pewnie tu gdzieś wypadało by dorysować jeszcze suwaczek... 
        text.setString(std::to_string(mean_frames_time) + "us");
        window.draw(text);

        // Pomiar czasu uśrednimy w okresie około 1/2 sekundy.
        frame_times.push_back(frame_clock.getElapsedTime().asMicroseconds());
        if (around_half_secound_clock.getElapsedTime().asSeconds() >= 0.5f && frame_times.size() >= 1)
        {
            mean_frames_time = (sf::Int64)((float)std::reduce(frame_times.begin(), frame_times.end()) / (float)frame_times.size());
            frame_times.clear();
            around_half_secound_clock.restart();
        }

        frame_clock.restart(); // Stop pomiaru czasu.
        window.display();
    }

    //Hmmm ... :-/
    h_RGB.font.reset();

    return 0;
}