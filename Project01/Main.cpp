#include "WindowSetting.h"
// #include "Object.h"
#include <iostream>
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
    if (!fruit.loadFromFile("./images/temp_fruit.jpg")) {
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

    Sprite fruitSprite;
    fruitSprite.setTexture(fruit);
    fruitSprite.setScale(0.4f, 0.4f);
    fruitSprite.setPosition(0, 0);
    fruitSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);

    Clock clock;
    float frameTime = 0.15f;
    float deltaTime = 0.0f;
    int currentFrame = 0;
    bool isPressed = 0;
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }
        Vector2f fpos = fruitSprite.getPosition();
        fruitSprite.setPosition(fpos.x + 1 , fpos.y + 1);

        deltaTime += clock.restart().asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::Space))
            isPressed = true;

        if (isPressed) {
            cout<< "실행데스" << endl;
            if (deltaTime >= frameTime) {
                cout << "이프문 통과데스" << endl;
                currentFrame = (currentFrame+1);
                sliceSprite.setTextureRect(sf::IntRect(currentFrame * 256, 0, 256, 256));
                deltaTime -= frameTime;
            }
            window.clear();
            window.draw(sliceSprite);
            if (currentFrame == 1) {
                cout << "왜유" << endl;
                deltaTime = 0;
                currentFrame = -1;
                isPressed = false;
            }
        }else {
            deltaTime = 0;
            window.clear();
            window.draw(baseSprite);
        }

        window.draw(fruitSprite);

        window.display();
    }
}
