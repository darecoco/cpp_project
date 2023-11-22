#include "WindowSetting.h"
// #include "Object.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace std;
using namespace sf;

class Fruit {
public:
    Fruit(Texture texture, float point_x, float point_y) : texture_(texture), point_x_(point_x), point_y_(point_y)
    {
        fruit_.setTexture(texture_);
        fruit_.setScale(0.2f, 0.2f);
        fruit_.setPosition(point_x_, point_y_);
        fruit_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
    }

    auto getSprite() {
        return fruit_;
    }
    auto getPoint() {
        return fruit_.getPosition();
    }

    void setPoint(float x, float y) {
        fruit_.setPosition(x, y);
    }

    boolean fruitInFrame(int num) {
        switch (num) {
        case 0: if (fruit_.getPosition().y >= 0) return true; break;
        case 1: if (fruit_.getPosition().y >= 0) return true; break;
        case 2: if (fruit_.getPosition().x <= win_width) return true; break;
        case 3: if (fruit_.getPosition().y <= win_height) return true; break;
        case 4: if (fruit_.getPosition().y <= win_height) return true; break;
        case 5: if (fruit_.getPosition().y <= win_height) return true; break;
        case 6: if (fruit_.getPosition().x >= 0) return true; break;
        case 7: if (fruit_.getPosition().y >= 0) return true; break;
        }
        return false;
    }

private:
    Sprite fruit_;
    Texture texture_;
    float point_x_;
    float point_y_;
};

int main() {
    RenderWindow window(VideoMode(win_width, win_height), "A big challenge for programmers is naming.");

    window.setFramerateLimit(fps);

    //텍스쳐 불러오기
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

    //텍스쳐 사이즈 조정
    Vector2u textureSize = fruit.getSize();

    //점수용 폰트 불러오기
    Text text;
    Font font; 
    if (!font.loadFromFile("./fonts/NeoDunggeunmoPro-Regular.ttf")) {
        return EXIT_FAILURE;
    }
    text.setFont(font);
    text.setPosition(0, 0);

    //랜덤 초기화
    random_device sr; //show random
    mt19937 show(sr());
    uniform_int_distribution<int> show_ran(textureSize.x / 2 + 20, textureSize.x * 3);

    random_device mr; //move random
    mt19937 move(mr());
    uniform_int_distribution<int> move_ran(5, 10);

    //스프라이트 불러오기
    Sprite sliceSprite;
    sliceSprite.setTexture(sliceSheet);
    sliceSprite.setTextureRect(IntRect(0, 0, 256, 256));
    sliceSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    Sprite baseSprite;
    baseSprite.setTexture(baseImage);
    baseSprite.setTextureRect(IntRect(0, 0, 256, 256));
    baseSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    //과일 0~9 초기화
    Fruit fruit0 = Fruit(fruit, win_width / 2, -70);
    Fruit fruit1 = Fruit(fruit, win_width + 90, -90);
    Fruit fruit2 = Fruit(fruit, win_width + 110, win_height / 2);
    Fruit fruit3 = Fruit(fruit, win_width + 130, win_height + 130);
    Fruit fruit4 = Fruit(fruit, win_width / 2, win_height + 70);
    Fruit fruit5 = Fruit(fruit, -170, win_height + 170);
    Fruit fruit6 = Fruit(fruit, -190, win_height / 2);
    Fruit fruit7 = Fruit(fruit, -210, -210);

    //초시계관련 초기화
    Clock clock;
    float frameTime = 0.15f;
    float deltaTime = 0.0f;
    int currentFrame = 0;

    //각종 변수 초기화
    unsigned int score = 0;
    int move_random, show_random;
    bool slash = 0;
    bool fruit_distroy[] = { true, true, true, true, true, true, true, true };

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
            }
            Vector2f fpos[] = { fruit0.getPoint(), fruit1.getPoint(), fruit2.getPoint(), fruit3.getPoint(), fruit4.getPoint(), fruit5.getPoint(),fruit6.getPoint(), fruit7.getPoint() };
            text.setString(L"점수 : " + to_string(score));
            text.setCharacterSize(score/5);

            //과일 파괴 안되었으면 각자의 방향으로 계속 나아감.
            //  7  0  1
            //  6     2
            //  5  4  3
            move_random = move_ran(move);
            fruit0.setPoint(fpos[0].x, fpos[0].y + move_random);
            fruit1.setPoint(fpos[1].x - move_random, fpos[1].y + move_random);
            fruit2.setPoint(fpos[2].x - move_random, fpos[2].y);
            fruit3.setPoint(fpos[3].x - move_random, fpos[3].y - move_random);
            fruit4.setPoint(fpos[4].x, fpos[4].y - move_random);
            fruit5.setPoint(fpos[5].x + move_random, fpos[5].y - move_random);
            fruit6.setPoint(fpos[6].x + move_random, fpos[6].y);
            fruit7.setPoint(fpos[7].x + move_random, fpos[7].y + move_random);

            //과일에 맞는 키보드 감지
            show_random = show_ran(show);
            if (Keyboard::isKeyPressed(Keyboard::Numpad8) && fruit_distroy[0]) {
                fruit_distroy[0] = false;
                fruit0.setPoint(win_width / 2, -show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad9) && fruit_distroy[1]) {
                fruit_distroy[1] = false;
                fruit1.setPoint(win_width + show_random, -show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad6) && fruit_distroy[2]) {
                fruit_distroy[2] = false;
                fruit2.setPoint(win_width + show_random, win_height / 2);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad3) && fruit_distroy[3]) {
                fruit_distroy[3] = false;
                fruit3.setPoint(win_width + show_random, win_height + show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad2) && fruit_distroy[4]) {
                fruit_distroy[4] = false;
                fruit4.setPoint(win_width / 2, win_height + show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad1) && fruit_distroy[5]) {
                fruit_distroy[5] = false;
                fruit5.setPoint(-show_random, win_height + show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad4) && fruit_distroy[6]) {
                fruit_distroy[6] = false;
                fruit6.setPoint(-show_random, win_height / 2);
                score += 5;
                slash = true;
                currentFrame = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Numpad7) && fruit_distroy[7]) {
                fruit_distroy[7] = false;
                fruit7.setPoint(-show_random, -show_random);
                score += 5;
                slash = true;
                currentFrame = 0;
            }

            //과일이 프레임 안에 있는가 -> 파괴 가능
            fruit_distroy[0] = fruit0.fruitInFrame(0);
            fruit_distroy[1] = fruit1.fruitInFrame(1);
            fruit_distroy[2] = fruit2.fruitInFrame(2);
            fruit_distroy[3] = fruit3.fruitInFrame(3);
            fruit_distroy[4] = fruit4.fruitInFrame(4);
            fruit_distroy[5] = fruit5.fruitInFrame(5);
            fruit_distroy[6] = fruit6.fruitInFrame(6);
            fruit_distroy[7] = fruit7.fruitInFrame(7);

            deltaTime += clock.restart().asSeconds();

            //쥔공 칼질 모션
            if (slash) {
                sliceSprite.setTextureRect(sf::IntRect(currentFrame * 256, 0, 256, 256));
                if (deltaTime >= frameTime) {
                    currentFrame++;
                    deltaTime = 0;
                }
                window.clear();
                window.draw(sliceSprite);
                if (currentFrame == 2) {
                    slash = false;
                    continue;
                }
            }else {
                currentFrame = 0;
                deltaTime = 0;
                window.clear();
                window.draw(baseSprite);
            }

            //과일과 점수 그리기
            window.draw(fruit0.getSprite());
            window.draw(fruit1.getSprite());
            window.draw(fruit2.getSprite());
            window.draw(fruit3.getSprite());
            window.draw(fruit4.getSprite());
            window.draw(fruit5.getSprite());
            window.draw(fruit6.getSprite());
            window.draw(fruit7.getSprite());
            window.draw(text);
            window.display();
        }

    }
}
