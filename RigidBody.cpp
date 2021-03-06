#include "RigidBody.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Polygon.hpp"
#include "Settings.hpp"

namespace fzx
{

RigidBody::RigidBody(std::string name)
{
   mName = name;
   mBodyType = DYNAMIC;
   mMaterial = Material{1, 0, 0, 1};
   mShape = new Circle(1);
   mAngularVelocity = 0;
   mTorque = 0;
   mLayer = 0;
   mIsSleeping= false;
   calculateMassData();
}
RigidBody::~RigidBody()
{
   delete mShape;
}

void RigidBody::calculateMassData()
{
   mMassData.mass = mShape->getArea() * mMaterial.density;
   mMassData.inertia = mShape->getInertiaPerMass() * mMassData.mass;

   if (mMassData.mass == 0) mMassData.inverseMass = 0;
   else mMassData.inverseMass = 1 / mMassData.mass;
   if(mMassData.inertia == 0) mMassData.inverseInertia = 0;
   else mMassData.inverseInertia = 1 / mMassData.inertia;
}

bool RigidBody::canSleep()
{
   return (mVelocity * mVelocity < MINIMUM_VELOCITY_FOR_AWAKING * MINIMUM_VELOCITY_FOR_AWAKING)
            && (std::abs(mAngularVelocity) < MINIMUM_ANGULAR_VELOCITY_FOR_AWAKING);
}

void RigidBody::applyPush(const Vec2f& push, RigidBody::ForceType forceType)
{
   if (mBodyType == STATIC) return;
   if (forceType == RigidBody::VELOCITY) mVelocity += push;
   if (forceType == RigidBody::ACCELERATION) mForce += push * mMassData.mass;
   if (forceType == RigidBody::MOMENTUM) mVelocity += push * mMassData.inverseMass;
   if (forceType == RigidBody::FORCE) mForce += push;
   if (mIsSleeping && canSleep()) mVelocity = Vec2f(0, 0);
   if (!canSleep()) mIsSleeping = false;
}

void RigidBody::applyTwist(float twist, RigidBody::ForceType forceType)
{
   if (mBodyType == STATIC) return;
   if (forceType == RigidBody::VELOCITY) mAngularVelocity += twist;
   if (forceType == RigidBody::ACCELERATION) mTorque += twist * mMassData.inertia;
   if (forceType == RigidBody::MOMENTUM) mAngularVelocity += twist * mMassData.inverseInertia;
   if (forceType == RigidBody::FORCE) mTorque += twist;
   if (mIsSleeping && canSleep()) mAngularVelocity = 0;
   if (!canSleep()) mIsSleeping = false;
}

void RigidBody::stop()
{
   mVelocity = Vec2f(0, 0);
   mAngularVelocity = 0;
   mForce = Vec2f(0, 0);
   mIsSleeping = true;
}

Vec2f RigidBody::getPush(ForceType forceType) const
{
   if (forceType == RigidBody::VELOCITY) return mVelocity;
   if (forceType == RigidBody::ACCELERATION) return mForce * mMassData.inverseMass;
   if (forceType == RigidBody::MOMENTUM) return mVelocity * mMassData.mass;
   return mForce;
}

float RigidBody::getTwist(ForceType forceType) const
{
   if (forceType == RigidBody::VELOCITY) return mAngularVelocity;
   if (forceType == RigidBody::ACCELERATION) return mTorque * mMassData.inverseInertia;
   if (forceType == RigidBody::MOMENTUM) return mAngularVelocity * mMassData.inertia;
   return mTorque;
}

void RigidBody::setPush(const Vec2f& push, ForceType forceType)
{
   if (mBodyType == STATIC) return;
   if (forceType == RigidBody::VELOCITY) mVelocity = push;
   if (forceType == RigidBody::ACCELERATION) mForce = push * mMassData.mass;
   if (forceType == RigidBody::MOMENTUM) mVelocity = push * mMassData.inverseMass;
   if (forceType == RigidBody::FORCE) mForce = push;
   mIsSleeping = false;
}

void RigidBody::setTwist(float twist, ForceType forceType)
{
   if (mBodyType == STATIC) return;
   if (forceType == RigidBody::VELOCITY) mAngularVelocity = twist;
   if (forceType == RigidBody::ACCELERATION) mTorque = twist * mMassData.inertia;
   if (forceType == RigidBody::MOMENTUM) mAngularVelocity = twist * mMassData.inverseInertia;
   if (forceType == RigidBody::FORCE) mTorque = twist;
   mIsSleeping = false;
}

RigidBody::BodyType RigidBody::getType() const
{
   return mBodyType;
}

const RigidBody::MassData& RigidBody::getMassData() const
{
   return mMassData;
}

const RigidBody::Material& RigidBody::getMaterial() const
{
   return mMaterial;
}

Transform& RigidBody::getTransform()
{
   return mTransform;
}

const Shape& RigidBody::getShape()
{
   return *mShape;
}

const std::string& RigidBody::getName()
{
   return mName;
}

int RigidBody::getLayer() const
{
   return mLayer;
}

bool RigidBody::isSleeping() const
{
   return mIsSleeping;
}

void RigidBody::setBodyType(BodyType type)
{
   mBodyType = type;
   if (mBodyType == STATIC) stop();
}

void RigidBody::setMaterial(Material material)
{
   mMaterial = material;
   calculateMassData();
}

void RigidBody::setName(std::string name)
{
   mName = name;
}

void RigidBody::setLayer(int layer)
{
   mLayer = layer;
}

void RigidBody::setSleeping(bool isSleeping)
{
   mIsSleeping = isSleeping;
}

void RigidBody::setShapeToCircle(float radius)
{
   delete mShape;
   mShape = new Circle(radius);
   calculateMassData();
}

void RigidBody::setShapeToRectangle(float width, float height)
{
   delete mShape;
   mShape = new Rectangle(width, height);
   calculateMassData();
}

void RigidBody::setShapeToPolygon(std::vector<Vec2f> vertices)
{
   delete mShape;
   mShape = new Polygon(vertices);
   calculateMassData();
}

}
