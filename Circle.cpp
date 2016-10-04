#include "Circle.hpp"

namespace fzx
{

Circle::Circle(float radius) : mRadius(radius) {}
Circle::Circle() : mRadius(1.0f) {}

Vec2f Circle::getBoundingBox()
{
   return Vec2f(mRadius * 2, mRadius * 2);
}

float Circle::getRadius()
{
   return mRadius;
}

float Circle::getArea()
{
   return 3.1415926f * mRadius * mRadius;
}

Vec2f Circle::getSupport(Vec2f& direction)
{
   return (direction / direction.getMagnitude()) * mRadius;
}

Shape::ShapeType Circle::getType()
{
   return Shape::CIRCLE;
}

}
