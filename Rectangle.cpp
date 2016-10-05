////////////////////////////////////////////////////////////
//
// Fizzex - The Simple Physics Library
// Copyright (C) 2014-2016 Leonardo Gutierrez (leongflux@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "Rectangle.hpp"
#include <cmath>
#include <algorithm>

namespace fzx
{

Rectangle::Rectangle(float width, float height) : mWidth(width), mHeight(height) {}
Rectangle::Rectangle() : mWidth(1.0f), mHeight(1.0f) {}

float Rectangle::getRadius() const
{
   //Pythagorean theorem for the diameter, then half for radius.
   return std::sqrt(mWidth * mWidth + mHeight * mHeight) / 2;
}

float Rectangle::getWidth() const
{
   return mWidth;
}

float Rectangle::getHeight() const
{
   return mHeight;
}

float Rectangle::getArea() const
{
   return mWidth * mHeight;
}

float Rectangle::getInertiaPerMass() const
{
   return (mWidth * mWidth + mHeight * mHeight) / 12;
}

Shape::BoundingBox Rectangle::getBoundingBox(const Transform& transform) const
{
   Vec2f upperRight = Vec2f(mWidth / 2, mHeight / 2);
   Vec2f lowerRight = Vec2f(mWidth / 2, -mHeight / 2);

   //Apply the transform, but remove the translation so only rotation is left.
   upperRight = transform.apply(upperRight) - transform.getTranslation();
   lowerRight = transform.apply(lowerRight) - transform.getTranslation();

   float maximumX = std::max(std::abs(upperRight.x), std::abs(lowerRight.x));
   float maximumY = std::max(std::abs(upperRight.y), std::abs(lowerRight.y));

   Shape::BoundingBox boundary;
   boundary.upperRight.set(maximumX, maximumY);
   boundary.lowerLeft = boundary.upperRight * -1;
   return boundary;
}

Vec2f Rectangle::getSupport(const Vec2f& direction, const Transform& transform) const
{
   Vec2f upperRight = Vec2f(mWidth / 2, mHeight / 2);
   Vec2f lowerRight = Vec2f(mWidth / 2, -mHeight / 2);

   //Apply the transform, but remove the translation so only rotation is left.
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

Shape::ShapeType Rectangle::getType() const
{
   return Shape::RECTANGLE;
}

}
