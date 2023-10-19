#include "WindowSetting.h"
// #include "Object.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(win_width, win_height), "A big challenge for programmers is naming.");

    window.setFramerateLimit(fps);

    Texture sliceSheet;
    if (!sliceSheet.loadFromFile("./images/slice_sheet.png")) {
        return 1;
    }

    Texture baseImage;
    if (!baseImage.loadFromFile("./images/slice1.png")) {
        return 1;
    }

    Texture fruit;
    if (!fruit.loadFromFile("./images/melon.png")) {
        return 1;
    }
    Vector2u textureSize = fruit.getSize();

    Sprite sliceSprite;
    sliceSprite.setTexture(sliceSheet);
    sliceSprite.setTextureRect(IntRect(0, 0, 256, 256));
    sliceSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    Sprite baseSprite;
    baseSprite.setTexture(baseImage);
    baseSprite.setTextureRect(IntRect(0, 0, 256, 256));
    baseSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    Sprite fruitSprite0;
    fruitSprite0.setTexture(fruit);
    fruitSprite0.setScale(0.4f, 0.4f);
    fruitSprite0.setPosition(win_width / 2, -70);
    fruitSprite0.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite1;
    fruitSprite1.setTexture(fruit);
    fruitSprite1.setScale(0.4f, 0.4f);
    fruitSprite1.setPosition(win_width + 70, -70);
    fruitSprite1.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite2;
    fruitSprite2.setTexture(fruit);
    fruitSprite2.setScale(0.4f, 0.4f);
    fruitSprite2.setPosition(win_width + 70, win_height / 2);
    fruitSprite2.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite3;
    fruitSprite3.setTexture(fruit);
    fruitSprite3.setScale(0.4f, 0.4f);
    fruitSprite3.setPosition(win_width + 70, win_height + 70);
    fruitSprite3.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite4;
    fruitSprite4.setTexture(fruit);
    fruitSprite4.setScale(0.4f, 0.4f);
    fruitSprite4.setPosition(win_width / 2, win_height + 70);
    fruitSprite4.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite5;
    fruitSprite5.setTexture(fruit);
    fruitSprite5.setScale(0.4f, 0.4f);
    fruitSprite5.setPosition(-70, win_height + 70);
    fruitSprite5.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite6;
    fruitSprite6.setTexture(fruit);
    fruitSprite6.setScale(0.4f, 0.4f);
    fruitSprite6.setPosition(-70, win_height/2);
    fruitSprite6.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Sprite fruitSprite7;
    fruitSprite7.setTexture(fruit);
    fruitSprite7.setScale(0.4f, 0.4f);
    fruitSprite7.setPosition(-70, -70);
    fruitSprite7.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Clock clock;
    float frameTime = 0.15f;
    float deltaTime = 0.0f;
    int currentFrame = 0;
    bool slash = 0;
    bool fruit_distroy[] = { false, false, false, false, false, false, false, false };

    unsigned int score = 0;
    int move_random;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(10, 20);

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }
        Vector2f fpos[] = { fruitSprite0.getPosition(), fruitSprite1.getPosition(), fruitSprite2.getPosition(), fruitSprite3.getPosition(), fruitSprite4.getPosition(), fruitSprite5.getPosition(),fruitSprite6.getPosition(), fruitSprite7.getPosition()};

        //과일 파괴 안되었으면 각자의 방향으로 계속 나아감.
        //  7  0  1
        //  6     2
        //  5  4  3
        move_random = distribution(gen);
        if (!fruit_distroy[0]) {
            fruitSprite0.setPosition(fpos[0].x, fpos[0].y + move_random);
        }
        if (!fruit_distroy[1]) {
            fruitSprite1.setPosition(fpos[1].x - move_random, fpos[1].y + move_random);
        }
        if (!fruit_distroy[2]) {
            fruitSprite2.setPosition(fpos[2].x - move_random, fpos[2].y);
        }
        if (!fruit_distroy[3]) {
            fruitSprite3.setPosition(fpos[3].x - move_random, fpos[3].y - move_random);
        }
        if (!fruit_distroy[4]) {
            fruitSprite4.setPosition(fpos[4].x, fpos[4].y - move_random);
        }
        if (!fruit_distroy[5]) {
            fruitSprite5.setPosition(fpos[5].x + move_random, fpos[5].y - move_random);
        }
        if (!fruit_distroy[6]) {
            fruitSprite6.setPosition(fpos[6].x + move_random, fpos[6].y);
        }
        if (!fruit_distroy[7]) {
            fruitSprite7.setPosition(fpos[7].x + move_random, fpos[7].y + move_random);
        }

        //과일에 맞는 키보드 감지
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            !fruit_distroy[0];
            fruitSprite0.setPosition(win_width / 2, -70);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            !fruit_distroy[1];
            fruitSprite1.setPosition(win_width + 70, -70);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            !fruit_distroy[2];
            fruitSprite2.setPosition(win_width + 70, win_height / 2);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::C)) {
            !fruit_distroy[3];
            fruitSprite3.setPosition(win_width + 70, win_height + 70);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            !fruit_distroy[4];
            fruitSprite4.setPosition(win_width / 2, win_height + 70);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            !fruit_distroy[5];
            fruitSprite5.setPosition(-70, win_height + 70);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            !fruit_distroy[6];
            fruitSprite6.setPosition(-70, win_height / 2);
            slash = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            !fruit_distroy[7];
            fruitSprite7.setPosition(-70, -70);
            slash = true;
        }

        deltaTime += clock.restart().asSeconds();
        if (slash) {
            if (deltaTime >= frameTime) {
                currentFrame = (currentFrame+1);
                sliceSprite.setTextureRect(sf::IntRect(currentFrame * 256, 0, 256, 256));
                deltaTime -= frameTime;
            }
            window.clear();
            window.draw(sliceSprite);
            if (currentFrame == 1) {
                deltaTime = 0;
                currentFrame = -1;
                slash = false;
            }
        }else {
            deltaTime = 0;
            window.clear();
            window.draw(baseSprite);
        }

        window.draw(fruitSprite0);
        window.draw(fruitSprite1);
        window.draw(fruitSprite2);
        window.draw(fruitSprite3);
        window.draw(fruitSprite4);
        window.draw(fruitSprite5);
        window.draw(fruitSprite6);
        window.draw(fruitSprite7);

        window.display();
    }
}
