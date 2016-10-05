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

#ifndef BODY_HPP_
#define BODY_HPP_

#include <vector>

#include "Shape.hpp"
#include "Circle.hpp"
#include "Vec2.hpp"

namespace fzx {

class Body {
public:
	enum BodyType
	{
		STATIC, KINEMATIC, DYNAMIC
	};
	enum ForceType
	{
		FORCE, IMPULSE, ACCELERATION, VELOCITY
	};
	struct Material
	{
		float density, staticFriction, kineticFriction, restitution;
	};
	struct MassData
	{
		float mass, inverseMass, inertia, inverseInertia;
	};
private:
	BodyType mBodyType;
	MassData mMassData;
	Material mMaterial;
	Shape* mShape;
	Transform mTransform;
	Vec2f mVelocity;
	Vec2f mForce;
	float mAngularVelocity;
	float mTorque;
	int mLayer;
	void calculateMassData();
public:
	Body();
	~Body();

	void step(float dt);

	void applyPush(const Vec2f& push, ForceType forceType = IMPULSE);
	void applyTwist(float twist, ForceType forceType = IMPULSE);
	Vec2f getPush(ForceType forceType = IMPULSE) const;
	float getTwist(ForceType forceType = IMPULSE) const;
	void setPush(const Vec2f& push, ForceType forceType = IMPULSE);
	void setTwist(float twist, ForceType forceType = IMPULSE);

	BodyType getType() const;
	MassData getMassData() const;
	Material getMaterial() const;
	Transform& getTransform();
	Shape& getShape();
	int getLayer() const;

	void setBodyType(BodyType type);
	void setMaterial(Material material);
	void setLayer(int layer);

	void setShapeToCircle(float radius);
	void setShapeToRectangle(float width, float height);
	void setShapeToPolygon(std::vector<Vec2f> vertices);
};

}

#endif /* BODY_HPP_ */
