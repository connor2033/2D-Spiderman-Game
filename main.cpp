#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <math.h>


using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Final Project");
    window.setFramerateLimit(60);

    Texture tex1;
    tex1.loadFromFile("spiderman.png");

    Texture tex2;
    tex2.loadFromFile("Background.png");

    Texture tex3;
    tex3.loadFromFile("Background.png");

    //making spiderman sprite
    Sprite spidey;
    spidey.setTexture(tex1);
    spidey.setTextureRect(IntRect(70,33,26,63));
    spidey.setPosition(350,320);
    spidey.setScale(4,4);

    Sprite background1;
    background1.setTexture(tex2);
    background1.setPosition(0,0);

    Sprite background2;
    background2.setTexture(tex3);
    background2.setPosition(-1600,0);





    bool wleft = false;
    bool wright = false;

    Clock c1;
    Time t1;



    bool isJump = false;

    bool crawl = false;
    bool crouch = false;






    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }



        t1 = c1.getElapsedTime();









///////////////////////////////////////////////////////MOVEMENTS


        if (isJump == false){
        spidey.setTextureRect(IntRect(21,33,26,63));

        //crawl left
        if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left)){
            //spidey.move(-2,0);
            background1.move(2,0);
            background2.move(2,0);
            spidey.setTextureRect(IntRect(abs(int(background1.getPosition().x/20)%4)*68+23,218,62,27));
            wleft = true;
            wright = false;
            crawl = true;
            crouch = false;
        }
        //crawl right
        else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right)){
            //spidey.move(2,0);
            background1.move(-2,0);
            background2.move(-2,0);
            spidey.setTextureRect(IntRect(abs(int(background1.getPosition().x/20)%4)*68+23,218,62,27));
            wleft = false;
            wright = true;
            crawl = true;
            crouch = false;
        }

        //walk left
        else if(Keyboard::isKeyPressed(Keyboard::Left)){
            //spidey.move(-3,0);
            background1.move(3,0);
            background2.move(3,0);
            spidey.setTextureRect(IntRect(abs(int(background1.getPosition().x/24)%4)*35+19,125,34,66));
            wleft = true;
            wright = false;
            crawl = false;
            crouch = false;
        }
        //walk right
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            //spidey.move(3,0);
            background1.move(-3,0);
            background2.move(-3,0);
            spidey.setTextureRect(IntRect(abs(int(background1.getPosition().x/24)%4)*35+19,125,34,66));
            wleft = false;
            wright = true;
            crawl = false;
            crouch = false;
        }

        //crouch
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            spidey.setTextureRect(IntRect(114,66,40,32));
            crawl = false;
            crouch = true;
        }
        //crawl up


        else {
            wleft = false;
            wright = false;
        }
        }



///////////////////////////////////////////////////GRAVITY

        if (Keyboard::isKeyPressed(Keyboard::Up) && t1.asSeconds() < 0.9 && crawl == false && crouch == false){
                isJump = true;
        }


        if (isJump == true){

        spidey.move(0,-80*t1.asSeconds()-0.5*-250*t1.asSeconds()*t1.asSeconds());

        spidey.setTextureRect(IntRect(188,128,46,59));

        if (wleft == true){
            background1.move(5,0);
            background2.move(5,0);
        }

        if (wright == true){
        background1.move(-5,0);
        background2.move(-5,0);
        }

// maybe make jumping texture change with function?
        }
        else {
            c1.restart();
        }

        if (spidey.getPosition().y >= 320){
            isJump = false;
            spidey.setPosition(spidey.getPosition().x, spidey.getPosition().y);

        }






/////////////////////Scrolling Backgroung


        if (background1.getPosition().x < -800){
            background2.setPosition(background1.getPosition().x + 1600, 0);
        }

        if (background2.getPosition().x < -800){
            background1.setPosition(background2.getPosition().x + 1600, 0);
        }

        if (background1.getPosition().x > 0){
            background2.setPosition(background1.getPosition().x - 1600, 0);
        }

        if (background2.getPosition().x > 0){
            background1.setPosition(background2.getPosition().x - 1600, 0);
        }








//////////////////////////////////////////idle





        //Scale
        if (wleft == true){
            spidey.setScale(-4,4);
        }
        else if (wright == true){
            spidey.setScale(4,4);
        }




        if (isJump == false){

        if (crawl == true){ spidey.setPosition(spidey.getPosition().x,390);
        crawl = false;
        }

        else if (crouch == true){ spidey.setPosition(spidey.getPosition().x,386);
        crouch = false;
        }

        else spidey.setPosition(spidey.getPosition().x,250);
        }






















        window.clear(Color(Color::Cyan));
        window.draw(background1);
        window.draw(background2);
        window.draw(spidey);
        window.display();
    }

    return 0;
}

