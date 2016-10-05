#include "Body.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Polygon.hpp"

namespace fzx
{

Body::Body()
{
   mBodyType = DYNAMIC;
   mMaterial = Material{1, 0, 0, 1};
   mShape = new Circle(1);
   mMassData = MassData{3.1415926f, 1/3.1415926f, };
   mAngularVelocity = 0;
   mTorque = 0;
   mLayer = 0;
   calculateMassData();
}
Body::~Body()
{
   delete mShape;
}

void Body::calculateMassData()
{
   mMassData.mass = mShape->getArea() * mMaterial.density;
   mMassData.inertia = mShape->getInertiaPerMass() * mMassData.mass;

   if (mMassData.mass == 0) mMassData.inverseMass = 0;
   else mMassData.inverseMass = 1 / mMassData.mass;
   if(mMassData.inertia == 0) mMassData.inverseInertia = 0;
   else mMassData.inverseInertia = 1 / mMassData.inertia;
}

void Body::step(float dt)
{
   mVelocity += mForce * (mMassData.inverseMass * dt);
   mTransform.translate(mVelocity * dt);
   mAngularVelocity += mTorque * (mMassData.inverseInertia * dt);
   mTransform.rotate(mAngularVelocity * dt);
}

void Body::applyPush(const Vec2f& push, Body::ForceType forceType)
{
   if (forceType == Body::VELOCITY) mVelocity += push;
   if (forceType == Body::ACCELERATION) mForce += push * mMassData.mass;
   if (forceType == Body::IMPULSE) mVelocity += push * mMassData.inverseMass;
   if (forceType == Body::FORCE) mForce += push;
}

void Body::applyTwist(float twist, Body::ForceType forceType)
{
   if (forceType == Body::VELOCITY) mAngularVelocity += twist;
   if (forceType == Body::ACCELERATION) mTorque += twist * mMassData.inertia;
   if (forceType == Body::IMPULSE) mAngularVelocity += twist * mMassData.inverseInertia;
   if (forceType == Body::FORCE) mTorque += twist;
}

Vec2f Body::getPush(ForceType forceType) const
{
   if (forceType == Body::VELOCITY) return mVelocity;
   if (forceType == Body::ACCELERATION) return mForce * mMassData.inverseMass;
   if (forceType == Body::IMPULSE) return mVelocity * mMassData.mass;
   return mForce;
}

float Body::getTwist(ForceType forceType) const
{
   if (forceType == Body::VELOCITY) return mAngularVelocity;
   if (forceType == Body::ACCELERATION) return mTorque * mMassData.inverseInertia;
   if (forceType == Body::IMPULSE) return mAngularVelocity * mMassData.inertia;
   return mTorque;
}

void Body::setPush(const Vec2f& push, ForceType forceType)
{
   if (forceType == Body::VELOCITY) mVelocity = push;
   if (forceType == Body::ACCELERATION) mForce = push * mMassData.mass;
   if (forceType == Body::IMPULSE) mVelocity = push * mMassData.inverseMass;
   if (forceType == Body::FORCE) mForce = push;
}

void Body::setTwist(float twist, ForceType forceType)
{
   if (forceType == Body::VELOCITY) mAngularVelocity = twist;
   if (forceType == Body::ACCELERATION) mTorque = twist * mMassData.inertia;
   if (forceType == Body::IMPULSE) mAngularVelocity = twist * mMassData.inverseInertia;
   if (forceType == Body::FORCE) mTorque = twist;
}

Body::BodyType Body::getType() const
{
   return mBodyType;
}

Body::MassData Body::getMassData() const
{
   return mMassData;
}

Body::Material Body::getMaterial() const
{
   return mMaterial;
}

Transform& Body::getTransform()
{
   return mTransform;
}

Shape& Body::getShape()
{
   return *mShape;
}

int Body::getLayer() const
{
   return mLayer;
}

void Body::setBodyType(BodyType type)
{
   mBodyType = type;
}

void Body::setMaterial(Material material)
{
   mMaterial = material;
   calculateMassData();
}

void Body::setLayer(int layer)
{
   mLayer = layer;
}

void Body::setShapeToCircle(float radius)
{
   delete mShape;
   mShape = new Circle(radius);
   calculateMassData();
}

void Body::setShapeToRectangle(float width, float height)
{
   delete mShape;
   mShape = new Rectangle(width, height);
   calculateMassData();
}

void Body::setShapeToPolygon(std::vector<Vec2f> vertices)
{
   delete mShape;
   mShape = new Polygon(vertices);
   calculateMassData();
}

}
