#include "Body.hpp"

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
   mMassData.inertia = mShape->getMomentPerMass() * mMassData.mass;

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

void Body::applyPush(Vec2f& push, Body::ForceType forceType)
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

}
