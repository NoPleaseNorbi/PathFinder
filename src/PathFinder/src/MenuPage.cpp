#include "../headers/MenuPage.hpp"
#include "../headers/Button.hpp"

MenuResult MenuPage::Show(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile(PROJECT_SOURCE_DIR + std::string("/monoregular.ttf"))) {
        std::cerr << "Failed to load font" << std::endl;
    }

    sf::Text welcome_text;
    welcome_text.setFont(font);
    welcome_text.setCharacterSize(80);
    welcome_text.setString("Path Finder");
    welcome_text.setPosition({ 240, 100 });

    Button start_unweighted_button("Unweighted graph", { 400, 100 }, sf::Color(255, 32, 78), sf::Color::White);
    start_unweighted_button.setHoverColor(sf::Color(160, 21, 62));
    start_unweighted_button.setFont(font);
    start_unweighted_button.setPosition({ 300, 300 });

    Button start_weighted_button("Weighted graph", { 400, 100 }, sf::Color(255, 32, 78), sf::Color::White);
    start_weighted_button.setHoverColor(sf::Color(160, 21, 62));
    start_weighted_button.setFont(font);
    start_weighted_button.setPosition({ 300, 500 });
    
    Button quit_button("Quit", { 400, 100 }, sf::Color(255, 32, 78), sf::Color::White);
    quit_button.setHoverColor(sf::Color(160, 21, 62));
    quit_button.setFont(font);
    quit_button.setPosition({ 300, 700 });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return MenuResult::Quit;
            }
            else if (start_unweighted_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    return MenuResult::Unweighted;
                }
            }
            else if (start_weighted_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    return MenuResult::Weighted;
                }
            }
            else if (quit_button.MouseOver(window)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    return MenuResult::Quit;
                }
            }
        }

        window.clear(sf::Color(0, 34, 77));
        start_unweighted_button.Draw(window);
        start_weighted_button.Draw(window);
        quit_button.Draw(window);
        window.draw(welcome_text);
        window.display();
    }

    return MenuResult::Nothing;
}