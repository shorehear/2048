#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

const int windowSize = 500;
const int numRows = 4; // Количество строк на доске
const int numCols = 4; // Количество столбцов на доске
std::array<std::array<int, numCols>, numRows> board{}; // Игровая доска

// Генерация случайной плитки
void generateRandomTile(std::array<std::array<int, numCols>, numRows>& board) {
    int row, col;
    do {
        row = rand() % numRows;
        col = rand() % numCols;
    } while (board[row][col] != 0);
    int value = (rand() % 10 == 0) ? 4 : 2;
    board[row][col] = value;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "2048");

    srand(time(0));

    // Текстуры и спрайты для плиток
    sf::Texture tileTextures[11]; // Массив текстур для плиток
    sf::Sprite tileSprites[numRows][numCols]; // Массив спрайтов для плиток

    // Загрузка текстур плиток
    for (int i = 0; i <= 10; ++i) {
        tileTextures[i].loadFromFile("images/" + std::to_string(1 << i) + ".png");
    }

    // Загрузка текстуры пустой плитки
    sf::Texture emptyTileTexture;
    emptyTileTexture.loadFromFile("images/1.png");

    // Новая игра
    for (int i = 0; i < 2; ++i) {
        generateRandomTile(board);
    }

    // Вычисление размера плитки
    const int tileSize = windowSize / std::max(numRows, numCols);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Отрисовка плиток и пустых ячеек
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                int value = board[row][col];
                sf::Sprite tileSprite;

                if (value > 0) {
                    tileSprite.setTexture(tileTextures[value]);

                    // Установка размера плитки
                    sf::Vector2u tileTextureSize = tileTextures[value].getSize();
                    tileSprite.setScale(static_cast<float>(tileSize) / tileTextureSize.x, static_cast<float>(tileSize) / tileTextureSize.y);

                    // Вычисление позиции плитки
                    float x = col * tileSize;
                    float y = row * tileSize;

                    tileSprite.setPosition(x, y);
                }
                else {
                    // Если значение равно 0, отрисовать пустую плитку
                    tileSprite.setTexture(emptyTileTexture);
                    sf::Vector2u tileTextureSize = emptyTileTexture.getSize();
                    tileSprite.setScale(static_cast<float>(tileSize) / tileTextureSize.x, static_cast<float>(tileSize) / tileTextureSize.y);
                    float x = col * tileSize;
                    float y = row * tileSize;
                    tileSprite.setPosition(x, y);
                }

                window.draw(tileSprite);
            }
        }

        window.display();
    }

    return 0;
}
