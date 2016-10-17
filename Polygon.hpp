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

#ifndef FZX_POLYGON_HPP_
#define FZX_POLYGON_HPP_

#include <vector>
#include "Shape.hpp"

namespace fzx
{

/**
 * A class that represents the shape of a convex polygon.
 */
class Polygon : public Shape
{
private:
   std::vector<Vec2f> mVertices; ///< The vertices of the shape in counterclockwise order.
   std::vector<Vec2f> mNormals; ///< The normals of all the sides.

   /**
    * Calculates the normals of the sides.
    */
   void calculateNormals();
public:
   /**
    * Creates a Polygon with the given vertices.
    *
    * If the center of the vertices is not at (0, 0), they will be shifted so
    * that they are.
    *
    * If the veritces given form a concave Polygon, points will be removed to
    * make it convex.
    *
    * If less than three point are supplied, a third one will be created at
    * (-1, -1), (2, -1), and (-1, 2) as needed. The shift will take place after.
    *
    * @param vertices A list of Vec2f that represent the vertices of this
    * polygon.
    */
   Polygon(std::vector<Vec2f> vertices);

   /**
    * Creates a right triangle polygon with vertices at coordinates (-1, -1),
    * (2, -1), and (-1, 2)
    */
   Polygon();

   /**
    * Returns the number of vertices this Polygon has.
    *
    * @return An unsigned integer representing the number of vertices in this Polygon.
    */
   unsigned getNumberOfVertices() const;

   /**
    * A specific vertix in the Polygon.
    *
    * @param  index The index of the vertix desired.
    * @return The desired vertix of the Polygon.
    */
   const Vec2f& getVertix(unsigned int index) const;

   /**
    * The normal of a side in of the polygon.
    *
    * The sides are index starting at the first vertix going counterclockwise.
    * The normal points into the shape.
    *
    * @param index The index of the normal desired.
    * @param The desired normal of the polygon.
    */
   const Vec2f& getNormal(unsigned int index) const;

   //The rest of the methods are overrides. Documentation is inherited.
   float getRadius() const;
   float getArea() const;
   float getInertiaPerMass() const;
   Shape::BoundingBox getBoundingBox(const Transform& transform) const;
   Vec2f getSupport(const Vec2f& direction, const Transform& transform) const;
   Shape::ShapeType getType() const;
};

}

#endif /*FZX_POLYGON_HPP_*/
