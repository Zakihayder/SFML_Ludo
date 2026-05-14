#include "Menu.h"
#include "Board.h"
#include <iostream>
#include <algorithm>

MainMenu::MainMenu(float width, float height) : showBoard(false), backgroundOffset(0) {
    // Load font
    if (!font.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\fonts\\YoungSerif-Regular.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Load background
    if (!backgroundTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\wallpapers.jpg")) {
        std::cerr << "Error loading background image\n";
    }
    if (!LogoTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Ludo_logo.jpg")) {
        std::cerr << "Error loading logo image\n";
    }
    background.setTexture(backgroundTexture);
    Logo.setTexture(LogoTexture);

    // Load sound effects
    if (!hoverBuffer.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\music\\audio.wav")) {
        std::cerr << "Error loading hover sound\n";
    }
    if (!clickBuffer.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\music\\click.wav")) {
        std::cerr << "Error loading click sound\n";
    }

    hoverSound.setBuffer(hoverBuffer);
    clickSound.setBuffer(clickBuffer);

    // Load icons
    if (!profileTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\profile.jpg"))
        std::cerr << "Error loading profile icon\n";
    if (!coinTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\coin.jpg"))
        std::cerr << "Error loading coin icon\n";
    if (!diamondTexture.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Diamond.jpg"))
        std::cerr << "Error loading diamond icon\n";
    if (!computer.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\friends.png"))
        std::cerr << "Error loading computer icon\n";
    if (!friends.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\Images\\Computer.png"))
        std::cerr << "Error loading friends icon\n";

    profileIcon.setTexture(profileTexture);
    coinIcon.setTexture(coinTexture);
    diamondIcon.setTexture(diamondTexture);
    computerIcon.setTexture(computer);
    friendsIcon.setTexture(friends);

    // Set scales
    background.setScale(1.70f, 1.50f);
    Logo.setScale(1.5f, 1.0f);
    profileIcon.setScale(0.03f, 0.03f);
    coinIcon.setScale(0.2f, 0.2f);
    diamondIcon.setScale(0.2f, 0.2f);
    computerIcon.setScale(1.0f, 1.0f);
    friendsIcon.setScale(1.0f, 1.0f);

    // Set positions
    Logo.setPosition(238.f, 70.f);
    computerIcon.setPosition(150.f, 345.f);
    friendsIcon.setPosition(150.f, 395.f);

    // Initialize UI elements
    initializeUIElements(width, height);
    setupColorSelection();
    setupTitleLetters(width, 220.f);
}

void MainMenu::initializeUIElements(float width, float height) {
    // Profile box
    profileBox.setSize(sf::Vector2f(200.f, 35.f));
    profileBox.setFillColor(sf::Color(240, 230, 210, 200));
    profileBox.setOutlineColor(sf::Color(139, 69, 19));
    profileBox.setOutlineThickness(3);
    profileBox.setPosition(22.f, 20.f);

    profileIcon.setPosition(20.f, 15.f);
    profileName.setFont(font);
    profileName.setString("   Zaki Haider");
    profileName.setCharacterSize(18);
    profileName.setFillColor(sf::Color::Black);
    profileName.setPosition(70.f, 25.f);

    // Coin box
    coinBox.setSize(sf::Vector2f(160.f, 35.f));
    coinBox.setFillColor(sf::Color(240, 230, 210, 200));
    coinBox.setOutlineColor(sf::Color(139, 69, 19));
    coinBox.setOutlineThickness(3);
    coinBox.setPosition(width / 2.f - 90.f, 20.f);

    coinIcon.setPosition(width / 2.f - 90.f, 15.f);
    coinsText.setFont(font);
    coinsText.setString("Coins: 100");
    coinsText.setCharacterSize(16);
    coinsText.setFillColor(sf::Color::Black);
    coinsText.setPosition(width / 2.f - 30.f, 25.f);

    // Diamond box
    diamondBox.setSize(sf::Vector2f(190.f, 35.f));
    diamondBox.setFillColor(sf::Color(240, 230, 210, 200));
    diamondBox.setOutlineColor(sf::Color(139, 69, 19));
    diamondBox.setOutlineThickness(3);
    diamondBox.setPosition(width - 200.f, 20.f);

    diamondIcon.setPosition(width - 200.f, 15.f);
    diamondsText.setFont(font);
    diamondsText.setString("Diamonds: 50");
    diamondsText.setCharacterSize(16);
    diamondsText.setFillColor(sf::Color::Black);
    diamondsText.setPosition(width - 140.f, 25.f);

    // Select text
    select.setFont(font);
    select.setString("SELECT COLORS");
    select.setCharacterSize(28);
    select.setFillColor(sf::Color::Transparent);
    select.setOutlineColor(sf::Color::Magenta);
    select.setOutlineThickness(0.5f);
    select.setPosition(280.f, 295.f);

    // Play button
    playButton.setFont(font);
    playButton.setString("PLAY");
    playButton.setCharacterSize(40);
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(width / 2.f - 60.f, 450.f);

    // Exit button
    exitButton.setFont(font);
    exitButton.setString("EXIT");
    exitButton.setCharacterSize(40);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(width / 2.f - 60.f, 520.f);
}

void MainMenu::setupColorSelection() {
    // Available colors
    std::vector<sf::Color> colors = {
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Blue,
        sf::Color::Red
    };

    // User color selection circles
    userColors.clear();
    for (int i = 0; i < 4; ++i) {
        sf::CircleShape circle(20.f);
        circle.setFillColor(colors[i]);
        circle.setPosition(295.f + i * 100.f, 340.f);
        userColors.push_back(circle);
        userColorsSelected[i] = false;
    }

    // Computer color selection circles
    computerColors.clear();
    for (int i = 0; i < 4; ++i) {
        sf::CircleShape circle(20.f);
        circle.setFillColor(colors[i]);
        circle.setPosition(295.f + i * 100.f, 390.f);
        computerColors.push_back(circle);
        computerColorsSelected[i] = false;
    }
}

void MainMenu::setupTitleLetters(float width, float baseY) {
    // L
    title1.setFont(font);
    title1.setString("L");
    title1.setCharacterSize(48);
    title1.setFillColor(sf::Color::Transparent);
    title1.setOutlineColor(sf::Color::Cyan);
    title1.setOutlineThickness(1);
    title1.setPosition(width / 3.1f - title1.getGlobalBounds().width / 2.f, baseY);

    // U
    title2.setFont(font);
    title2.setString("U");
    title2.setCharacterSize(48);
    title2.setFillColor(sf::Color::Transparent);
    title2.setOutlineColor(sf::Color::Green);
    title2.setOutlineThickness(1);
    title2.setPosition(width / 2.75f - title2.getGlobalBounds().width / 2.f, baseY);

    // D
    title3.setFont(font);
    title3.setString("D");
    title3.setCharacterSize(48);
    title3.setFillColor(sf::Color::Transparent);
    title3.setOutlineColor(sf::Color::Yellow);
    title3.setOutlineThickness(1);
    title3.setPosition(width / 2.40f - title3.getGlobalBounds().width / 2.f, baseY);

    // O
    title4.setFont(font);
    title4.setString("O");
    title4.setCharacterSize(48);
    title4.setFillColor(sf::Color::Transparent);
    title4.setOutlineColor(sf::Color::Red);
    title4.setOutlineThickness(1);
    title4.setPosition(width / 2.15f - title4.getGlobalBounds().width / 2.f, baseY);

    // G
    title5.setFont(font);
    title5.setString("G");
    title5.setCharacterSize(48);
    title5.setFillColor(sf::Color::Transparent);
    title5.setOutlineColor(sf::Color::Cyan);
    title5.setOutlineThickness(1);
    title5.setPosition(width / 1.85f - title5.getGlobalBounds().width / 2.f, baseY);

    // A
    title6.setFont(font);
    title6.setString("A");
    title6.setCharacterSize(48);
    title6.setFillColor(sf::Color::Transparent);
    title6.setOutlineColor(sf::Color::Green);
    title6.setOutlineThickness(1);
    title6.setPosition(width / 1.71f - title6.getGlobalBounds().width / 2.f, baseY);

    // M
    title7.setFont(font);
    title7.setString("M");
    title7.setCharacterSize(48);
    title7.setFillColor(sf::Color::Transparent);
    title7.setOutlineColor(sf::Color::Yellow);
    title7.setOutlineThickness(1);
    title7.setPosition(width / 1.57f - title7.getGlobalBounds().width / 2.f, baseY);

    // E
    title8.setFont(font);
    title8.setString("E");
    title8.setCharacterSize(48);
    title8.setFillColor(sf::Color::Transparent);
    title8.setOutlineColor(sf::Color::Red);
    title8.setOutlineThickness(1);
    title8.setPosition(width / 1.43f - title8.getGlobalBounds().width / 2.f, baseY);
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();

    if (showBoard) {
        board.draw(window);
    }
    else {
        // Draw background
        window.draw(background);
        window.draw(Logo);

        // Draw HUD elements
        window.draw(profileBox);
        window.draw(profileIcon);
        window.draw(profileName);
        window.draw(coinBox);
        window.draw(coinIcon);
        window.draw(coinsText);
        window.draw(diamondBox);
        window.draw(diamondIcon);
        window.draw(diamondsText);

        // Draw mode selection icons
        window.draw(computerIcon);
        window.draw(friendsIcon);
        window.draw(select);

        // Draw title letters
        window.draw(title1);
        window.draw(title2);
        window.draw(title3);
        window.draw(title4);
        window.draw(title5);
        window.draw(title6);
        window.draw(title7);
        window.draw(title8);

        // Draw color selection circles
        for (auto& circle : userColors) window.draw(circle);
        for (auto& circle : computerColors) window.draw(circle);

        // Draw buttons
        window.draw(playButton);
        window.draw(exitButton);

        // Draw decorative bars
        sf::RectangleShape bar(sf::Vector2f(800.f, 5.f));
        bar.setFillColor(sf::Color(0, 255, 255, 150));
        bar.setPosition(0.f, 590.f);
        window.draw(bar);

        sf::RectangleShape bar1(sf::Vector2f(5.f, 800.f));
        bar1.setFillColor(sf::Color(0, 255, 255, 150));
        bar1.setPosition(5.f, fmod(backgroundOffset, 600.f));
        window.draw(bar1);

        sf::RectangleShape bar2(sf::Vector2f(5.f, 800.f));
        bar2.setFillColor(sf::Color(0, 255, 255, 150));
        bar2.setPosition(790.f, fmod(backgroundOffset, 600.f));
        window.draw(bar2);
    }

    window.display();
}

void MainMenu::handleInput(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (showBoard) {
        // Board interaction mode
        if (board.volIcon.getGlobalBounds().contains(mousePosF)) {
            static bool volClickedLastFrame = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!volClickedLastFrame) {
                    board.toggleVolume();
                    volClickedLastFrame = true;
                }
            }
            else {
                volClickedLastFrame = false;
            }
        }

        // Check if it's the player's turn to roll dice
        if (board.getCurrentPlayer() == 0 && board.diceSprites[0].getGlobalBounds().contains(mousePosF)) {
            static bool diceClickedLastFrame = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!diceClickedLastFrame) {
                    board.rollDice();
                    diceClickedLastFrame = true;

                    // If player rolled a 6, they get another turn
                    if (board.getCurrentDiceNumber() == 6) {
                        board.changeTurn();
                    }
                }
            }
            else {
                diceClickedLastFrame = false;
            }
        }

        // Check if restart button was clicked
        if (board.isRestartClicked(mousePosF)) {
            static bool restartClickedLastFrame = false;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (!restartClickedLastFrame) {
                    board.resetGame();
                    restartClickedLastFrame = true;
                }
            }
            else {
                restartClickedLastFrame = false;
            }
        }
    }
    else {
        // Menu interaction mode
        bool canPlay = std::count(std::begin(userColorsSelected), std::end(userColorsSelected), true) >= 1 &&
            std::count(std::begin(computerColorsSelected), std::end(computerColorsSelected), true) >= 1;

        // Play button interaction
        if (playButton.getGlobalBounds().contains(mousePosF)) {
            if (!playHovered) {
                hoverSound.play();
                playHovered = true;
            }
            playButton.setFillColor(sf::Color::Green);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canPlay) {
                clickSound.play();
                showBoard = true;
                board.resetGame();
            }
        }
        else {
            playButton.setFillColor(sf::Color::White);
            playHovered = false;
        }

        // Exit button interaction
        if (exitButton.getGlobalBounds().contains(mousePosF)) {
            if (!exitHovered) {
                hoverSound.play();
                exitHovered = true;
            }
            exitButton.setFillColor(sf::Color::Red);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                clickSound.play();
                window.close();
            }
        }
        else {
            exitButton.setFillColor(sf::Color::White);
            exitHovered = false;
        }

        // Color selection tracking
        for (int i = 0; i < 4; ++i) {
            if (userColors[i].getGlobalBounds().contains(mousePosF)) {
                static std::vector<bool> userClickLastFrame(4, false);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !computerColorsSelected[i]) {
                    if (!userClickLastFrame[i]) {
                        userColorsSelected[i] = !userColorsSelected[i];
                        userColors[i].setOutlineColor(userColorsSelected[i] ? sf::Color::White : sf::Color::Transparent);
                        userColors[i].setOutlineThickness(userColorsSelected[i] ? 3.f : 0.f);
                        userClickLastFrame[i] = true;
                    }
                }
                else {
                    userClickLastFrame[i] = false;
                }
            }
            if (computerColors[i].getGlobalBounds().contains(mousePosF)) {
                static std::vector<bool> compClickLastFrame(4, false);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !userColorsSelected[i]) {
                    if (!compClickLastFrame[i]) {
                        computerColorsSelected[i] = !computerColorsSelected[i];
                        computerColors[i].setOutlineColor(computerColorsSelected[i] ? sf::Color::White : sf::Color::Transparent);
                        computerColors[i].setOutlineThickness(computerColorsSelected[i] ? 3.f : 0.f);
                        compClickLastFrame[i] = true;
                    }
                }
                else {
                    compClickLastFrame[i] = false;
                }
            }
        }
    }
}

void MainMenu::update(float deltaTime) {
    backgroundOffset += deltaTime * animationSpeed;
    if (backgroundOffset > backgroundTexture.getSize().x)
        backgroundOffset = 0;

    background.setTextureRect(sf::IntRect(static_cast<int>(backgroundOffset), 0, 800, 600));

    // If it's the computer's turn, automatically roll the dice after a delay
    if (showBoard && board.getCurrentPlayer() > 0) {
        static float computerTurnTimer = 0.0f;
        computerTurnTimer += deltaTime;

        if (computerTurnTimer >= 1.5f) { // Wait 1.5 seconds before rolling
            board.rollDice();
            computerTurnTimer = 0.0f;

            // If computer rolled a 6, they get another turn
            if (board.getCurrentDiceNumber() == 6) {
                board.changeTurn();
            }
        }
    }
}