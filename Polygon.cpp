#include "Polygon.hpp"
#include <cmath>

namespace fzx
{

Polygon::Polygon(std::vector<Vec2f> vertices)
{
   mVertices = vertices;

   if(mVertices.size() < 3) mVertices.push_back(Vec2f(-1, -1));
   if(mVertices.size() < 3) mVertices.push_back(Vec2f(2, -1));
   if(mVertices.size() < 3) mVertices.push_back(Vec2f(-1, 2));

   float lastCrossProduct = 0;
   for (int i = 2; i < mVertices.size(); i++)
   {
      Vec2f currentSide = mVertices[i] - mVertices[i-1];
      Vec2f lastSide = mVertices[i-1] - mVertices[i-2];
      float crossProduct = currentSide % lastSide;

      if (i == 2) lastCrossProduct = crossProduct;
      if (crossProduct * lastCrossProduct < 0)
      {
         mVertices.erase(mVertices.begin() + i);
         i--;
      }
   }

   Vec2f sum = Vec2f(0, 0);
   for (Vec2f vector : mVertices) sum += vector;
   sum /= mVertices.size();
   for (Vec2f vector : mVertices) sum -= sum;
}

Polygon::Polygon()
{
   mVertices.push_back(Vec2f(-1, -1));
   mVertices.push_back(Vec2f(2, -1));
   mVertices.push_back(Vec2f(-1, 2));
}

Vec2f Polygon::getBoundingBox()
{
   float maxWidth = 0;
   float maxHeight = 0;

   for (Vec2f vector : mVertices)
   {
      if (std::abs(vector.x) > maxWidth) maxWidth = vector.x;
      if (std::abs(vector.y) > maxHeight) maxHeight = vector.y;
   }

   return Vec2f(maxWidth * 2, maxHeight * 2);
}
float Polygon::getRadius();
float Polygon::getArea();
Vec2f Polygon::getSupport(Vec2f& direction, Transform& transform);
Shape::ShapeType Polygon::getType();
}
