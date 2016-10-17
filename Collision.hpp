#ifndef FZX_COLLISION_HPP_
#define FZX_COLLISION_HPP_

#include "RigidBody.hpp"
#include "Rectangle.hpp"
#include "Polygon.hpp"

namespace fzx
{

/**
 * A representation of a collision between two RigidBodys.
 */
class Collision
{
friend World;
public:
/**
 * The data of a point of contact in the Collision.
 */
struct ContactData
{
   Vec2f normal; ///< The normal vector to the flat surface of the contact.
   Vec2f tangent; ///< The tangent vector to the flat surface of the contact.
   Vec2f location; ///< The location of the contact in real space.
   Vec2f velocity; ///< The relative velocity of the point of contact.
   Vec2f leverA; ///< A vector from the center of RigidBody A to the contact.
   Vec2f leverB; ///< A vector from the center of RigidBody B to the contact.
   float normalImpulse; ///< The impulse exchange from the contact in the normal.
   float tangentImpulse; ///< The impulse exchange from the contact in the tangent.
   float penetration; ///< The amount the object penetrated in this contact.
};
private:
   RigidBody* mBodyA; ///< A pointer to RigidBody A
   RigidBody* mBodyB; ///< A pointer to RigidBody B
   std::vector<ContactData> mContacts; ///< The contact locations of this collision.
   float mMixedStaticFriction; ///< The static friction between the two surfaces.
   float mMixedKineticFriction; ///< The kinetic friction between the two surfaces.
   float mMixedRestitution; ///< The restituion between the two surfaces.

   /**
    * Solves the contacts between two Circles
    */
   void solveCircleVsCircle();
   /**
    * Solves the contacts between a Circle and a Rectangle
    */
   void solveCircleVsRectangle();
   /**
    * Solves the contacts between a Circle and a Polygon
    */
   void solveCircleVsPolygon();
   /**
    * Solves the contacts between two Rectangles
    */
   void solveRectangleVsRectangle();
   /**
    * Solves the contacts between a Rectangle and a Polygon
    */
   void solveRectangleVsPolygon();
   /**
    * Solves the contacts between two Polygons
    */
   void solvePolygonVsPolygon();
   /**
    * Solves the impulses for the contacts.
    */
   void solveImpulse();
public:
   /**
    * Set's up the Collision between two RigidBody.
    *
    * This doesn't automatically solve the contacts or impulses.
    */
   Collision(RigidBody* bodyA, RigidBody* bodyB);

   /**
    * Checks whether the BoundingBoxes of two RigidBodys intersect.
    *
    * @param  bodyA The first RigidBody.
    * @param  bodyB The second RigidBody.
    * @return Whether or not the BoundingBoxes intersect.
    */
   static bool checkBoundingBoxes(RigidBody* bodyA, RigidBody* bodyB);

   /**
    * Solves for the contacts of the Collision.
    *
    * This can be a very expensive operation.
    */
   void solve();

   /**
    * Corrects the penetration between two RigidBodys due to the Collision
    */
   void correctPenetration();

   /**
    * Applies the appropriate impulses to the two RigidBodys.
    */
   void applyImpulse();

   /**
    * Returns a reference to RigidBody A
    * @return A reference to RigidBody A
    */
   RigidBody& getBodyA();

   /**
    * Returns a reference to RigidBody B
    * @return A reference to RigidBody B
    */
   RigidBody& getBodyB();

   /**
    * Returns the static friction between the two RigidBodys
    * @return The combined static friction
    */
   float getMixedStaticFriction() const;

   /**
    * Returns the kinetic friction between the two RigidBodys
    * @return The combined kinetic friction
    */
   float getMixedKineticFriction() const;

   /**
    * Returns the restituion between the two RigidBodys
    * @return The combined restituion
    */
   float getMixedRestitution() const;

   /**
    * Returns a contacts given an index
    * @param  i An index of a contact.
    * @return A constanct referenct to the contact.
    */
   const ContactData& getContactData(unsigned i) const;

   /**
    * The number of contact points in the Collision.
    * @return The number of contact points.
    */
   unsigned getNumberOfContacts() const;
};

}

#endif /*FZX_COLLISION_HPP_*/
