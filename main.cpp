#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <chrono>
#include <thread>
#include <functional>

/*Public parameters*/
// Main window where it is displayed the screen
sf::RenderWindow mainWindow(sf::VideoMode(800,600), "SimplePong Game", sf::Style::Close | sf::Style::Titlebar);
// Event object
sf::Event mainEvent;

/* Textures */
sf::Texture padTexture;
sf::Texture ballTexture;
sf::Texture backTexture;

/* Soundbuffer */
sf::SoundBuffer buffHit;
sf::Sound hit;
/* Shapes */
sf::RectangleShape background;

sf::RectangleShape firstPad;
sf::RectangleShape secondPad;

sf::RectangleShape ball;

/* States */
bool up = false, down = false;

/* Variables */
int ySpeedFirstPad = 0;
int xSpeedBall = -3, ySpeedBall=-3;
int ySpeedSecondPad = 0;
int pad1score=0, pad2score=0;
/* font and text */
sf::Font myFont;
sf::Text score;
sf::Text pause;

int soglia = 5;
bool isPause = false;
/* initialization functions */
void initWindow();
void initShapes();
void initSounds();
void initFonts();

/*game part functions*/
void eventPart();
void logicPart();
void renderingPart();
void timer_start(std::function<void(void)> func, unsigned int interval);
void add_difficulty();

int main() {
    /*Window creation and settings*/
    initWindow();
    initShapes();
    initSounds();
    initFonts();
    timer_start(add_difficulty, 30000);
    /* Main Game Loop */
    while(mainWindow.isOpen()){
        /* Event part */
        eventPart();
        if(!isPause){
            /* Logic part */
            logicPart();
        }
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

/* Shapes initialization */
void initShapes(){
    // Pad shape
    if(!padTexture.loadFromFile("data/img/pad.png")){/**/}
    if(!ballTexture.loadFromFile("data/img/ball.png")){/**/}
    if(!backTexture.loadFromFile("data/img/background.png")){/**/}

    //Sfondo
    background.setSize(sf::Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&backTexture);

    //Primo pad
    firstPad.setSize(sf::Vector2f(30,100));
    firstPad.setPosition(10, 200);
    firstPad.setTexture(&padTexture);

    //Secondo pad
    secondPad.setSize(sf::Vector2f(30,100));
    secondPad.setPosition(760, 200);
    secondPad.setTexture(&padTexture);

    //Pallina
    ball.setSize(sf::Vector2f(60,50));
    ball.setPosition(400,200);
    ball.setTexture(&ballTexture);
}

/* Sounds initialization */
void initSounds(){
    if(!buffHit.loadFromFile("data/audio/hit.wav")){std::cout<<"NOOO"<<std::endl;}
    hit.setBuffer(buffHit);
}

/* Fonts initialization */
void initFonts(){
    // Inizializzazione del font:
    if(!(myFont.loadFromFile("data/fonts/Grundschrift-Bold.otf"))){ /*Errori gestiti in automatico*/ }
    score.setFont(myFont);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Yellow);
    score.setPosition(375,10);
    score.setString("0 : 0");
    pause.setFont(myFont);
    pause.setCharacterSize(40);
    pause.setFillColor(sf::Color::Red);
    pause.setPosition(350,270);
    pause.setString("");
}

/* Events part */
void eventPart(){
    while(mainWindow.pollEvent(mainEvent)){
        /* Close event */
        if(mainEvent.type == sf::Event::Closed) mainWindow.close();
        if(!isPause){
            /* Pressed */
            if(mainEvent.type == sf::Event::KeyPressed && mainEvent.key.code == sf::Keyboard::Up) up = true;
            if(mainEvent.type == sf::Event::KeyPressed && mainEvent.key.code == sf::Keyboard::Down) down = true;
            /* Released */
            if(mainEvent.type == sf::Event::KeyReleased && mainEvent.key.code == sf::Keyboard::Up) up = false;
            if(mainEvent.type == sf::Event::KeyReleased && mainEvent.key.code == sf::Keyboard::Down) down = false;
        }
        /* Pause game */
        if(mainEvent.type == sf::Event::KeyPressed && mainEvent.key.code == sf::Keyboard::P){
            if(isPause){
                pause.setString("");
                isPause = false;
            }else{
                pause.setString("PAUSE");
                isPause = true;
            }
        }
    }
}

/* Logic part */
void logicPart(){
    //Logic of first pad
    if(up){
        ySpeedFirstPad = -5;
    }
    if(down){
        ySpeedFirstPad = 5;
    }
    if((down && up) || (!down && !up)){
        ySpeedFirstPad = 0;
    }
    //Movement
    firstPad.move(0,ySpeedFirstPad);
    // Check if not out of bound
    if(firstPad.getPosition().y < 0){
        firstPad.setPosition(10,0);
    }
    if(firstPad.getPosition().y > 500){
        firstPad.setPosition(10,500);
    }
    // Logic of pad2
    if(ball.getPosition().y < secondPad.getPosition().y){
        ySpeedSecondPad = -4;
    }
    if(ball.getPosition().y > secondPad.getPosition().y){
        ySpeedSecondPad = 4;
    }
    secondPad.move(0,ySpeedSecondPad);

    //Logic of ball
    ball.move(xSpeedBall,ySpeedBall);
    // Check if not out of bound
    // in questo caso devo invertire l'asse y
    if(ball.getPosition().y < 0){
        ySpeedBall = -ySpeedBall;
    }
    if(ball.getPosition().y > 550){
        ySpeedBall = -ySpeedBall;
    }
    if(ball.getGlobalBounds().intersects(firstPad.getGlobalBounds())){
        xSpeedBall = -xSpeedBall;
        hit.play();
    }
    if(ball.getGlobalBounds().intersects(secondPad.getGlobalBounds())){
        xSpeedBall = -xSpeedBall;
        hit.play();
    }

    if(ball.getPosition().x < 25){
        pad2score++;
        ball.setPosition(300,200);
    }
    if(ball.getPosition().x > 750){
        pad1score++;
        ball.setPosition(300,200);
    }

}

/* Rendering part */
void renderingPart(){
    mainWindow.clear();

    /* Drawing part */
    mainWindow.draw(background);
    mainWindow.draw(firstPad);
    mainWindow.draw(secondPad);
    mainWindow.draw(ball);
    mainWindow.draw(pause);
    std::stringstream text;
    text << pad1score << " : " << pad2score;
    score.setString(text.str());
    mainWindow.draw(score);
    mainWindow.display();
}

/* adding difficulty every 30 seconds */

void timer_start(std::function<void(void)> func, unsigned int interval){
    std::thread([func, interval]() {
        while (true){
            func();
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}


void add_difficulty(){
    if(xSpeedBall > -8 && ySpeedBall > -8){
        xSpeedBall--;
        ySpeedBall--;
    }
    if(ySpeedSecondPad < 0){
        if(ySpeedSecondPad > -7)
            ySpeedSecondPad--;
    }else{
        if(ySpeedSecondPad < 7)
        ySpeedSecondPad++;
    }

    if(ySpeedFirstPad <0){
        if(pad1score>=soglia && ySpeedFirstPad>-10){
            soglia += 5;
            ySpeedFirstPad--;
        }
    }else{
        if(pad1score>=soglia && ySpeedFirstPad<10){
            soglia += 5;
            ySpeedFirstPad++;
        }
    }


}