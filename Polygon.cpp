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
   for (unsigned i = 2; i < mVertices.size(); i++)
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
   for (Vec2f vector : mVertices) vector -= sum;
}

Polygon::Polygon()
{
   mVertices.push_back(Vec2f(-1, -1));
   mVertices.push_back(Vec2f(2, -1));
   mVertices.push_back(Vec2f(-1, 2));
}

float Polygon::getRadius() const
{
   float largestSquareMagnitude = 0;
   for (Vec2f vector : mVertices)
      if (largestSquareMagnitude < vector.getMagnitudeSquared())
         largestSquareMagnitude = vector.getMagnitudeSquared();
   return std::sqrt(largestSquareMagnitude);
}

float Polygon::getArea() const
{
   float area = 0;

   for (unsigned i = 1; i < mVertices.size(); i++)
   {
      area += std::abs(mVertices[i] % mVertices[i-1]);
   }
   area += std::abs(mVertices[0] % mVertices[mVertices.size() - 1]);

   return area / 2;
}

Vec2f Polygon::getVertix(unsigned int index) const
{
   return mVertices[index];
}

unsigned int Polygon::getNumberOfVertices() const
{
   return mVertices.size();
}

float Polygon::getInertiaPerMass() const
{
   float moment = 0;

   for (unsigned i = 1; i <= mVertices.size(); i++)
   {
      Vec2f vertexA, vertexB;
      if (i == mVertices.size())
      {
         vertexA = mVertices[0];
         vertexB = mVertices[mVertices.size() - 1];
      }
      else
      {
         vertexA = mVertices[i];
         vertexB = mVertices[i-1];
      }
      float squareDistance = ((vertexA + vertexB) / 3).getMagnitudeSquared();
      float area = (vertexA % vertexB) / 2;
      float sideA = vertexA.getMagnitude();
      float sideB = vertexB.getMagnitude();
      float height = 2 * area / sideB;

      float partialMoment = 0;
      partialMoment += sideB * sideB * sideB * height;
      partialMoment -= sideB * sideB * height * sideA;
      partialMoment += sideB * height * sideA * sideA;
      partialMoment += sideB * height * height * height;
      partialMoment /= 36;
      partialMoment += squareDistance;

      moment += std::abs(partialMoment);
   }

   return moment;
}

Shape::BoundingBox Polygon::getBoundingBox(const Transform& transform) const
{
   BoundingBox boundry;
   for (Vec2f vertex : mVertices)
   {
      vertex = transform.apply(vertex);
      if (vertex.x > boundry.upperRight.x) boundry.upperRight.x = vertex.x;
      if (vertex.y > boundry.upperRight.y) boundry.upperRight.y = vertex.y;
      if (vertex.x < boundry.lowerLeft.x) boundry.lowerLeft.x = vertex.x;
      if (vertex.y < boundry.lowerLeft.y) boundry.lowerLeft.y = vertex.y;
   }
   return boundry;
}

Vec2f Polygon::getSupport(const Vec2f& direction, const Transform& transform) const
{
   Vec2f support = transform.apply(mVertices[0]);
   float largestDirectionMeasure = support * direction;

   for (Vec2f vertex : mVertices) {
      vertex = transform.apply(vertex);
      float directionMeasure = vertex * direction;
      directionMeasure /= vertex.getMagnitude() * direction.getMagnitude();

      if (largestDirectionMeasure < directionMeasure)
      {
         largestDirectionMeasure = directionMeasure;
         support = vertex;
      }
   }

   return support;
}

Shape::ShapeType Polygon::getType() const
{
   return Shape::POLYGON;
}

}
