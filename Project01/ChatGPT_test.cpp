#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation");

    sf::Texture spriteSheetTexture;
    if (!spriteSheetTexture.loadFromFile("./images/slice_sheet.png")) {
        return 1;
    }

    sf::Sprite characterSprite;
    characterSprite.setTexture(spriteSheetTexture);
    characterSprite.setTextureRect(sf::IntRect(0, 0, 256, 560)); // ù ��° ������ ��ġ�� ũ�� ����

    sf::Clock clock;
    float frameTime = 0.2f; // �� ������ �� �ð� ���� (��)
    float deltaTime = 0.0f; // ������ �ð�
    int currentFrame = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        deltaTime += clock.restart().asSeconds();
        if (deltaTime >= frameTime) {
            currentFrame = (currentFrame + 1) % 3; // 6�� �������� �� ����
            characterSprite.setTextureRect(sf::IntRect(currentFrame * 256, 0, 256, 256)); // ���� ������ ��ġ ����
            deltaTime -= frameTime; // ������ �ð����� ������ �ð��� ����
        }

        window.clear();
        window.draw(characterSprite);
        window.display();
    }

    return 0;
}
