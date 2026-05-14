#include "Board.h"
#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Board::Board() : volumeOn(true), currentDiceNumber(1), currentPlayer(0),
diceRolled(false), consecutiveSixes(0), gameOver(false) {
    // Seed for random number generation for dice rolls
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Load board image
    if (!boardTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Board.jpg")) {
        std::cerr << "Error loading board image\n";
    }
    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(1.5, 1.5);
    boardSprite.setPosition(100, 0);

    // Load restart icon
    if (!restartTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\rematch.png")) {
        std::cerr << "Error loading restart icon\n";
    }
    restartIcon.setTexture(restartTexture);
    restartIcon.setPosition(730, 280);
    restartIcon.setScale(1, 1);

    // Load volume icons
    if (!volOnTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\sound.png") ||
        !volOffTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\soundOff.png")) {
        std::cerr << "Error loading volume icons\n";
    }
    volIcon.setTexture(volOnTexture);
    volIcon.setPosition(30, 280);
    volIcon.setScale(1, 1);

    // Load pawn textures
    if (!Pawntexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Green_Pawn.png")) {
        std::cerr << "Error loading green pawn texture\n";
    }
    if (!pawn1texture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Yellow_Pawn.png")) {
        std::cerr << "Error loading yellow pawn texture\n";
    }
    if (!pawn2texture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Blue_Pawn.png")) {
        std::cerr << "Error loading blue pawn texture\n";
    }
    if (!pawn3texture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Red_Pawn.png")) {
        std::cerr << "Error loading red pawn texture\n";
    }
    if (!pawn4texture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Red_Pawn_rev.png")) {
        std::cerr << "Error loading reversed red pawn texture\n";
    }
    if (!pawn5texture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Blue_Pawn_rev.png")) {
        std::cerr << "Error loading reversed blue pawn texture\n";
    }

    // Initialize pawn sprites for all players
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pawnSprites[i][j].setScale(0.8, 0.8);
        }
    }

    // Player 1 (Green) pawns
    for (int i = 0; i < 4; i++) {
        pawnSprites[0][i].setTexture(Pawntexture);
    }
    pawnSprites[0][0].setPosition(160, 115);
    pawnSprites[0][1].setPosition(237, 115);
    pawnSprites[0][2].setPosition(160, 37);
    pawnSprites[0][3].setPosition(237, 37);

    // Player 2 (Yellow) pawns
    for (int i = 0; i < 4; i++) {
        pawnSprites[1][i].setTexture(pawn1texture);
    }
    pawnSprites[1][0].setPosition(517, 115);
    pawnSprites[1][1].setPosition(595, 115);
    pawnSprites[1][2].setPosition(517, 37);
    pawnSprites[1][3].setPosition(595, 37);

    // Player 3 (Blue) pawns
    for (int i = 0; i < 4; i++) {
        pawnSprites[2][i].setTexture(pawn2texture);
    }
    pawnSprites[2][0].setPosition(517, 393);
    pawnSprites[2][1].setPosition(595, 393);
    pawnSprites[2][2].setPosition(517, 470);
    pawnSprites[2][3].setPosition(595, 470);

    // Player 4 (Red) pawns
    for (int i = 0; i < 4; i++) {
        pawnSprites[3][i].setTexture(pawn3texture);
    }
    pawnSprites[3][0].setPosition(155, 393);
    pawnSprites[3][1].setPosition(232, 393);
    pawnSprites[3][2].setPosition(155, 470);
    pawnSprites[3][3].setPosition(232, 470);

    // Load dice face textures for 1 to 6
    diceFaceTextures.resize(6);
    for (int i = 0; i < 6; ++i) {
        std::string path = "C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\" + std::to_string(i + 1) + "dice.png";
        if (!diceFaceTextures[i].loadFromFile(path)) {
            std::cerr << "Error loading dice face image: " << path << '\n';
        }
    }

    // Set initial dice face textures
    for (int i = 0; i < 4; ++i) {
        diceSprites[i].setTexture(diceFaceTextures[0]);
        diceSprites[i].setPosition(25 + (i % 2) * 700, 150 + (i / 2) * 250);
        diceSprites[i].setScale(1.2, 1.2);
    }

    // Load font for text
    if (!font.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\fonts\\YoungSerif-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Setup turn indicator text
    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::Green);
    turnText.setPosition(700, 50);
    turnText.setString("Player 1's turn");

    // Setup message text
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(300, 550);
    messageText.setString("");

    // Load dice roll sound buffer
    if (!diceRollBuffer.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\music\\Dice_Roll.mp3")) {
        std::cerr << "Error loading dice roll sound\n";
    }
    diceRollSound.setBuffer(diceRollBuffer);

    // Initialize player boxes
    player1Box.setSize(sf::Vector2f(65, 65));
    player1Box.setFillColor(sf::Color(240, 230, 210, 200));
    player1Box.setOutlineColor(sf::Color(255, 255, 100));
    player1Box.setOutlineThickness(4);
    player1Box.setPosition(17, 143);

    player2Box.setSize(sf::Vector2f(65, 65));
    player2Box.setFillColor(sf::Color(240, 230, 210, 200));
    player2Box.setOutlineColor(sf::Color(255, 255, 100));
    player2Box.setOutlineThickness(4);
    player2Box.setPosition(717, 143);

    player3Box.setSize(sf::Vector2f(65, 65));
    player3Box.setFillColor(sf::Color(240, 230, 210, 200));
    player3Box.setOutlineColor(sf::Color(255, 255, 100));
    player3Box.setOutlineThickness(4);
    player3Box.setPosition(17, 393);

    player4Box.setSize(sf::Vector2f(65, 65));
    player4Box.setFillColor(sf::Color(240, 230, 210, 200));
    player4Box.setOutlineColor(sf::Color(255, 255, 100));
    player4Box.setOutlineThickness(4);
    player4Box.setPosition(717, 393);

    // Player labels
    P1.setFont(font);
    P1.setString("Player 1");
    P1.setCharacterSize(48);
    P1.setFillColor(sf::Color::Green);
    P1.setOutlineColor(sf::Color::Black);
    P1.setScale(0.7, 0.7);
    P1.setOutlineThickness(2);
    P1.setPosition(153, -2);

    P2.setFont(font);
    P2.setString("Player 2");
    P2.setCharacterSize(48);
    P2.setFillColor(sf::Color::Yellow);
    P2.setOutlineColor(sf::Color::Black);
    P2.setScale(0.7, 0.7);
    P2.setOutlineThickness(2);
    P2.setPosition(511, -2);

    P3.setFont(font);
    P3.setString("Player 3");
    P3.setCharacterSize(48);
    P3.setFillColor(sf::Color::Blue);
    P3.setOutlineColor(sf::Color::Black);
    P3.setScale(0.7, 0.7);
    P3.setOutlineThickness(2);
    P3.setPosition(511, 560);

    P4.setFont(font);
    P4.setString("Player 4");
    P4.setCharacterSize(48);
    P4.setFillColor(sf::Color::Red);
    P4.setOutlineColor(sf::Color::Black);
    P4.setScale(0.7, 0.7);
    P4.setOutlineThickness(2);
    P4.setPosition(153, 560);

    // Initialize board positions and players
    initializeBoardPositions();
    initializePlayers();
    resetGame();
}

void Board::initializeBoardPositions() {
    // Initialize all 52 board positions (simplified for example)
    boardPositions.resize(52);

    // These are approximate positions - you'll need to adjust them to match your board image
    // Starting from Player 1's start position (top-left) and moving clockwise

    // Top row (left to right)
    for (int i = 0; i < 6; i++) {
        boardPositions[i] = sf::Vector2f(200 + i * 60, 100);
    }

    // Right side (top to bottom)
    for (int i = 0; i < 6; i++) {
        boardPositions[6 + i] = sf::Vector2f(560, 100 + i * 60);
    }

    // Bottom row (right to left)
    for (int i = 0; i < 6; i++) {
        boardPositions[12 + i] = sf::Vector2f(560 - i * 60, 460);
    }

    // Left side (bottom to top)
    for (int i = 0; i < 6; i++) {
        boardPositions[18 + i] = sf::Vector2f(200, 460 - i * 60);
    }

    // Continue this pattern for all 52 cells...
    // (You'll need to complete this with accurate positions for your board)

    // Initialize final path positions for each player
    for (int p = 0; p < 4; ++p) {
        finalPathPositions[p].resize(6);
        for (int i = 0; i < 6; ++i) {
            // These positions should lead to each player's home
            if (p == 0) { // Green (top-left)
                finalPathPositions[p][i] = sf::Vector2f(200 + i * 30, 150 + i * 30);
            }
            else if (p == 1) { // Yellow (top-right)
                finalPathPositions[p][i] = sf::Vector2f(560 - i * 30, 150 + i * 30);
            }
            else if (p == 2) { // Blue (bottom-right)
                finalPathPositions[p][i] = sf::Vector2f(560 - i * 30, 460 - i * 30);
            }
            else { // Red (bottom-left)
                finalPathPositions[p][i] = sf::Vector2f(200 + i * 30, 460 - i * 30);
            }
        }
    }

    // Define safe cells (star positions)
    safeCells = { 0, 8, 13, 21, 26, 34, 39, 47 };
}

void Board::initializePlayers() {
    // Player 1 (Green)
    players[0].color = sf::Color::Green;
    players[0].startCell = 0;
    players[0].endCell = 50;
    players[0].homePositions[0] = sf::Vector2f(160, 115);
    players[0].homePositions[1] = sf::Vector2f(237, 115);
    players[0].homePositions[2] = sf::Vector2f(160, 37);
    players[0].homePositions[3] = sf::Vector2f(237, 37);
    players[0].startPositions[0] = boardPositions[0];
    players[0].startPositions[1] = boardPositions[0];
    players[0].startPositions[2] = boardPositions[0];
    players[0].startPositions[3] = boardPositions[0];

    // Player 2 (Yellow)
    players[1].color = sf::Color::Yellow;
    players[1].startCell = 13;
    players[1].endCell = 11;
    players[1].homePositions[0] = sf::Vector2f(517, 115);
    players[1].homePositions[1] = sf::Vector2f(595, 115);
    players[1].homePositions[2] = sf::Vector2f(517, 37);
    players[1].homePositions[3] = sf::Vector2f(595, 37);
    players[1].startPositions[0] = boardPositions[13];
    players[1].startPositions[1] = boardPositions[13];
    players[1].startPositions[2] = boardPositions[13];
    players[1].startPositions[3] = boardPositions[13];

    // Player 3 (Blue)
    players[2].color = sf::Color::Blue;
    players[2].startCell = 26;
    players[2].endCell = 24;
    players[2].homePositions[0] = sf::Vector2f(517, 393);
    players[2].homePositions[1] = sf::Vector2f(595, 393);
    players[2].homePositions[2] = sf::Vector2f(517, 470);
    players[2].homePositions[3] = sf::Vector2f(595, 470);
    players[2].startPositions[0] = boardPositions[26];
    players[2].startPositions[1] = boardPositions[26];
    players[2].startPositions[2] = boardPositions[26];
    players[2].startPositions[3] = boardPositions[26];

    // Player 4 (Red)
    players[3].color = sf::Color::Red;
    players[3].startCell = 39;
    players[3].endCell = 37;
    players[3].homePositions[0] = sf::Vector2f(155, 393);
    players[3].homePositions[1] = sf::Vector2f(232, 393);
    players[3].homePositions[2] = sf::Vector2f(155, 470);
    players[3].homePositions[3] = sf::Vector2f(232, 470);
    players[3].startPositions[0] = boardPositions[39];
    players[3].startPositions[1] = boardPositions[39];
    players[3].startPositions[2] = boardPositions[39];
    players[3].startPositions[3] = boardPositions[39];
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(boardSprite);

    // Draw decorative bars (from your original code)
    sf::RectangleShape bar(sf::Vector2f(3, 700));
    bar.setFillColor(sf::Color(0, 255, 255, 150));
    bar.setPosition(-1.5, 0);
    window.draw(bar);

    sf::RectangleShape bar1(sf::Vector2f(3, 700));
    bar1.setFillColor(sf::Color(0, 255, 255, 150));
    bar1.setPosition(797, 0);
    window.draw(bar1);

    sf::RectangleShape bar2(sf::Vector2f(3, 700));
    bar2.setFillColor(sf::Color(0, 255, 255, 150));
    bar2.setPosition(100, 0);
    window.draw(bar2);

    sf::RectangleShape bar3(sf::Vector2f(3, 700));
    bar3.setFillColor(sf::Color(0, 255, 255, 150));
    bar3.setPosition(697, 0);
    window.draw(bar3);

    sf::RectangleShape bar4(sf::Vector2f(100, 3));
    bar4.setFillColor(sf::Color(0, 255, 0, 190));
    bar4.setPosition(0, 236);
    window.draw(bar4);

    sf::RectangleShape bar5(sf::Vector2f(100, 3));
    bar5.setFillColor(sf::Color(255, 255, 100));
    bar5.setPosition(700, 236);
    window.draw(bar5);

    sf::RectangleShape bar6(sf::Vector2f(100, 3));
    bar6.setFillColor(sf::Color(255, 0, 0, 150));
    bar6.setPosition(0, 360);
    window.draw(bar6);

    sf::RectangleShape bar7(sf::Vector2f(100, 3));
    bar7.setFillColor(sf::Color(0, 0, 255, 255));
    bar7.setPosition(700, 360);
    window.draw(bar7);

    // Draw all UI elements
    window.draw(turnText);
    window.draw(messageText);
    window.draw(volIcon);
    window.draw(restartIcon);

    // Draw player boxes with highlight for current player
    window.draw(player1Box);
    window.draw(player2Box);
    window.draw(player3Box);
    window.draw(player4Box);

    // Draw player labels
    window.draw(P1);
    window.draw(P2);
    window.draw(P3);
    window.draw(P4);

    // Draw dice
    for (const auto& diceSprite : diceSprites) {
        window.draw(diceSprite);
    }

    // Draw pawns
    for (int p = 0; p < 4; ++p) {
        for (int i = 0; i < 4; ++i) {
            if (!players[p].pawnFinished[i]) {
                window.draw(pawnSprites[p][i]);
            }
        }
    }

    // Highlight movable pawns if dice has been rolled
    if (diceRolled && !gameOver) {
        highlightMovablePawns();
    }
}

void Board::update(float deltaTime) {
    if (gameOver) return;

    // Update message text timeout
    static float messageTime = 0.0f;
    if (messageTime > 0.0f) {
        messageTime -= deltaTime;
        if (messageTime <= 0.0f) {
            messageText.setString("");
        }
    }

    // Computer player logic
    if (currentPlayer > 0 && diceRolled) {
        computerPlay(deltaTime);
    }
}

void Board::handleInput(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Volume toggle
    if (volIcon.getGlobalBounds().contains(mousePosF)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            toggleVolume();
        }
    }

    // Restart game
    if (isRestartClicked(mousePosF) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        resetGame();
    }

    // Dice roll for human player
    if (currentPlayer == 0 && !diceRolled && diceSprites[0].getGlobalBounds().contains(mousePosF)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            rollDice();
        }
    }

    // Pawn selection and movement
    if (diceRolled && currentPlayer == 0) {
        for (int i = 0; i < 4; ++i) {
            if (pawnSprites[currentPlayer][i].getGlobalBounds().contains(mousePosF) &&
                canMovePawn(currentPlayer, i)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    movePawn(currentPlayer, i);
                }
            }
        }
    }
}

void Board::rollDice() {
    if (diceRolled || gameOver) return;

    int roll = (std::rand() % 6) + 1;
    currentDiceNumber = roll;
    diceRolled = true;

    // Update dice sprite
    diceSprites[currentPlayer].setTexture(diceFaceTextures[roll - 1]);

    // Play sound
    if (volumeOn) {
        diceRollSound.play();
    }

    // Check if player has any valid moves
    bool canMove = false;
    for (int i = 0; i < 4; ++i) {
        if (canMovePawn(currentPlayer, i)) {
            canMove = true;
            break;
        }
    }

    if (!canMove) {
        messageText.setString("No valid moves! Passing turn.");
        messageText.setPosition(300, 550);
        changeTurn();
    }
}

void Board::movePawn(int player, int pawnIndex) {
    if (!diceRolled || !canMovePawn(player, pawnIndex)) return;

    Player& p = players[player];
    int& pos = p.pawnPositions[pawnIndex];

    // Moving from home
    if (pos == -1) {
        if (currentDiceNumber == 6) {
            pos = p.startCell;
            messageText.setString("Player " + std::to_string(player + 1) + " moved a pawn out!");
            messageText.setPosition(300, 550);
        }
    }
    // Moving on board
    else if (pos < 52) {
        int newPos = (pos + currentDiceNumber) % 52;

        // Check if pawn can enter final path
        if (newPos == p.startCell && pos + currentDiceNumber >= 52) {
            pos = 52; // Enter final path
        }
        else {
            pos = newPos;
        }

        // Check for kills
        for (int otherPlayer = 0; otherPlayer < 4; ++otherPlayer) {
            if (otherPlayer == player) continue;

            for (int otherPawn = 0; otherPawn < 4; otherPawn++) {
                if (players[otherPlayer].pawnPositions[otherPawn] == pos &&
                    !isSafeCell(pos) &&
                    !players[otherPlayer].pawnFinished[otherPawn]) {
                    // Kill opponent's pawn
                    players[otherPlayer].pawnPositions[otherPawn] = -1;
                    messageText.setString("Player " + std::to_string(player + 1) +
                        " killed Player " + std::to_string(otherPlayer + 1) + "'s pawn!");
                    messageText.setPosition(250, 550);
                    break;
                }
            }
        }
    }
    // Moving on final path
    else {
        pos += currentDiceNumber;
        if (pos >= 58) {
            pos = 57; // Can't overshoot final cell
        }

        if (pos == 57) {
            p.pawnFinished[pawnIndex] = true;
            messageText.setString("Player " + std::to_string(player + 1) + " pawn reached home!");
            messageText.setPosition(300, 550);
            checkWinCondition();
        }
    }

    updatePawnPositions();

    // Check for another turn (rolled a 6)
    if (currentDiceNumber == 6 && !gameOver) {
        consecutiveSixes++;
        if (consecutiveSixes < 3) {
            diceRolled = false;
            return;
        }
    }

    consecutiveSixes = 0;
    changeTurn();
}

bool Board::canMovePawn(int player, int pawnIndex) const {
    const Player& p = players[player];
    int pos = p.pawnPositions[pawnIndex];

    // Can't move finished pawns
    if (p.pawnFinished[pawnIndex]) return false;

    // Moving from home
    if (pos == -1) {
        return currentDiceNumber == 6;
    }

    // Moving on board
    if (pos < 52) {
        int newPos = (pos + currentDiceNumber) % 52;

        // Check if pawn can enter final path
        if (newPos == p.startCell && pos + currentDiceNumber >= 52) {
            return true;
        }

        // Check if new position is blocked by own pawns
        for (int i = 0; i < 4; ++i) {
            if (i != pawnIndex && p.pawnPositions[i] == newPos && !p.pawnFinished[i]) {
                return false;
            }
        }

        return true;
    }

    // Moving on final path
    if (pos >= 52) {
        int newPos = pos + currentDiceNumber;
        if (newPos > 57) return false;

        // Check if new position is blocked by own pawns
        for (int i = 0; i < 4; ++i) {
            if (i != pawnIndex && p.pawnPositions[i] == newPos && !p.pawnFinished[i]) {
                return false;
            }
        }

        return true;
    }

    return false;
}

void Board::updatePawnPositions() {
    for (int p = 0; p < 4; ++p) {
        for (int i = 0; i < 4; ++i) {
            int pos = players[p].pawnPositions[i];
            if (pos == -1) {
                pawnSprites[p][i].setPosition(players[p].homePositions[i]);
            }
            else if (pos < 52) {
                pawnSprites[p][i].setPosition(boardPositions[pos]);
            }
            else {
                int pathPos = pos - 52;
                pawnSprites[p][i].setPosition(finalPathPositions[p][pathPos]);
            }
        }
    }
}

void Board::changeTurn() {
    if (gameOver) return;

    diceRolled = false;
    currentPlayer = (currentPlayer + 1) % 4;

    // Skip players who have already won
    while (std::find(playerRankings.begin(), playerRankings.end(), currentPlayer) != playerRankings.end()) {
        currentPlayer = (currentPlayer + 1) % 4;
    }

    // Update turn text
    turnText.setString("Player " + std::to_string(currentPlayer + 1) + "'s turn");
    turnText.setFillColor(players[currentPlayer].color);
}

void Board::checkWinCondition() {
    for (int p = 0; p < 4; ++p) {
        bool allFinished = true;
        for (int i = 0; i < 4; ++i) {
            if (!players[p].pawnFinished[i]) {
                allFinished = false;
                break;
            }
        }

        if (allFinished && std::find(playerRankings.begin(), playerRankings.end(), p) == playerRankings.end()) {
            playerRankings.push_back(p);
        }
    }

    if (playerRankings.size() >= 3) { // Game over when 3 players have finished
        gameOver = true;
        displayWinner();
    }
}

void Board::displayWinner() {
    std::string winnerText = "Game Over!\n";
    for (size_t i = 0; i < playerRankings.size(); ++i) {
        winnerText += std::to_string(i + 1) + "st: Player " + std::to_string(playerRankings[i] + 1) + "\n";
    }

    messageText.setString(winnerText);
    messageText.setPosition(300, 250);
    messageText.setCharacterSize(36);
}

void Board::resetGame() {
    currentPlayer = 0;
    currentDiceNumber = 1;
    diceRolled = false;
    consecutiveSixes = 0;
    gameOver = false;
    playerRankings.clear();

    for (auto& player : players) {
        for (int i = 0; i < 4; ++i) {
            player.pawnPositions[i] = -1;
            player.pawnFinished[i] = false;
        }
    }

    turnText.setString("Player 1's turn");
    turnText.setFillColor(players[0].color);
    messageText.setString("");
    messageText.setCharacterSize(24);

    updatePawnPositions();
}

void Board::highlightMovablePawns() {
    for (int i = 0; i < 4; ++i) {
        if (canMovePawn(currentPlayer, i)) {
            pawnSprites[currentPlayer][i].setColor(sf::Color(255, 255, 255, 200));
        }
        else {
            pawnSprites[currentPlayer][i].setColor(sf::Color(255, 255, 255, 100));
        }
    }
}

void Board::computerPlay(float deltaTime) {
    static float delay = 0.0f;
    delay += deltaTime;

    if (delay < 1.0f) return; // Wait 1 second before moving

    delay = 0.0f;

    // Find all movable pawns
    std::vector<int> movablePawns;
    for (int i = 0; i < 4; ++i) {
        if (canMovePawn(currentPlayer, i)) {
            movablePawns.push_back(i);
        }
    }

    if (!movablePawns.empty()) {
        // Simple AI: pick first movable pawn
        int pawnToMove = movablePawns[0];

        // Slightly smarter: prefer to kill opponents or enter final path
        for (int i : movablePawns) {
            int newPos = players[currentPlayer].pawnPositions[i] + currentDiceNumber;

            // Check if this move would kill an opponent
            for (int p = 0; p < 4; ++p) {
                if (p == currentPlayer) continue;

                for (int j = 0; j < 4; ++j) {
                    if (players[p].pawnPositions[j] == newPos % 52 &&
                        !isSafeCell(newPos % 52) &&
                        !players[p].pawnFinished[j]) {
                        pawnToMove = i;
                        break;
                    }
                }
            }

            // Check if this move enters final path
            if (players[currentPlayer].pawnPositions[i] < 52 &&
                newPos >= 52 &&
                newPos % 52 == players[currentPlayer].startCell) {
                pawnToMove = i;
                break;
            }
        }

        movePawn(currentPlayer, pawnToMove);
    }
    else {
        changeTurn();
    }
}

void Board::toggleVolume() {
    volumeOn = !volumeOn;
    volIcon.setTexture(volumeOn ? volOnTexture : volOffTexture);
}

bool Board::isRestartClicked(const sf::Vector2f& mousePos) const {
    return restartIcon.getGlobalBounds().contains(mousePos);
}

bool Board::isSafeCell(int position) const {
    return std::find(safeCells.begin(), safeCells.end(), position) != safeCells.end();
}