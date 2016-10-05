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
}
Body::~Body()
{
   delete mShape;
}

void Body::step(float dt)
{
   
}

}
