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
    bool isPressed = 0;
    bool fruit_distroy[] = { false, false, false, false, false, false, false, false };

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }
        Vector2f fpos7 = fruitSprite7.getPosition();
        Vector2f fpos6 = fruitSprite6.getPosition();

        //과일 파괴 안되었으면 각자의 방향으로 계속 나아감.
        //  7  0  1
        //  6     2
        //  5  4  3
        if (!fruit_distroy[7]) {
            fruitSprite7.setPosition(fpos7.x + 1 , fpos7.y + 1);
        }
        if (!fruit_distroy[6]) {
            fruitSprite6.setPosition(fpos6.x + 2, fpos6.y);
        }

        //과일에 맞는 키보드 감지
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            !fruit_distroy[7];
            fruitSprite7.setPosition(-70, -70);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            !fruit_distroy[6];
            fruitSprite6.setPosition(-70, win_height / 2);
        }

        deltaTime += clock.restart().asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::Space))
            isPressed = true;

        if (isPressed) {
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
                isPressed = false;
            }
        }else {
            deltaTime = 0;
            window.clear();
            window.draw(baseSprite);
        }

        window.draw(fruitSprite7);
        window.draw(fruitSprite6);

        window.display();
    }
}
