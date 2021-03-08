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
	return 0;
}

void drawFractal(sf::RenderWindow &window) {
    window.clear();

    sf::Image fractalImage;
    fractalImage.create(WIDTH, HEIGHT);

    const int centralX = WIDTH / 2;
    const int centralY = HEIGHT / 2;

    for (int viewportX = 0; viewportX < WIDTH; ++viewportX) {
        for (int viewportY = 0; viewportY < HEIGHT; ++viewportY) {

            const auto mandlebrotX = (float) (viewportX - centralX - OFFSET_X) / SCALE;
            const auto mandlebrotY = (float) (viewportY - centralY - OFFSET_Y) / SCALE;

		    const auto depth = (float) computeMandelbrot(mandlebrotX, mandlebrotY, MAX_RECURSION_DEPTH);

		    const auto color = sf::Color(0, 0, depth / (float) MAX_RECURSION_DEPTH * 255.f);

            fractalImage.setPixel(viewportX, viewportY, color);
        }
    }

    sf::Texture texture;
    texture.loadFromImage(fractalImage);  //Load Texture from image

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);
    window.display();
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");

	drawFractal(window);

    //if (texture.copyToImage().saveToFile("exportj.png"))
    //{
    //    std::cout << "screenshot saved to " << "exportj.png" << std::endl;
    //}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}