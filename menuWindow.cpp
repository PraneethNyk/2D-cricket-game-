#include "menuWindow.h"
#include <iostream>
#include <unistd.h>
menuWindow::menuWindow()
{
    /// setting up menu background
    this->texturebg.loadFromFile("Background/menubg.jpg");
    this->spritebg.setTexture(this->texturebg);
    sf::Vector2u bgsize=this->texturebg.getSize();
    spritebg.setScale(1920/static_cast<float>(bgsize.x),1080/static_cast<float>(bgsize.y));
    spritebg.setPosition(0.f,0.f);

    /// setting up text and tiles
    this->font.loadFromFile("Fonts/LibreBaskerville-Italic.ttf");
    this->text[0].setString("Play");
    this->text[1].setString("Help");
    this->text[2].setString("About");
    this->text[3].setString("Close");
    for(int i=0;i<4;i++)
    {
        this->text[i].setCharacterSize(55);
        this->text[i].setFillColor(sf::Color::Blue);
        this->text[i].setFont(this->font);
        this->text[i].setPosition(700.f,300.f+200*i);
        tile_.push_back(_tile.getObject());
        (*(tile_.begin()+i)).setPosition(500.f,250.f+200*i);
    }

    /// initialising hover
    for(int i=0;i<4;i++)
    hover.push_back(false);
}

/// resetting screen to original condition
void menuWindow::reset()
{
    (*tile_.begin()).setFillColor(sf::Color::Red);
    (*tile_.begin()).setOutlineColor(sf::Color::Green);
    hover.at(0) = true;
    for(int i=1;i<4;i++)
    {
        (*(hover.begin()+i)) = false;
        (*(tile_.begin()+i)).setFillColor(sf::Color::Yellow);
        (*(tile_.begin()+i)).setOutlineColor(sf::Color::White);
    }
    event.key.code = sf::Keyboard::Space;
}

/// function to render graphics on screen
void menuWindow::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(spritebg);
    for(int i=0;i<4;i++)
    {
        window.draw((*(tile_.begin()+i)));
        window.draw(text[i]);
    }
    window.setView(sf::View(sf::Vector2f(960.f,540.f),sf::Vector2f(1920.f,1080.f)));
    window.display();
}

jump_t menuWindow::call(sf::RenderWindow& window)
{
    int i;
    reset();
    render(window);
    while(true)
    {
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::KeyPressed)
            {
                i = nav.navigate(event,4,hover,tile_);
            }
            render(window);
            if(event.key.code==sf::Keyboard::Enter)
            {
                sleep(1);
                if(text[i].getString()=="Play")
                    return jump_t::LEVELS;
                if(text[i].getString()=="Close")
                    return jump_t::CLOSE;
                if(text[i].getString()=="Help")
                    return jump_t::HELP;
                if(text[i].getString()=="About")
                    return jump_t::ABOUT;
            }
        }
    }
}