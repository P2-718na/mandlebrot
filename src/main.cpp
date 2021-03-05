#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>

#define SCALE 200.f
#define WIDTH 600
#define HEIGHT 600
#define OFFSET_X 150
#define OFFSET_Y 0
#define MAX_RECURSION_DEPTH 32

using namespace std;

int cabs(complex<float> n) {
	return sqrt(real(n)*real(n) + imag(n)*imag(n));
}

int computeMandelbrot(float x, float y, int depth) {
	complex<float> c(x, y);
	complex<float> z(0, 0);
	while (depth > 0) {
		z = pow(z, complex<float>(2, 0)) + c;
		if (cabs(z) > 2) {
			return depth;
		}
		--depth;
	}
	return true;
}

int main() {
	sf::Color rainbow[] = { sf::Color::Black, sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");
	sf::RectangleShape dotIdea(sf::Vector2f(1, 1));

	window.clear();

	for (int i = -WIDTH/2 - OFFSET_X; i < WIDTH/2 - OFFSET_X; i++) {
		for (int j = -HEIGHT/2 - OFFSET_Y; j < HEIGHT/2 - OFFSET_Y; j++) {
		    const float depth = computeMandelbrot(i/SCALE, j/SCALE, MAX_RECURSION_DEPTH);
			dotIdea.setFillColor(sf::Color(0, 0, depth / (float)MAX_RECURSION_DEPTH * 255.f));
			dotIdea.setPosition(i + WIDTH/2 + OFFSET_X, j + HEIGHT/2 + OFFSET_Y);
			window.draw(dotIdea);
		}
		//cout << i << endl;
		
	}
	window.display();
	

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}