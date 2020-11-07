#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*Public parameters*/
// Main window where it is displayed the screen
sf::RenderWindow mainWindow(sf::VideoMode(800,600), "SimplePong Game", sf::Style::Close | sf::Style::Titlebar);

/* initialization functions */
void initWindow();
void initShapes();
void initSounds();
void initFonts();

/*game part functions*/
void eventPart();
void logicPart();
void renderingPart();

int main() {
    /*Window creation and settings*/
    initWindow();
    initShapes();
    initSounds();
    initFonts();
    /* Main Game Loop */
    while(mainWindow.isOpen()){
        /* Event part */
        eventPart();
        /* Logic part */
        logicPart();
        /* Rendering part */
        renderingPart();
    }

    /*Game exited*/
    std::cout << "Game closing" << std::endl;
    return 0;
}

/* Window initialization */
void initWindow(){
    mainWindow.setFramerateLimit(60);
    std::cout << "Game started" << std::endl;
}
