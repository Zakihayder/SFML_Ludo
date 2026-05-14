// Board.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>

class Board {
public:
    Board(); // Constructor

    // Core game functions
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void handleInput(sf::RenderWindow& window);
    void changeTurn();

    // Game state management
    bool isPlayerTurn(int player) const { return currentPlayer == player; }
    int getCurrentPlayer() const { return currentPlayer; }
    int getCurrentDiceNumber() const { return currentDiceNumber; }
    bool hasRolledDice() const { return diceRolled; }
    bool canMovePawn(int player, int pawnIndex) const;

    // Player actions
    void rollDice();
    void movePawn(int player, int pawnIndex);
    void toggleVolume();
    void resetGame();
    bool isRestartClicked(const sf::Vector2f& mousePos) const;

    // UI elements for external access
    sf::Sprite volIcon;
    std::array<sf::Sprite, 4> diceSprites;

private:
    // Game state variables
    bool volumeOn;
    bool diceRolled;
    int currentDiceNumber;
    int currentPlayer; // 0-3 for 4 players
    int consecutiveSixes;
    bool gameOver;
    std::vector<int> playerRankings;

    // Player data
    struct Player {
        sf::Color color;
        std::array<sf::Vector2f, 4> homePositions;
        std::array<sf::Vector2f, 4> startPositions;
        std::array<int, 4> pawnPositions; // -1: home, 0-51: board, 52-57: final path
        std::array<bool, 4> pawnFinished;
        int startCell;
        int endCell;
    };
    std::array<Player, 4> players;

    // Textures and sprites
    sf::Texture boardTexture;
    sf::Sprite boardSprite;

    sf::Texture volOnTexture;
    sf::Texture volOffTexture;

    sf::Texture restartTexture;
    sf::Sprite restartIcon;

    sf::Texture Pawntexture, pawn1texture, pawn2texture, pawn3texture, pawn4texture, pawn5texture;
    std::array<sf::Sprite, 4> pawnSprites[4]; // 4 players, 4 pawns each

    std::vector<sf::Texture> diceFaceTextures;

    // Text elements
    sf::Font font;
    sf::Text turnText;
    sf::Text messageText;
    sf::Text P1, P2, P3, P4;

    //player Boxes
    sf::RectangleShape player1Box, player2Box, player3Box, player4Box;

    // Audio
    sf::SoundBuffer diceRollBuffer;
    sf::Sound diceRollSound;

    // Board positions
    std::vector<sf::Vector2f> boardPositions;
    std::vector<sf::Vector2f> finalPathPositions[4];
    std::vector<int> safeCells;

    // Helper functions
    void loadTextures();
    void setupUIElements();
    void initializeBoardPositions();
    void initializePlayers();
    void updatePawnPositions();
    bool isSafeCell(int position) const;
    bool isFinalPath(int position) const;
    bool isFinalCell(int player, int position) const;
    void checkWinCondition();
    void displayWinner();
    void computerPlay(float deltaTime);
    void highlightMovablePawns();
};