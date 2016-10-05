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

#ifndef FZX_VEC2_HPP_
#define FZX_VEC2_HPP_

#include <cmath>

namespace fzx
{

/**
 * A class that represents a 2-dimensional, real vector.
 *
 * Uses a template paramter to represent the real components.
 * Overloads the traditional mathematical operators used for vectors
 * such as +, -, /, and *.
 */
template <typename T>
struct Vec2
{
	T x; ///< The x-component of the vector.
	T y; ///< The y-component of the vector.

	/**
	 * Creates a vector at the origin.
	 *
	 * Set's the x and y components to 0.
	 */
	Vec2() : x(0), y(0) {}

	/**
	 * Creates a vector with the given components.
	 *
	 * @param x The x-component of the vector.
	 * @param y The y-component of the vector.
	 */
	Vec2(T x, T y) : x(x), y(y) {}

	/**
	 * Returns the sum of two vectors.
	 *
	 * Creates a new vector that is the vector sum of this instance and the
	 * parameter.
	 *
	 * @param vector A reference to the vector that will be added to this
	 * instance.
	 * @return A new vector that is the sum of this instance and the parameter.
	 */
	Vec2<T> operator+(const Vec2<T>& vector) const
	{
		return Vec2<T>(this->x + vector.x, this->y + vector.y);
	}

	/**
	 * Returns the difference of two vectors.
	 *
	 * Creates a new vector that is the vector difference of this vector and
	 * the parameter.
	 *
	 * @param vector A reference to the vector that will be subtracted from to
	 * this instance.
	 * @return A new vector that is the sum of this instance and the parameter.
	 */
	Vec2<T> operator-(const Vec2<T>& vector) const
	{
		return Vec2<T>(this->x - vector.x, this->y - vector.y);
	}

	/**
	 * Creates a scaled vector.
	 *
	 * Returns a new vector that is a scaled version of this instance.
	 *
	 * @param s The scale that will be applied to this vector.
	 * @return A new vector that is this vector scaled by the parameter.
	 */
	Vec2<T> operator*(T s) const
	{
		return Vec2<T>(this->x * s, this->y * s);
	}

	/**
	 * Creates a inversly scaled vector.
	 *
	 * Returns a new vector that is a inversly scaled verion of this instance.
	 *
	 * @param The real that will inversly scale this vector. If it is zero, an
	 * exception will be thrown.
	 * @return A new vector that is this vector inversly scaled by the parameter.
	 */
	Vec2<T> operator/(T s) const
	{
		return Vec2<T>(this->x / s, this->y / s);
	}

	/**
	 * Adds a vector to this instance.
	 *
	 * Adds the paramter vector to this instance and returns a reference to
	 * itself.
	 *
	 * @param vector A reference to the vector that will be added to this
	 * instance.
	 * @return A reference to this instance.
	 */
	Vec2<T>& operator+=(const Vec2<T>& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		return *this;
	}

	/**
	 * Subtracts a vector from this instance.
	 *
	 * Subtracts the paramter vector from this instance and returns a reference to
	 * itself.
	 *
	 * @param vector A reference to the vector that will be subtracted from to
	 * this instance.
	 * @return A reference to this instance.
	 */
	Vec2<T>& operator-=(const Vec2<T> &vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		return *this;
	}

	/**
	 * Scales this vector.
	 *
	 * Scales this vector by a real and returns a reference to itself.
	 *
	 * @param s The real that will scale this vector.
	 * @return A reference to this instance.
	 */
	Vec2<T>& operator*=(T s)
	{
		this->x *= s;
		this->y *= s;
		return *this;
	}

	/**
	 * Inversly scales this vector.
	 *
	 * Inversly scales this vector by a real and returns a reference to itself.
	 *
	 * @param s The real that will inversly scale this vector.
	 * @return A reference to this instance.
	 */
	Vec2<T>& operator/=(T s)
	{
		this->x /= s;
		this->y /= s;
		return *this;
	}

	/**
	 * Calculates the dot product between two vectors.
	 *
	 * Calculates the dot product between this vector and the parameter vector.
	 *
	 * @param vector A reference to the vector that will be operated with this
	 * instance.
	 * @return A real representing the dot product.
	 */
	T operator*(const Vec2<T> &vector) const
	{
		return this->x * vector.x + this->y * vector.y;
	}

	/**
	 * Calculates the cross product between two vectors.
	 *
	 * Calculates the cross product between this vector and the paramter vector.
	 * The cross product is only defined for three dimensional vectors, so here
	 * we asume that the third component is 0. This would result in a vector with
	 * one non-zero component. It is that component that is returned.
	 *
	 * @param vector A reference to the vector that will be operated with this
	 * instance.
	 * @return The real that represents the cross product between the two.
	 */
	T operator%(const Vec2<T> &vector) const
	{
		return this->x * vector.y - vector.x * this->y;
	}

	/**
	 * Sets the components of this vector.
	 *
	 * Sets the components of this vector to the given parameters.
	 *
	 * @param x A real representing the x-component.
	 * @param y A real representing the y-component.
	 */
	void set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	/**
	 * Calculates the sqaure magnitude of this vector.
	 *
	 * Calculatesthe square magnintude of this vector. This method is
	 * considerably faster than calculating the actual magnitude and should be
	 * used when one only needs to compare magnitudes without specific accuracy.
	 *
	 * @see getMagnitudeS()
	 * @return A real representing the square magnitude of the vector.
	 */
	T getMagnitudeSquared() const
	{
		return this->x * this->x + this->y * this->y;
	}

	/**
	 * Calculates the magnitude of this vector.
	 *
	 * @return A real representing the magnitude of this vector.
	 */
	T getMagnitude() const
	{
		return std::sqrt(getMagnitudeSquared());
	}

	/**
	 * Calculates the direction of this vector.
	 *
	 * Calculates the direction of this vector in radians. The angle is measured
	 * from the positive x-axis, counterclockwise.
	 *
	 * @return A real representing the direction in radians.
	 */
	T getDirection()  const
	{
		return std::atan2(y, x);
	}
};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

}

#endif /* FZX_VEC2_HPP_ */
