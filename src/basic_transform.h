#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
      // Note that both scale and trasnlation can be combined into a single 3x3 matrix for a 2d space.
      // So if we represetn such a matrix for f as A, and a matrix B for g, then we already know that ABx = A(Bx) = (AB)x, where x = [a,b,z]
      // where z is 0 if x is a vector and 1 if x is a point.
      //
      sf::Vector2f newScale = f.scale * g.scale;
      sf::Vector2f newTranslation = sf::Vector2f(f.scale.x * g.translation.x + f.translation.x,
                                     f.scale.y * g.translation.y + f.translation.y);

      return BasicTransform(newScale, newTranslation);

    }

    static BasicTransform inverse(const BasicTransform& f) {
      // We can compose both the scale S and the Translation T as T(Sx) = (TS)x.
      // (TS) has a rank of 3 so its invertible.

      sf::Vector2f inverseScale = sf::Vector2f(1.0f, 1.0f) / f.scale;
      sf::Vector2f inverseTranslation = (-f.translation) / f.scale; 
      return BasicTransform(inverseScale, inverseTranslation);
    }

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif
