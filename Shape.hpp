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

#ifndef FZX_SHAPE_HPP_
#define FZX_SHAPE_HPP_

#include "Transform.hpp"
#include "Vec2.hpp"

namespace fzx {

/**
 * Represents a Shape in the 2D plane.
 *
 * Can represent Rectangles, Circles, and convex Polygons.
 */
class Shape
{
public:
	/**
	 * An enum that represents the type of Shape this class represents.
	 */
	enum ShapeType
	{
		CIRCLE, RECTANGLE, POLYGON
	};

	//Destructor made virtual to allow subclasses to override it
	virtual ~Shape(){};

	/**
	 * Returns an axis-aligned bound box that completely sorrounds the Shape.
	 *
	 * The box shares the same center as this Shape and it's dimensions are
	 * stored in a Vec2f.
	 *
	 * @return A Vec2f with an x that represents the box's width and a y that
	 * represents the box's y.
	 */
	virtual Vec2f getBoundingBox() = 0;

	/**
	 * Returns the radius of a circle that completely sorrounds this Shape.
	 *
	 * The circle shares the same center as this Shape.
	 *
	 * @return A float that is the radius of the sorrounding circle.
	 */
	virtual float getRadius() = 0;

	/**
	 * Returns the area of the Shape.
	 *
	 * @return A float representing the area of the Shape.
	 */
	virtual float getArea() = 0;

	/**
	 * Returns the nearest vertex of the shape in the direction of the parameter.
	 *
	 * @param direction A Vec2f that represents the direction the vertex should
	 * be near to.
	 * @param transform A Transform that is used to rotate and scale the shape
	 * to the desired. basis.
	 * @return The closes vertex in the direction of the parameter. If the shape
	 * is a circle, then it will return a vector from the center to the
	 * circumference with the direction of the parameter.
	 */
	virtual Vec2f getSupport(Vec2f& direction, Transform& transform) = 0;

	/**
	 * Returns the ShapeType of the Shape.
	 *
	 * @return The ShapeType of the Shape.
	 */
	virtual ShapeType getType() = 0;
};

}

#endif /* FZX_SHAPE_HPP_ */
