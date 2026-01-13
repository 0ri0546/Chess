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
        }
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

private:
    std::array<Piece, SIZE* SIZE> board;
    sf::Texture texture;
    sf::RectangleShape sprite;

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
                tile.setPosition({ static_cast<float>(x * TILE_SIZE), static_cast<float>(7.0f - y) * static_cast<float>(TILE_SIZE) });
                window.draw(tile);
            }
        }
    }

public:
    void drawPieces(sf::RenderWindow& window)
    {
        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
            {
                Piece p = get(x, y);
                if (p == Piece::None) continue;

                int index = static_cast<int>(p) - 1;
                int px = (index % 6) * 64;
                int py = (index / 6) * 64;

                sprite.setTextureRect(sf::IntRect({ px, py }, { 64, 64 }));

                sprite.setPosition({
                    static_cast<float>(x * TILE_SIZE),
                    static_cast<float>((7 - y) * TILE_SIZE)
                });

                window.draw(sprite);
            }
        }
    }
};
