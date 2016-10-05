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

#ifndef FZX_TRANSFORM_HPP_
#define FZX_TRANSFORM_HPP_

#include "Mat22.hpp"
#include "Vec2.hpp"

namespace fzx
{

/**
 * Represents a set of geometrical transformations.
 */
class Transform
{
private:
   Mat22f mRotationMatrix; ///< The matrix that represents an objects rotation.
   Vec2f mTranslation; ///< The vector that represents an objects translation.
   float mAngle; ///< The angle that the object is rotated by counterclockwise.
public:

   /**
    * Creates a neutral transformation.
    *
    * The angle and translation is set to zero.
    */
   Transform() : mRotationMatrix(0), mTranslation(0, 0), mAngle(0) {}

   /**
    * Applies this transformation to a vector.
    *
    * A new vector with the same values as the parameter is rotated
    * and then shifted based on the values in this Transform.
    *
    * @param  vector The Vec2f to be transformed.
    * @return A new vector that is the parameter vector transformed by this
    * Transform.
    */
   Vec2f apply(Vec2f& vector);

   /**
    * Translates the transformation to a new location.
    *
    * @param delta The Vec2f to translate by.
    */
   void translate(Vec2f& delta);

   /**
    * Rotates the transformation to a new angle.
    *
    * @param delta The float that represents the angle to rotate by in radians.
    */
   void rotate(float delta);

   /**
    * Returns a Mat22f that is the rotation matrix of this Transform's angle.
    *
    * @return A Mat22f that is the rotation matrix of this Transform's angle.
    */
   Mat22f getRotationMatrix();

   /**
    * Returns a Vec2f that is the translation of this Transform.
    *
    * @return A Vec2f that is the translation of this Transform.
    */
   Vec2f& getTranslation();

   /**
    * Returns the angle that this Transform is rotated by.
    *
    * @return A float that is the angle this Transform is rotated by.
    */
   float getRotation();

   /**
    * Set's this Transform's angle to a specific value.
    *
    * @param theta A float that represents the new value of the rotation angle.
    */
   void setRotation(float theta);

   /**
    * Set the translation of this Transform to a specific value.
    *
    * @param translation A Vec2f that is the new value of this Transform's
    * translation.
    */
   void setTranslation(Vec2f& translation);
};

}

#endif /*FZX_TRANSFORM_HPP_*/
