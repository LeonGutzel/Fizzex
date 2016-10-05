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

#ifndef FZX_RECTANGLE_HPP_
#define FZX_RECTANGLE_HPP_

#include "Shape.hpp"

namespace fzx
{

/**
 * Represents a shape that has four sides and four right angles.
 *
 * Extends the Shape class.
 */
class Rectangle : public Shape
{
private:
   float mWidth; ///< The width of this Rectangle.
   float mHeight; ///< The height of this Rectangle.
public:
   /**
    * Creates a Rectangle with a given width and height.
    *
    * @param width A float that is the width of the rectangle.
    * @param height A float that is the height of the rectangle.
    */
   Rectangle(float width, float height);

   /**
    * Creates a Reactangle with a width and height of 1.
    */
   Rectangle();

   //The rest of the methods are overrides. Documentation is inherited.
   float getRadius() const;
   float getArea() const;
   float getMomentPerMass() const;
   BoundingBox getBoundingBox(const Transform& transform) const;
   Vec2f getSupport(const Vec2f& direction, const Transform& transform) const;
   Shape::ShapeType getType() const;
};

}

#endif /*FZX_RECTANGLE_HPP_*/
