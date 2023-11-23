#include "WindowSetting.h"
// #include "Object.h"
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace std;
using namespace sf;

const int win_width = 800;
const int win_height = 800;
const int fps = 30;

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
        case 0: if (fruit_.getPosition().y >= 0)  return true; break;
        case 1: if (fruit_.getPosition().y >= 0) return true; break;
        case 2: if (fruit_.getPosition().x <= win_width)  return true; break;
        case 3: if (fruit_.getPosition().y <= win_height) return true; break;
        case 4: if (fruit_.getPosition().y <= win_height) return true; break;
        case 5: if (fruit_.getPosition().y <= win_height) return true; break;
        case 6: if (fruit_.getPosition().x >= 0) return true; break;
        case 7: if (fruit_.getPosition().y >= 0)  return true; break;
        }
        return false;
    }

    boolean fruitOverFrame(int num) {
        switch (num) {
        case 0: if (fruit_.getPosition().y >= win_height) return true; break;
        case 1: if (fruit_.getPosition().y >= win_height) return true; break;
        case 2: if (fruit_.getPosition().x <= 0) return true; break;
        case 3: if (fruit_.getPosition().y <= 0) return true; break;
        case 4: if (fruit_.getPosition().y <= 0) return true; break;
        case 5: if (fruit_.getPosition().y <= 0) return true; break;
        case 6: if (fruit_.getPosition().x >= win_width) return true; break;
        case 7: if (fruit_.getPosition().y >= win_height) return true; break;
        }
        return false;
    }

private:
    Sprite fruit_;
    Texture texture_;
    float point_x_;
    float point_y_;
};

class Texts {
public:
    Texts(int x, int y) : x_(x), y_(y) {
        if (!font_.loadFromFile("./fonts/NeoDunggeunmoPro-Regular.ttf")) {
            exit;
        }
        text_.setFont(font_);
        text_.setPosition(x, y);
    }

    Text getText() {
        return text_;
    }

    void setText(wstring s) {
        text_.setString(s);
    }

    void setSize(int size) {
        text_.setCharacterSize(size);
    }

private:
    Font font_;
    Text text_;
    int x_;
    int y_;
};

int main() {
    RenderWindow window(VideoMode(win_width, win_height), "A big challenge for programmers is naming.");

    window.setFramerateLimit(fps);
    window.setKeyRepeatEnabled(false);

    //�ؽ��� �ҷ�����
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

    Texture title;
    if (!title.loadFromFile("./images/title.png")) {
        return 1;
    }

    Texture end;
    if (!end.loadFromFile("./images/gameOver.png")) {
        return 1;
    }

    Texture discription1, discription2, discription3;
    if (!discription1.loadFromFile("./images/discription1.png")) {
        return 1;
    }
    if (!discription2.loadFromFile("./images/discription2.png")) {
        return 1;
    }
    if (!discription3.loadFromFile("./images/discription2.png")) {
        return 1;
    }
    Texture ruleImage[] = {
        discription1,
        discription2,
        discription3
    };

    //�ؽ��� ������ ����
    Vector2u textureSize = fruit.getSize();

    //�ؽ�Ʈ�� �ʱ�ȭ
    Texts scoreText(0, 0);

    Texts gameStartText(550, 570);
    gameStartText.setText(L"[S] ���� ����");
    gameStartText.setSize(30);

    Texts gameRule(550, 650);
    gameRule.setText(L"[R] ���� ���");
    gameRule.setSize(30);

    Texts gameExitText(550, 730);
    gameExitText.setText(L"[X] ���� ������");
    gameExitText.setSize(30);

    Texts retry(550, 650);
    retry.setText(L"[M] ���� ȭ��");
    retry.setSize(30);

    Texts finalScore(110, 80);
    finalScore.setSize(50);

    //���� ���� ��
    wstring rule[] = {
        L"�˰������� ��濡�� ���ƿ��� ���ϵ���\n�ִ��� ���� �� ���� ������� ����˴ϴ�.",
        L"Numpad�� ����Ű�θ� ���ϵ��� �ĳ� �� �ֽ��ϴ�.\n������ ȭ���� �Ѿ�ų�\n������ ���� ���� Į���ϸ� ���ӿ���!",
        L"������ Ŀ����, Į���ϸ� ���ϵ��� ��� �������� ��\n�Ž����� ���ظ� ���ư��� ������ ġ�ﺸ����."
    };
    Texts discriptionText(80, 610);
    discriptionText.setText(rule[0]);

    Texts arrowText(60, 740);
    arrowText.setText(L"[��] ���� ������\t[B] ���ư���\t[��] ���� ������");

    //���� �ʱ�ȭ
    random_device sr; //show random
    mt19937 show(sr());
    uniform_int_distribution<int> show_ran(textureSize.x / 2 + 20, textureSize.x * 3);

    random_device mr; //move random
    mt19937 move(mr());
    uniform_int_distribution<int> move_ran(5, 10);

    //��������Ʈ �ҷ�����
    Sprite sliceSprite;
    sliceSprite.setTexture(sliceSheet);
    sliceSprite.setTextureRect(IntRect(0, 0, 256, 256));
    sliceSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    Sprite baseSprite;
    baseSprite.setTexture(baseImage);
    baseSprite.setTextureRect(IntRect(0, 0, 256, 256));
    baseSprite.setPosition(win_width / 2 - 256 / 2, win_height / 2 - 256 / 2);

    Sprite startScreen;
    startScreen.setTexture(title);
    startScreen.setPosition(0, 0);

    Sprite discription;
    discription.setTexture(discription1);
    discription.setPosition(150, 100);

    Sprite endScreen;
    endScreen.setTexture(end);
    endScreen.setPosition(0, 0);

    //���� 0~9 �ʱ�ȭ
    Fruit fruit0 = Fruit(fruit, win_width / 2, -70);
    Fruit fruit1 = Fruit(fruit, win_width + 90, -90);
    Fruit fruit2 = Fruit(fruit, win_width + 110, win_height / 2);
    Fruit fruit3 = Fruit(fruit, win_width + 130, win_height + 130);
    Fruit fruit4 = Fruit(fruit, win_width / 2, win_height + 70);
    Fruit fruit5 = Fruit(fruit, -170, win_height + 170);
    Fruit fruit6 = Fruit(fruit, -190, win_height / 2);
    Fruit fruit7 = Fruit(fruit, -210, -210);

    //�ʽð���� �ʱ�ȭ
    Clock clock;
    float frameTime = 0.1f;
    float deltaTime = 0.0f;
    int currentFrame = 0;

    //���� ���� �ʱ�ȭ
    unsigned int score = 0;
    int move_random, show_random;
    bool slash = 0;
    bool fruit_distroy[] = { true, true, true, true, true, true, true, true };
    bool gameOver = false;
    bool titleScreen = true;

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }
        
        //���� ȭ��
        while (titleScreen && window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                titleScreen = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                //���� ��� â
                 int ruleNum = 0;
                while (window.isOpen()) {
                    Event e;
                    while (window.pollEvent(e)) {
                        if (e.type == Event::Closed)
                            window.close();
                        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                            if (++ruleNum > 2) ruleNum = 2;
                            cout << ruleNum << endl;
                            discription.setTexture(ruleImage[ruleNum]);
                            discriptionText.setText(rule[ruleNum]);
                        }else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                            if (--ruleNum < 0) ruleNum = 0;
                            discription.setTexture(ruleImage[ruleNum]);
                            discriptionText.setText(rule[ruleNum]);
                        }
                        window.clear();
                        window.draw(discription);
                        window.draw(discriptionText.getText());
                        window.draw(arrowText.getText());
                        window.display();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::B)) {
                        break;
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::X)) {
                return 0;
            }
            window.draw(startScreen);
            window.draw(gameStartText.getText());
            window.draw(gameRule.getText());
            window.draw(gameExitText.getText());

            window.display();
        }

        while (window.isOpen()) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
            }
            Vector2f fpos[] = { fruit0.getPoint(), fruit1.getPoint(), fruit2.getPoint(), fruit3.getPoint(), fruit4.getPoint(), fruit5.getPoint(),fruit6.getPoint(), fruit7.getPoint() };
            scoreText.setText(L"���� : " + to_string(score));
            scoreText.setSize(score/5);

            //���� �ı� �ȵǾ����� ������ �������� ��� ���ư�.
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

            //���Ͽ� �´� Ű���� ����
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

            //������ ������ �ȿ� �ִ°� -> �ı� ����
            fruit_distroy[0] = fruit0.fruitInFrame(0);
            fruit_distroy[1] = fruit1.fruitInFrame(1);
            fruit_distroy[2] = fruit2.fruitInFrame(2);
            fruit_distroy[3] = fruit3.fruitInFrame(3);
            fruit_distroy[4] = fruit4.fruitInFrame(4);
            fruit_distroy[5] = fruit5.fruitInFrame(5);
            fruit_distroy[6] = fruit6.fruitInFrame(6);
            fruit_distroy[7] = fruit7.fruitInFrame(7);

            //������ �������� �Ѿ�°� -> ���� ����
            gameOver = fruit0.fruitOverFrame(0);
            gameOver = fruit2.fruitOverFrame(2);
            gameOver = fruit3.fruitOverFrame(3);
            gameOver = fruit4.fruitOverFrame(4);
            gameOver = fruit5.fruitOverFrame(5);
            gameOver = fruit6.fruitOverFrame(6);
            gameOver = fruit7.fruitOverFrame(7);

            if (gameOver) {
                finalScore.setText(L"��������!\n����� ������...\n" + to_string(score) + L"�� �Դϴ�. \n�����ϼ̽��ϴ�.");
                break;
            }

            deltaTime += clock.restart().asSeconds();

            //��� Į�� ���
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

            //���ϰ� ���� �׸���
            window.draw(fruit0.getSprite());
            window.draw(fruit1.getSprite());
            window.draw(fruit2.getSprite());
            window.draw(fruit3.getSprite());
            window.draw(fruit4.getSprite());
            window.draw(fruit5.getSprite());
            window.draw(fruit6.getSprite());
            window.draw(fruit7.getSprite());
            window.draw(scoreText.getText());
            window.display();

        }

        while (gameOver) {
            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close();
                else if (Keyboard::isKeyPressed(Keyboard::M)) {
                    cout << "�����" << endl;
                    titleScreen = true;
                    gameOver = false;
                    break;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::X)) {
                return 0;
            }

            window.draw(endScreen);
            window.draw(gameExitText.getText());
            window.draw(retry.getText());
            window.draw(finalScore.getText());
            window.display();
        }
    }
}
