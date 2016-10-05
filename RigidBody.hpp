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

#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include <vector>

#include "Shape.hpp"
#include "Circle.hpp"
#include "Vec2.hpp"

namespace fzx {

/**
 * A class that represents a rigid body in 2D space.
 */
class RigidBody {
public:
	/**
	 * The type of RigidBody.
	 *
	 * STATIC means that it isn't affected by external objects or forces, but
	 * other objects are still affected by it. It is always stationary.
	 *
	 * KINEMATIC means it can be affected by outside forces, but not by objects.
	 * Other objects still react to it.
	 *
	 * DYNAMIC means that is completely interacts with it's enviroment.
	 */
	enum BodyType
	{
		STATIC, KINEMATIC, DYNAMIC
	};

	/**
	 * Force type is used to differentiate between different pushes and twists.
	 *
	 * FORCE means Translational Force or Torque
	 * MOMENTUM means Translational Momentum or Angular MOMENTUM
	 * ACCELERATION means Translational Acceleration or Angular Acceleration
	 * VELOCITY means Translational Velocity or Angular Velocity
	 */
	enum ForceType
	{
		FORCE, MOMENTUM, ACCELERATION, VELOCITY
	};

	/**
	 * A struct that defines the material of the RigidBody.
	 */
	struct Material
	{
		float density, staticFriction, kineticFriction, restitution;
	};

	/**
	 * A struct that contains data on the RigidBody's mass and inertia.
	 */
	struct MassData
	{
		float mass, inverseMass, inertia, inverseInertia;
	};

private:
	BodyType mBodyType; ///< The Type of the RigidBody
	MassData mMassData; ///< Data on the RigidBody's mass and inertia.
	Material mMaterial; ///< The material that composes the RigidBody.
	Shape* mShape; ///< The Shape of the RigidBody
	Transform mTransform; ///< The geometrical transformation of the RigidBody.
	Vec2f mVelocity; ///< The translational velocity of the RigidBody.
	Vec2f mForce; ///< The constant force on the RigidBody.
	float mAngularVelocity; ///< The rotational velocity of the RigidBody.
	float mTorque; ///< The Torque of the RigidBody.
	int mLayer; ///< The layer the RigidBody resides on.

	/**
	 * Calculates the data for the MassData strucutre.
	 */
	void calculateMassData();
public:
	/**
	 * Creates a RigidBody at the origin.
	 *
	 * The RigidBody has a Circle shape of radius 1.
	 * The material is set so that it has a density of 1 and no friction.
	 * It's BodyType is set to DYNAMIC
	 * It's put at the origin with no rotation.
	 * It has no velocity or forces acting on it.
	 * It is on layer 0.
	 */
	RigidBody();

	/**
	 * Destroys the RigidBody.
	 *
	 * Deletes the Shape memeber.
	 */
	~RigidBody();

	void step(float dt);

	void applyPush(const Vec2f& push, ForceType forceType = MOMENTUM);
	void applyTwist(float twist, ForceType forceType = MOMENTUM);
	Vec2f getPush(ForceType forceType = MOMENTUM) const;
	float getTwist(ForceType forceType = MOMENTUM) const;
	void setPush(const Vec2f& push, ForceType forceType = MOMENTUM);
	void setTwist(float twist, ForceType forceType = MOMENTUM);

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

#endif /* RIGID_BODY_HPP */
