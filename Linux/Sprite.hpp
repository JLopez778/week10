#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <memory>
#include "Component.hpp"

class GameObject;
class Texture;

class Sprite : public Component {

public:
    Sprite();
    ~Sprite();

    void setTexture(std::shared_ptr<Texture> newTexture);
    std::shared_ptr<Texture> getTexture();

private:
    std::shared_ptr<Texture> texture;
};

#endif