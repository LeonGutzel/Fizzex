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

#ifndef FZX_MAT22_HPP_
#define FZX_MAT22_HPP_

#include "Vec2.hpp"

namespace fzx {

#include <cmath>

/**
 * A class that represents a 2-by-2 matrix.
 *
 * This matrix is represented by two, 2-dimensional column vectors.
 */
template <typename T>
class Mat22
{
private:
	Vec2<T> mLeftColumn; ///< The left-most column of the matrix.
	Vec2<T> mRightColumn; ///< The right-most column of the matrix.
public:
	/**
	 * Creates the identity matrix.
	 *
	 * Sets the first column vector to (1, 0) and the second to (0, 1)
	 */
	Mat22() : mLeftColumn(1, 0), mRightColumn(0, 1) {}

	/**
	 * Creates a rotation matrix based on an angle.
	 *
	 * Sets the left column to (cos(t), sin(t)) and the right column to
	 * (-sin(t), cos(t)), where t is the angle of rotation.
	 *
	 * @param The angle of rotation of the matrix.
	 */
	Mat22(T theta)
	{
		mLeftColumn.x = cos(theta);
		mLeftColumn.y = sin(theta);
		mRightColumn.x = -mLeftColumn.y;
		mRightColumn.y = mLeftColumn.x;
	}

	/**
	 * Creates a matrix based on given column vectors.
	 *
	 * @param leftColumn The left column of the matrix.
	 * @param rightColumn The right column of the matrix.
	 */
	Mat22(Vec2<T> leftColumn, Vec2<T> rightColumn)
	{
		mLeftColumn = leftColumn;
		mRightColumn = rightColumn;
	}

	/**
	 * Creates a matric given the individual elements.
	 *
	 * The elements are given in terms of the matrix's column vectors.
	 *
	 * @param lx The x-component of the left column vector.
	 * @param ly The y-component of the left column vector.
	 * @param rx The x-component of the right column vector.
	 * @param ry The y-component of the right column vector.
	 */
	Mat22(T lx, T ly, T rx, T ry) : mLeftColumn(lx, ly), mRightColumn(rx, ry) {}

	/**
	 * Creates a matrix that is the addition of two matrices.
	 *
	 * Creates a matrix that represents the sum of this instance and the
	 * parameter matrix.
	 *
	 * @param matrix The matrix that will be added to this instance.
	 * @return A new matrix that is the sum of this and the paramter.
	 */
	Mat22 operator+(Mat22& matrix)
	{
		return Mat22(mLeftColumn + matrix.mLeftColumn,
							mRightColumn + matrix.mRightColumn);
	}

	/**
	 * Creates a matrix that is the subtraction of two matrices.
	 *
	 * Creates a matrix that represents the difference of this instance and the
	 * parameter matrix.
	 *
	 * @param matrix The matrix that will be subtracted from this instance.
	 * @return A new matrix that is the difference of this and the paramter.
	 */
	Mat22 operator-(Mat22 &matrix)
	{
		return Mat22(mLeftColumn - matrix.mLeftColumn,
							mRightColumn - matrix.mRightColumn);
	}

	/**
	 * Creates a matrix that is a scale of this matrix.
	 *
	 * @param s The real that will scale this matrix.
	 * @return A new matrix that represents this instance scaled by s.
	 */
	Mat22 operator*(T s)
	{
		return Mat22(mLeftColumn * s, mRightColumn * s);
	}

	/**
	 * Creates a new matrix that is this one inversly scaled.
	 *
	 * @param s The real that will inversly scale this matrix. Will throw an
	 * exception if s is 0.
	 * @return A new matrix that is this inversly scaled by s.
	 */
	Mat22 operator/(T s)
	{
		return Mat22(mLeftColumn / s, mRightColumn / s);
	}

	/**
	 * Adds a matrix to this instance.
	 *
	 * @param matrix The matrix that will be added to this instance.
	 * @return A reference to this instance.
	 */
	Mat22& operator+=(Mat22 &matrix)
	{
		mLeftColumn += matrix.mLeftColumn;
		mRightColumn += matrix.mRightColumn;
		return *this;
	}

	/**
	 * Subtracts a matrix from this instance.
	 *
	 * @param matrix The matrix that will be subtracted from this instance.
	 * @return A reference to this instance.
	 */
	Mat22& operator-=(Mat22 &matrix)
	{
		mLeftColumn -= matrix.mLeftColumn;
		mRightColumn -= matrix.mRightColumn;
		return *this;
	}

	/**
	 * Scales this instance matrix.
	 *
	 * @param s The real that will scale this instance.
	 * @return A reference to this instance.
	 */
	Mat22& operator*=(T s)
	{
		mLeftColumn *= s;
		mRightColumn *= s;
		return *this;
	}

	/**
	 * Inversly-scales this instance matrix.
	 *
	 * @param s The real that will inversly scale this instance. Will throw an
	 * exception if s is 0.
	 * @return A reference to this instance.
	 */
	Mat22& operator/=(T s)
	{
		mLeftColumn /= s;
		mRightColumn /= s;
		return *this;
	}

	/**
	 * Creates a matrix that is the product of this instance and the parameter.
	 *
	 * @param matrix The matrix that will be multiplied to this instance.
	 * @return A new matrix that represents the product of this matrix and the
	 * parameter.
	 */
	Mat22 operator*(Mat22 &matrix)
	{
		Mat22 output;
		output.mLeftColumn.x = mLeftColumn.x * matrix.mLeftColumn.x +
										mRightColumn.x * matrix.mLeftColumn.y;
		output.mLeftColumn.y = mLeftColumn.y * matrix.mLeftColumn.x +
										mRightColumn.y * matrix.mLeftColumn.y;
		output.mRightColumn.x = mLeftColumn.x * matrix.mLeftColumn.x +
										mRightColumn.x * matrix.mRightColumn.y;
		output.mRightColumn.y = mLeftColumn.y * matrix.mRightColumn.y +
										mRightColumn.y * matrix.mRightColumn.y;
		return output;
	}

	/**
	 * Returns a vector that is a product of this matrix and a vector.
	 *
	 * @param vector The vector to be multiplied to this matrix.
	 * @return The product of this matrix and the parameter.
	 */
	Vec2<T> operator*(Vec2<T>& vector)
	{
		Vec2<T> output;
		output.x = mLeftColumn.x * vector.x +
						mRightColumn.x * vector.y;
		output.y = mLeftColumn.y * vector.x +
						mRightColumn.y * vector.y;
		return output;
	}

	/**
	 * Returns the determinant of this matrix.
	 * @return A real that represents the determinant of this matrix.
	 */
	T getDeterminant()
	{
		return mLeftColumn.x * mRightColumn.y - mRightColumn.x * mLeftColumn.y;
	}

	/**
	 * Returns the inverse of this matrix.
	 * @return A new matrix that is the inverse of this instance.
	 */
	Mat22 getInverse()
	{
		Mat22 output;
		output.mLeftColumn.x = mRightColumn.y;
		output.mRightColumn.y = mLeftColumn.x;
		output.mLeftColumn.y = -mLeftColumn.y;
		output.mRightColumn.x = -mRightColumn.y;
		return output / getDeterminant();
	}
};

typedef Mat22<float> Mat22f;
typedef Mat22<double> Mat22d;

}

#endif /* FZX_MAT22_HPP_ */
