#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation");

    sf::Texture spriteSheetTexture;
    if (!spriteSheetTexture.loadFromFile("./images/slice_sheet.png")) {
        return 1;
    }

    sf::Sprite characterSprite;
    characterSprite.setTexture(spriteSheetTexture);
    characterSprite.setTextureRect(sf::IntRect(0, 0, 256, 560)); // 첫 번째 프레임 위치와 크기 설정

    sf::Clock clock;
    float frameTime = 0.2f; // 각 프레임 간 시간 간격 (초)
    float deltaTime = 0.0f; // 누적된 시간
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
            currentFrame = (currentFrame + 1) % 3; // 6은 프레임의 총 개수
            characterSprite.setTextureRect(sf::IntRect(currentFrame * 256, 0, 256, 256)); // 다음 프레임 위치 설정
            deltaTime -= frameTime; // 누적된 시간에서 프레임 시간을 빼줌
        }

        window.clear();
        window.draw(characterSprite);
        window.display();
    }

    return 0;
}
