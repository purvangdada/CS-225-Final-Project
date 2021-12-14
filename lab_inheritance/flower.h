/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "circle.h"
#include "drawable.h"
#include "rectangle.h"
#include "triangle.h"
#include "vector2.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Rectangle* stem;
    Circle* pistil; // center piece of flower
    Triangle* leaf;

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;
    void clear();

  public:
    Flower(const Vector2& center);
    ~Flower();
    void draw(cs225::PNG* canvas) const;
};
