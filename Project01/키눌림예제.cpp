#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define CIRCLE_RADIUS   100.f

int main()
{
    float x = 0, y = 0;


    //Ű���� �Է� ���� ������ RectangleShape ��ü
    RectangleShape rect_shape(Vector2f(200, 200));
    RectangleShape small_rect_shape(Vector2f(10, 10));

    rect_shape.setFillColor(Color::Green);
    rect_shape.setOutlineColor(sf::Color::Red);
    rect_shape.setOutlineThickness(20);
    rect_shape.setPosition(x, y);

    small_rect_shape.setFillColor(Color::Yellow);
    small_rect_shape.setOutlineColor(sf::Color::Blue);
    small_rect_shape.setOutlineThickness(20);
    small_rect_shape.setPosition(x, y);

    cout << "���α׷��� ���۵Ǿ����ϴ�." << endl;

    //ȭ�� ũ��, ĸ�� �̸� ����
    RenderWindow app(VideoMode(504, 504), "https://maincodes.tistory.com/");
    app.setFramerateLimit(60);  //������ ���� ����

    //SFML ���� ���� - �����찡 ������ ���� �ݺ�
    while (app.isOpen())
    {
        Event event;

        //�̺�Ʈ ó��
        while (app.pollEvent(event))
        {
            //���α׷� ���� �̺�Ʈ ó��
            if (event.type == Event::EventType::Closed)
            {
                app.close();
                cout << "���α׷��� ����Ǿ����ϴ�." << endl;
            }

            //Ű���� ����(Pressed) �̺�Ʈ
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Left:
                {
                    cout << "Left Ű ���� " << endl;
                    x -= 10;
                    break;
                }

                case Keyboard::Right:
                {
                    cout << "Right Ű ���� " << endl;
                    x += 10;
                    break;
                }

                case Keyboard::Up:
                {
                    cout << "UP Ű ���� " << endl;
                    y -= 10;
                    break;
                }

                case Keyboard::Down:
                {
                    cout << "Down Ű ���� " << endl;
                    y += 10;
                    break;
                }

                case Keyboard::Space:
                {
                    cout << "Space Ű ���� " << endl;

                    float speed = 3;

                    //���� �簢�� �ִϸ��̼� ȿ��
                    for (int i = 0; i < 50; i += speed)
                    {
                        small_rect_shape.move(speed * 1, speed * 1);
                        app.draw(small_rect_shape);
                        app.display();
                    }

                    //���� �簢�� �� ��ġ
                    small_rect_shape.setPosition(Vector2f((float)x, (float)y));
                    break;
                }
                default:
                    cout << "Ű ����((key.code) = " << event.key.code << endl;
                    break;
                }
            }
            if (event.type == Event::KeyReleased)
                cout << "Ű ����((key.code) = " << event.key.code << endl;
        }

        //���ȭ���� ������� clear
        app.clear(Color::White);

        //rect_shape ��ġ ����
        rect_shape.setPosition(Vector2f(x - 100.f, y - 100.f));
        app.draw(rect_shape);

        app.draw(small_rect_shape);

        //�������� ��ũ���� ���
        app.display();
    }

    return 0;
}
