#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include "registry.h"

using SpriteID = size_t;

class SpriteManager {

  public:

  sf::Texture& registerTexture(const std::string& filepath) {
    mTextures.push_back(sf::Texture(filepath));
    return mTextures[mTextures.size() - 1]; // probably a safer way to do this.
  }

  template <typename... Args>
  SpriteID createSprite(Args&&... args) {
    return mSpriteRegistry.store(std::forward<Args>(args)...);
  }

  Sprite& getSprite(SpriteID id) {
    return mSpriteRegistry[id];
  }
  
  private:
  
  std::vector<sf::Texture> mTextures;
  Registry<Sprite> mSpriteRegistry;
};

#endif  // SPRITE_MANAGER_H
