/*
 * Body.hpp
 *
 *  Created on: Oct 13, 2014
 *      Author: Leon
 */

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

	void applyPush(Vec2f& push, ForceType forceType = IMPULSE);
	void applyTwist(float twist, ForceType forceType = IMPULSE);
	Vec2f getPush(Vec2f& push, ForceType forceType = IMPULSE);
	float getTwist(float twist, ForceType forceType = IMPULSE);
	void setPush(Vec2f& push, ForceType forceType = IMPULSE);
	void setTwist(float twist, ForceType forceType = IMPULSE);

	BodyType getType();
	MassData getMassData();
	Material getMaterial();
	Transform& getTransform();
	int getLayer();

	void setBodyType(BodyType type);
	void setMaterial(Material material);
	void setLayer(int layer);

	void setShapeToCircle(float radius);
	void setShapeToRectangle(float width, float height);
	void setShapeToPolygon(std::vector<Vec2f> vertices);
};

}

#endif /* BODY_HPP_ */
