#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

float v2fNorm(Vector2f v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f raycast(Vector2f start, Vector2f mouse, Image img) {
    // Grab the normalized vector
    Vector2f u = mouse - start;
    u /= v2fNorm(u);

    Rect<float> r(Vector2f(0, 0), (Vector2f) img.getSize());

    // Do it until you go outside of the bounds
    while (r.contains(start.x, start.y)) {
        if (img.getPixel(start.x, start.y) != Color::Black &&
            img.getPixel(start.x, start.y) != Color::Red) {
            // We've hit it!
            return start;
        }

        start += u;
    }

    return start;
}

int main() {
    RenderWindow w(VideoMode(500, 500), "Raycast Thingy", Style::Close);
    Event evt;
    Texture wt;
    Image img;
    Vector2f start(250, 250);
    CircleShape c;
    std::vector<decltype(Mouse::getPosition())> cpos;
    bool hasDrawn = false;

    wt.create(w.getSize().x, w.getSize().y);
    wt.update(w);
    img = wt.copyToImage();

    c.setFillColor(Color::White);
    c.setRadius(10);

    while (w.isOpen()) {
        while (w.pollEvent(evt)) {
            switch (evt.type) {
            case Event::Closed:
                w.close();
                break;
            case Event::MouseButtonReleased:
                cpos.push_back(Mouse::getPosition() - w.getPosition());
                hasDrawn = true;
                break;
            default:
                break;
            }
        }

        w.clear();

        // Draw line with raycasting
        VertexArray vs(Lines, 2);
        vs[0].position = start;
        vs[1].position = raycast(start,
                                (Vector2f) (Mouse::getPosition() - w.getPosition()),
                                img);
        vs[0].color = Color::Red;
        vs[1].color = Color::Red;
        w.draw(vs);

        for (auto v : cpos) {
            c.setPosition(v.x, v.y);
            w.draw(c);
        }

        if (hasDrawn) {
            wt.update(w);
            img = wt.copyToImage();
            hasDrawn = false;
        }

        w.display();
    }
}
