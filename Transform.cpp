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
///
#include "Transform.hpp"

namespace fzx {

Vec2f Transform::apply(Vec2f& vector)
{
   return mRotationMatrix * vector * mScale + mTranslation;
}

void Transform::translate(Vec2f& delta)
{
   mTranslation += delta;
}
void Transform::rotate(float delta)
{
   mAngle += delta;
   mRotationMatrix = Mat22f(mAngle);
}
void Transform::scale(float scale)
{
   mScale *= scale;
}

Mat22f Transform::getRotationMatrix()
{
   return mRotationMatrix;
}

Vec2f& Transform::getTranslation()
{
   return mTranslation;
}

float Transform::getRotation()
{
   return mAngle;
}

float Transform::getScale()
{
   return mScale;
}

void Transform::setRotation(float theta)
{
   mAngle = theta;
   mRotationMatrix = Mat22f(theta);
}

void Transform::setScale(float scale)
{
   mScale = scale;
}

void Transform::setTranslation(Vec2f& translation)
{
   mTranslation = translation;
}

}
