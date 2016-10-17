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

#include "Circle.hpp"

namespace fzx
{

Circle::Circle(float radius) : mRadius(radius) {}
Circle::Circle() : mRadius(1.0f) {}

void Circle::setRadius(float radius)
{
   mRadius = radius; 
}

float Circle::getRadius() const
{
   return mRadius;
}

float Circle::getArea() const
{
   return 3.1415926f * mRadius * mRadius;
}

float Circle::getInertiaPerMass() const
{
   return mRadius * mRadius / 2;
}

Shape::BoundingBox Circle::getBoundingBox(const Transform& transform) const
{
   Shape::BoundingBox boundary;
   boundary.lowerLeft.set(-mRadius, -mRadius);
   boundary.upperRight = boundary.lowerLeft * -1;
   boundary.lowerLeft += transform.getTranslation();
   boundary.upperRight += transform.getTranslation();
   return boundary;
}

Vec2f Circle::getSupport(const Vec2f& direction, const Transform& transform) const
{
   return (direction/direction.getMagnitude()) * mRadius;
}

Shape::ShapeType Circle::getType() const
{
   return Shape::CIRCLE;
}

}
