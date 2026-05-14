#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Board.h"

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window);
    void update(float deltaTime);

    bool userColorsSelected[4] = { false, false, false, false };
    bool computerColorsSelected[4] = { false, false, false, false };

private:
    // SFML basics
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Texture LogoTexture;
    sf::Sprite background;
    sf::Sprite Logo;
    float backgroundOffset = 0.f;

    // Sound effects
    sf::SoundBuffer hoverBuffer, clickBuffer;
    sf::Sound hoverSound, clickSound;

    // UI Texts for menu title and buttons
    sf::Text title1, title2, title3, title4, title5, title6, title7, title8;
    sf::Text playButton;
    sf::Text exitButton;
    sf::Text select;

    bool playHovered = false;
    bool exitHovered = false;

    // Profile/Coins/Diamonds UI
    sf::RectangleShape profileBox, coinBox, diamondBox;
    sf::Texture profileTexture, coinTexture, diamondTexture, computer, friends;
    sf::Sprite profileIcon, coinIcon, diamondIcon, computerIcon, friendsIcon;
    sf::Text profileName, coinsText, diamondsText;

    // Color selection circles
    std::vector<sf::CircleShape> userColors;
    std::vector<sf::CircleShape> computerColors;
    std::vector<sf::Color> availableColors{ sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Red };

    float animationSpeed = 30.f;

    // Board display management
    bool showBoard = false;
    Board board; // Board instance

    // Private helper functions
    void initializeUIElements(float width, float height);
    void setupColorSelection();
    void setupTitleLetters(float width, float baseY);
};