//
// Created by robin on 19.01.2020.
//

#include "ProgramManager.h"

int emuprogramExample(int argc, char** argv)
{

    std::string title = "emusound demo";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    esnddemo::ProgramManager program(title, sf::Vector2i(400 * 4, 240 * 4), sf::Vector2i(400, 240), sf::Style::Titlebar, settings);
    //program.setZoomValue(1.f);
    program.initialize();
    program.run();

    return 0;
}

int main(int argc, char** argv)
{
    return emuprogramExample(argc, argv);
}