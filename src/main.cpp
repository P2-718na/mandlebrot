#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <cmath>

#define SCALE 300.f
#define WIDTH 1024
#define HEIGHT 1024
#define OFFSET_X 0
#define OFFSET_Y 0
#define MAX_RECURSION_DEPTH 30

using namespace std;

int cabs(complex<float> n) {
	return sqrt(real(n)*real(n) + imag(n)*imag(n));
}

int computeJulia(float x, float y, int depth) {
    const complex<float> c(0, 0.8);

    complex<float> z(x, y);
	while (depth > 0) {
		z = pow(z, complex<float>(2, 0)) + c;
		if (cabs(z) > 2) {
			return depth;
		}
		--depth;
	}
	return 0;
}

int main() {
	sf::Color rainbow[] = { sf::Color::Black, sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");
	sf::RectangleShape dotIdea(sf::Vector2f(1, 1));

	window.clear();

	const int centralX = WIDTH / 2;
	const int centralY = HEIGHT / 2;

	for (int viewportX = 0; viewportX < WIDTH; ++viewportX) {
		for (int viewportY = 0; viewportY < HEIGHT; ++viewportY) {

		    const auto mandlebrotX = (float) (viewportX - centralX - OFFSET_X) / SCALE;
            const auto mandlebrotY = (float) (viewportY - centralY - OFFSET_Y) / SCALE;

		    const auto depth = (float) computeJulia(mandlebrotX, mandlebrotY, MAX_RECURSION_DEPTH);

		    const auto color = sf::Color(depth / (float) MAX_RECURSION_DEPTH * 255.f, depth / (float) MAX_RECURSION_DEPTH * 255.f, 0);

			dotIdea.setFillColor(color);
			dotIdea.setPosition((float) viewportX, (float) viewportY);
			window.draw(dotIdea);
		}
	}
	window.display();

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(window);
    if (texture.copyToImage().saveToFile("exportj.png"))
    {
        std::cout << "screenshot saved to " << "exportj.png" << std::endl;
    }

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}