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
#include <string>

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
	std::string mName;
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
	 * Creates a RigidBody at the origin with a given name.
	 *
	 * The RigidBody has a Circle shape of radius 1.
	 * The material is set so that it has a density of 1 and no friction.
	 * It's BodyType is set to DYNAMIC
	 * It's put at the origin with no rotation.
	 * It has no velocity or forces acting on it.
	 * It is on layer 0.
	 *
	 * @param The RigidBody's std::string name.
	 */
	RigidBody(std::string name);

	/**
	 * Destroys the RigidBody.
	 *
	 * Deletes the Shape memeber.
	 */
	~RigidBody();

	/**
	 * Update the velocity, angular velocity, position, and angle given a
	 * displacement in time.
	 *
	 * @param dt A float that is a displacement in time.
	 */
	void step(float dt);

	/**
	 * Pushes the RigidBody with a certain ForceType
	 *
	 * Applies a "push" to the RigidBody. This push has a dfferent effect
	 * depending on the ForceType parameter. See the description of ForceType
	 * for more detail. By default, MOMENTUM is used.
	 *
	 * @param push	A Vec2f that represents the push.
	 * @param forceType The type of "force" to use.
	 */
	void applyPush(const Vec2f& push, ForceType forceType = MOMENTUM);

	/**
	 * Twists the RigidBody with a certain ForceType
	 *
	 * Applies a "twist" to the RigidBody. This push has a dfferent effect
	 * depending on the ForceType parameter. See the description of ForceType
	 * for more detail. By default, MOMENTUM is used.
	 *
	 * @param twist A float that is the amount of twist.
	 * @param forceType The type of "force" to use.
	 */
	void applyTwist(float twist, ForceType forceType = MOMENTUM);

	/**
	 * Get's the amount of "push" on the RigidBody.
	 *
	 * The "push" that is returned depends on the ForceType put in. See the
	 * description of ForceType for more detail. By default, MOMENTUM is used.
	 *
	 * @param  forceType The type of push to be measured.
	 * @return A Vec2f that is the amount of "push" on the object.
	 */
	Vec2f getPush(ForceType forceType = MOMENTUM) const;

	/**
	 * Get's the amount of "twist" on the RigidBody.
	 *
	 * The "twist" that is returned depends on the ForceType put in. See the
	 * description of ForceType for more detail. By default, MOMENTUM is used.
	 *
	 * @param  forceType The type of twist to be measured.
	 * @return A float that us the amount of "twist" on the object.
	 */
	float getTwist(ForceType forceType = MOMENTUM) const;

	/**
	 * Sets the amount of "push" on the RigidBody.
	 *
	 * Sets the "push" on the RigidBody. This push has a dfferent effect
	 * depending on the ForceType parameter. See the description of ForceType
	 * for more detail. By default, MOMENTUM is used.
	 *
	 * @param push	A Vec2f that represents the push.
	 * @param forceType The type of "force" to use.
	 */
	void setPush(const Vec2f& push, ForceType forceType = MOMENTUM);

	/**
	 * Sets the twist of the RigidBody with a certain ForceType
	 *
	 * Sets the "twist" of the RigidBody. This push has a dfferent effect
	 * depending on the ForceType parameter. See the description of ForceType
	 * for more detail. By default, MOMENTUM is used.
	 *
	 * @param twist A float that is the amount of twist.
	 * @param forceType The type of "force" to use.
	 */
	void setTwist(float twist, ForceType forceType = MOMENTUM);

	/**
	 * Returns the BodyType of this RigidBody.
	 *
	 * See the BodyType documentation for more details.
	 *
	 * @return The BodyType of the RigidBody
	 */
	BodyType getType() const;

	/**
	 * Returns the MassData of this RigidBody.
	 *
	 * @return The MassData of this RigidBody
	 */
	const MassData& getMassData() const;

	/**
	 * Returns the Material of this RigidBody
	 *
	 * @return The Material of this RigidBody
	 */
	const Material& getMaterial() const;

	/**
	 * Returns a reference to this RigidBody's Transform.
	 *
	 * @return A reference to this RigidBody's Transform
	 */
	Transform& getTransform();

	/**
	 * Returns a reference to this RigidBody's Shape.
	 *
	 * @return A reference to this RigidBody's Shape.
	 */
	const Shape& getShape();

	/**
	 * Returns the name of the RigidBody
	 *
	 * @return The std::string name of the RigidBody.
	 */
	const std::string& getName();

	/**
	 * Returns the layer this RigidBody is on.
	 *
	 * @return An int which is the layer this RigidBody is on.
	 */
	int getLayer() const;

	/**
	 * Set's this RigidBody's type.
	 *
	 * See BodyType's documentation for more detial.
	 *
	 * @param type They BodyType this RigidBody wil lbe set to.
	 */
	void setBodyType(BodyType type);

	/**
	 * Set's this RigidBody's material.
	 *
	 * @param material The Material that will compose this RigidBody.
	 */
	void setMaterial(Material material);

	/**
	 * Set's this RigidBody's layer.
	 *
	 * @param layer The int layer of this RigidBody.
	 */
	void setLayer(int layer);

	/**
	 * Set's the name of the RigidBody.
	 *
	 * @param name The new name of the RigidBody
	 */
	void setName(std::string name);

	/**
	 * Set's this RigidBody's Shape to a Circle with a given radius.
	 *
	 * See Circle for more details.
	 *
	 * @param radius The float radius of this new Circle.
	 */
	void setShapeToCircle(float radius);

	/**
	 * Set's this RigidBody's Shape to a Rectangle with given dimensions..
	 *
	 * See Rectangle for more details.
	 *
	 * @param width The float width of this new Rectangle
	 * @param height The float height of this new Rectangle
	 */
	void setShapeToRectangle(float width, float height);

	/**
	 * Set's this RigidBody's Shape to a Polygon with a given vertices.
	 *
	 * See Polygon for more details.
	 *
	 * @param vertices The Vec2f vertices of this new Polygon.
	 */
	void setShapeToPolygon(std::vector<Vec2f> vertices);
};

}

#endif /* RIGID_BODY_HPP */
