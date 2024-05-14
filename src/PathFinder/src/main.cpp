#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/MenuPage.hpp"
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "PathFinder");

    MenuPage menu;
    MenuResult result = menu.Show(window);
    UnweightedAlgorithmsPage unweighted_algorithms_page;
    WeightedPage weighted_algorithms_page;
    switch (result) {
    case MenuResult::Unweighted:
        unweighted_algorithms_page.Display(window);
        break;
    case MenuResult::Weighted:
        weighted_algorithms_page.Display(window);
        break;
    case MenuResult::Quit:
        window.close();
        break;
    case MenuResult::Nothing:
        break;
    }

    return 0;
}