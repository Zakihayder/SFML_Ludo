
#include <SFML/Graphics.hpp>
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ludo Main Menu");
    window.setFramerateLimit(60);

    MainMenu menu(800, 600);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        menu.handleInput(window);
        menu.update(deltaTime);
        menu.draw(window);
    }

    return 0;
}
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <random>
//#include <cmath>
//#include <vector>
//
//// Helper to avoid invalid distribution bounds
//float randf(std::mt19937_64& rng, float min, float max) {
//    if (min > max) std::swap(min, max);
//    std::uniform_real_distribution<float> dist(min, max);
//    return dist(rng);
//}
//
//// Particle for fireworks/expansion
//struct Particle {
//    sf::CircleShape shape;
//    sf::Vector2f velocity;
//    float lifetime;
//};
//
//// Confetti element
//struct Confetti {
//    sf::RectangleShape shape;
//    sf::Vector2f velocity;
//    float lifetime;
//};
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Ludo Winner Celebration");
//    window.setFramerateLimit(60);
//
//    std::mt19937_64 rng{ std::random_device{}() };
//
//    // --- Firework Particles ---
//    std::vector<Particle> firework;
//    auto spawnFirework = [&]() {
//        firework.clear();
//        sf::Vector2f origin = { 400, 500 };
//        for (int i = 0; i < 200; ++i) {
//            Particle p;
//            p.shape = sf::CircleShape(3);
//            p.shape.setFillColor(sf::Color::Yellow);
//            p.shape.setPosition(origin);
//            float angle = randf(rng, 0, 2 * 3.14159f);
//            float speed = randf(rng, 200, 400);
//            p.velocity = { std::cos(angle) * speed, std::sin(angle) * speed - 200 };
//            p.lifetime = randf(rng, 1.5f, 2.5f);
//            firework.push_back(p);
//        }
//        };
//    spawnFirework();
//
//    // --- Confetti ---
//    std::vector<Confetti> confetti;
//    for (int i = 0; i < 200; ++i) {
//        Confetti c;
//        float size = randf(rng, 5, 12);
//        c.shape = sf::RectangleShape({ size, size * 0.3f });
//        c.shape.setOrigin(size / 2, size / 2);
//        c.shape.setPosition(randf(rng, 0, 800), randf(rng, -50, 0));
//        c.shape.setFillColor(sf::Color(
//            static_cast<sf::Uint8>(randf(rng, 100, 255)),
//            static_cast<sf::Uint8>(randf(rng, 100, 255)),
//            static_cast<sf::Uint8>(randf(rng, 100, 255))
//        ));
//        float angle = randf(rng, 0, 2 * 3.14159f);
//        float speed = randf(rng, 100, 200);
//        c.velocity = { std::cos(angle) * speed, std::sin(angle) * speed };
//        c.lifetime = randf(rng, 2, 4);
//        confetti.push_back(c);
//    }
//
//    // --- Animated "WINNER" Text ---
//    sf::Font font;
//    font.loadFromFile("C:\\Users\\zakih\\OneDrive\\Desktop\\SFML_Project\\fonts\\YoungSerif-Regular.ttf"); // <-- Update path
//    sf::Text winner("WINNER\nPLAYER 1", font, 96);
//    winner.setOrigin(winner.getLocalBounds().width / 2, winner.getLocalBounds().height / 2);
//    winner.setPosition(400, 150);
//
//    // --- Dancing Pawns ---
//    struct Pawn { sf::CircleShape top, base; sf::VertexArray body; sf::Vector2f pos; };
//    std::vector<Pawn> pawns;
//    std::vector<sf::Color> colors{ sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow };
//    float startX = 200;
//    for (int i = 0; i < 4; ++i) {
//        Pawn p;
//        p.pos = { startX + i * 120, 400 };
//
//        float baseR = 30;
//        p.base = sf::CircleShape(baseR);
//        p.base.setOrigin(baseR, 0);
//        p.base.setFillColor(colors[i]);
//        p.base.setOutlineColor(sf::Color::Black);
//        p.base.setOutlineThickness(3);
//
//        float bodyW = 60, topW = 30, h = 60;
//        p.body = sf::VertexArray(sf::TriangleFan, 5);
//        p.body[0] = { {p.pos}, colors[i] };
//        p.body[1] = { {p.pos + sf::Vector2f(-bodyW / 2, 0)}, colors[i] };
//        p.body[2] = { {p.pos + sf::Vector2f(-topW / 2, -h)}, colors[i] };
//        p.body[3] = { {p.pos + sf::Vector2f(topW / 2, -h)}, colors[i] };
//        p.body[4] = p.body[1];
//
//        p.top = sf::CircleShape(topW / 2);
//        p.top.setOrigin(topW / 2, topW / 2);
//        p.top.setFillColor(colors[i]);
//        p.top.setOutlineColor(sf::Color::Black);
//        p.top.setOutlineThickness(2);
//
//        pawns.push_back(p);
//    }
//
//    sf::Clock clock;
//    float elapsed = 0;
//
//    while (window.isOpen()) {
//        float dt = clock.restart().asSeconds();
//        elapsed += dt;
//
//        sf::Event ev;
//        while (window.pollEvent(ev))
//            if (ev.type == sf::Event::Closed) window.close();
//
//        // Update firework
//        for (auto& p : firework) {
//            p.lifetime -= dt;
//            if (p.lifetime > 0) {
//                p.velocity.y += 300 * dt;
//                p.shape.move(p.velocity * dt);
//                p.shape.setFillColor(sf::Color(
//                    static_cast<sf::Uint8>(randf(rng, 200, 255)),
//                    static_cast<sf::Uint8>(randf(rng, 100, 200)),
//                    static_cast<sf::Uint8>(randf(rng, 0, 100))
//                ));
//            }
//        }
//        if (elapsed > 3.0f) { elapsed = 0; spawnFirework(); }
//
//        // Update confetti
//        for (auto& c : confetti) {
//            c.lifetime -= dt;
//            if (c.lifetime <= 0) {
//                c.lifetime = randf(rng, 2, 4);
//                c.shape.setPosition(randf(rng, 0, 800), randf(rng, -100, 0));
//            }
//            c.velocity.y += 200 * dt;
//            c.shape.move(c.velocity * dt);
//            c.shape.rotate(180 * dt);
//        }
//
//        // Update "WINNER" text animation
//        float scale = 1.0f + 0.2f * std::sin(elapsed * 3);
//        winner.setScale(scale, scale);
//        sf::Uint8 r = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 2));
//        sf::Uint8 g = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 3));
//        sf::Uint8 b = static_cast<sf::Uint8>(128 + 127 * std::sin(elapsed * 4));
//        winner.setFillColor({ r, g, b, 255 });
//
//        // Render everything
//        window.clear(sf::Color(15, 15, 40));
//
//        for (auto& c : confetti) window.draw(c.shape);
//        for (auto& p : firework) if (p.lifetime > 0) window.draw(p.shape);
//
//        window.draw(winner);
//
//        // Render pawns
//        for (int i = 0; i < pawns.size(); i++) {
//            auto& P = pawns[i];
//            float bounce = 10 * std::sin(elapsed * 4 + i);
//            float rotate = 15 * std::sin(elapsed * 2 + i);
//            sf::Transform t;
//            t.translate(P.pos.x, P.pos.y + bounce);
//            t.rotate(rotate, 0, 0);
//            window.draw(P.base, t);
//            window.draw(P.body, t);
//            P.top.setPosition(P.pos.x, P.pos.y + bounce - 60);
//            P.top.setRotation(rotate);
//            window.draw(P.top);
//        }
//
//        window.display();
//    }
//
//    return 0;
//}
//
