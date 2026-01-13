#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Piece
{
    None,
    PawnWhite, RookWhite, KnightWhite, BishopWhite, QueenWhite, KingWhite,
    PawnBlack, RookBlack, KnightBlack, BishopBlack, QueenBlack, KingBlack
};

class Grid
{
public:
    static constexpr int SIZE = 8;
    static constexpr int TILE_SIZE = 80;

    Grid()
    {
        reset();
        if (!texture.loadFromFile("pieces.png"))
        {
            std::cout << "error to load tilesheet" << std::endl;
            exit(1);
        }
        texture.setSmooth(true);
        sprite.setTexture(&texture);
        sprite.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    }

    void reset();
    Piece get(int x, int y) const;
    void set(int x, int y, Piece piece);

    void draw(sf::RenderWindow& window)
    {
        drawBoard(window);
        drawPieces(window);
    }

    // Gestion du clic souris
    void handleClick(const sf::Vector2i& mousePos);

private:
    std::array<Piece, SIZE* SIZE> board;
    sf::Texture texture;
    sf::RectangleShape sprite;

    int selectedX = -1;
    int selectedY = -1;

    void drawBoard(sf::RenderWindow& window)
    {
        sf::RectangleShape tile({ TILE_SIZE, TILE_SIZE });

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
            {
                bool white = (x + y) % 2 == 0;
                tile.setFillColor(white ? sf::Color(240, 217, 181)
                    : sf::Color(181, 136, 99));
                tile.setPosition({ static_cast<float>(x * TILE_SIZE),
                    static_cast<float>((7 - y) * TILE_SIZE) });
                window.draw(tile);
            }
        }

        // surbrillance de la pièce sélectionnée
        if (selectedX != -1)
        {
            sf::RectangleShape highlight({ TILE_SIZE, TILE_SIZE });
            highlight.setFillColor(sf::Color(0, 255, 0, 100));
            highlight.setPosition({ static_cast<float>(selectedX * TILE_SIZE),
                static_cast<float>((7 - selectedY) * TILE_SIZE) });
            window.draw(highlight);
        }
    }

    void drawPieces(sf::RenderWindow& window)
    {
        const int piecesPerRow = 6;
        const int rows = 2;
        int pieceWidth = texture.getSize().x / piecesPerRow;
        int pieceHeight = texture.getSize().y / rows;

        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
            {
                Piece p = get(x, y);
                if (p == Piece::None) continue;

                int index = static_cast<int>(p) - 1;
                int px = (index % piecesPerRow) * pieceWidth;
                int py = (index / piecesPerRow) * pieceHeight;

                sprite.setTextureRect(sf::IntRect({ px, py }, { pieceWidth, pieceHeight }));
                sprite.setPosition({ static_cast<float>(x * TILE_SIZE),
                    static_cast<float>((7 - y) * TILE_SIZE) });
                window.draw(sprite);
            }
        }
    }

    sf::Vector2i mouseToCell(const sf::Vector2i& mousePos) const
    {
        int x = mousePos.x / TILE_SIZE;
        int y = 7 - (mousePos.y / TILE_SIZE);
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
            return { -1, -1 };
        return { x, y };
    }
};
