#include "Rectangle.hpp"
#include <cmath>

namespace fzx
{

Rectangle::Rectangle(float width, float height) : mWidth(width), mHeight(height) {}
Rectangle::Rectangle() : mWidth(1.0f), mHeight(1.0f) {}

Vec2f Rectangle::getBoundingBox()
{
   return Vec2f(mWidth, mHeight);
}

float Rectangle::getRadius()
{
   //Pythagorean theorem for the diameter, then half for radius.
   return std::sqrt(mWidth * mWidth + mHeight * mHeight) / 2;
}

float Rectangle::getArea()
{
   return mWidth * mHeight;
}

Vec2f Rectangle::getSupport(Vec2f& direction, Transform& transform)
{
   Vec2f upperRight, lowerRight;
	upperRight.set(mWidth / 2, mHeight / 2);
	lowerRight.set(mWidth / 2, -mHeight / 2);

   //Apply the transform, but remove the translation so only rotation and scale is left.
	upperRight = transform.apply(upperRight) - transform.getTranslation();
	lowerRight = transform.apply(lowerRight) - transform.getTranslation();
	float dot1 = direction * upperRight;
	float dot2 = direction * lowerRight;

   //The higher dot product means that it's more in the same direction.
	if (std::abs(dot1) > std::abs(dot2))
   {
		if (dot1 < 0) return upperRight * -1; //LowerLeft
		else return upperRight;
	}
   else
   {
		if (dot2 < 0) return lowerRight * -1; //UpperLeft
		else return lowerRight;
	}
}

Shape::ShapeType Rectangle::getType()
{
   return Shape::RECTANGLE;
}

}
