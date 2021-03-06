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

#ifndef FZX_CIRCLE_HPP_
#define FZX_CIRCLE_HPP_

#include "Shape.hpp"

namespace fzx
{

/**
 * Represents a shape who's edge is equidistant from a single point.
 *
 * Extends the shape class.
 */
class Circle : public Shape
{
private:
   float mRadius; ///< The radius of the circle.
public:
   /**
    * Creates a circle with a given radius.
    *
    * @param radius A float that represents the circle's radius.
    */
   Circle(float radius);

   /**
    * Creates a circle with radius 1.
    */
   Circle();

   void setRadius(float radius); 

   //The rest of the methods are overrides. Documentation is inherited.
   float getRadius() const;
   float getArea() const;
   float getInertiaPerMass() const;
   Shape::BoundingBox getBoundingBox(const Transform& transform) const;
   Vec2f getSupport(const Vec2f& direction, const Transform& transform) const;
   Shape::ShapeType getType() const;
};

}

#endif /*FZX_CIRCLE_HPP_*/
