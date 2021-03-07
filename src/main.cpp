#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <cmath>

#define SCALE 7000.f
#define WIDTH 1920
#define HEIGHT 1080
#define OFFSET_X 11900
#define OFFSET_Y 200
#define MAX_RECURSION_DEPTH 32

using namespace std;

int cabs(complex<float> n) {
	return sqrt(real(n)*real(n) + imag(n)*imag(n));
}

int computeShip(float x, float y, int depth) {
	complex<float> c(x, y);
	complex<float> z(0, 0);
	while (depth > 0) {
	    z.real(abs(z.real()));
        z.imag(abs(z.imag()));

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

		    const auto depth = (float) computeShip(mandlebrotX, mandlebrotY, MAX_RECURSION_DEPTH);

		    const auto color = sf::Color(0, 0, depth / (float) MAX_RECURSION_DEPTH * 255.f);

			dotIdea.setFillColor(color);
			dotIdea.setPosition((float) viewportX, (float) viewportY);
			window.draw(dotIdea);
		}
	}
	window.display();

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(window);
    if (texture.copyToImage().saveToFile("exportw.png"))
    {
        std::cout << "screenshot saved to " << "exportw.png" << std::endl;
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