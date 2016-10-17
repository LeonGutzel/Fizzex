#ifndef FZX_WORLD_HPP_
#define FZX_WORLD_HPP_

#include "RigidBody.hpp"
#include "Collision.hpp"

#include <string>
#include <vector>
#include <memory>

namespace fzx
{

/**
 * Represents a collection of RigidBodys that can interact with eachother.
 */
class World
{
private:
   std::vector<std::unique_ptr<RigidBody>> mBodies; ///< The RigidBodys in the world.
   std::vector<Collision> mCollisions; ///< The Collision generated last step.
   Vec2f mGravity; ///< The gravity all non-static RigidBodys undergo.
   Vec2f mFluidVelocity; ///< The velocity of the fluid sorrounding the objects.
   unsigned mPositionIterations; ///< The number of position iterations per step.
   unsigned mVelocityIterations; ///< The number of velocity iterations per step.
   float mFluidDrag; ///< The drag of the sorrounding fluid.
   float mDeltaTime; ///< The displacement in time for step.

   /**
    * Sets up Collisions that aren't obciously seperated.
    */
   void broadPhase();

   /**
    * Narrows down the collisions to those that are definetly in contacts.
    */
   void narrowPhase();

   /**
    * Updates the velocity of the RigidBodys.
    */
   void integrateForce();

   /**
    * Updates the position of the RigidBodys.
    */
   void integrateVelocity();
public:

   /**
    * Creates a World given the number of iterations and the delta time.
    *
    * @param positionIteration The number of position iterations per step.
    * @param velocityIterations The number of velocity iterations per step.
    * @param deltaTime The time displacement per step.S
    */
   World(unsigned positionIteration, unsigned velocityIterations, float deltaTime);

   /**
    * Steps the World. Updates positions and velocity while generating and
    * resolving Collisions.
    */
   void step();

   /**
    * Removes all the RigidBodys from the World.
    */
   void clear();

   /**
    * Creates a RigidBody, adds it to the World, and returns a reference.
    *
    * @param  name The name of the RigidBody.
    * @return A reference to the RigidBody added to the World.
    */
   RigidBody& addBody(const std::string& name);

   /**
    * Returns a pointer to a RigidBody with a given name.
    *
    * @param  name The name of the RigidBody to return.
    * @return A constant pointer to the desired RigidBody
    */
   RigidBody* const getBody(const std::string& name);

   /**
    * Returns A reference to a RigidBody with a given index.
    * @param  i The index of the RigidBody.
    * @return A reference to the desired RigidBody.
    */
   RigidBody& getBody(unsigned i);

   /**
    * Removes all RigidBodys with the given name.
    * @param name The name of the objects to remove.
    */
   void removeBody(const std::string& name);

   /**
    * Removes the RigidBody with a given index.
    * @param i The index of the RigidBody to remove.
    */
   void removeBody(unsigned i);

   /**
    * Returns the number of RigidBodys in the World.
    *
    * @return The number of RigidBody in the World.
    */
   unsigned getNumberOfBodies() const;

   /**
    * Returns a constant reference to a collision given an index.
    * @param i The index of the collision.
    * @return a constant reference to the desired collision.
    */
   const Collision& getCollision(unsigned i) const;

   /**
    * Returns a constant reference to a collision given a name.
    *
    * @param name The name of an involved RigidBody.
    * @return a constant reference to the desired collision.
    */
   Collision const * const getCollision(const std::string& name) const;

   /**
    * Returns a constant reference to a collision given a RigidBody.
    *
    * @param body A reference to the RigidBody desired.
    * @return a constant reference to the desired collision.
    */
   Collision const * const getCollision(const RigidBody& body) const;

   /**
    * The number of Collisions generated last step.
    *
    * @return The number of Collisions generated last step.
    */
   unsigned getNumberOfCollisions() const;

   /**
    * Returns the gravity of the world.
    *
    * @return The gravity of the world.
    */
   const Vec2f& getGravity() const;

   /**
    * Returns the fluid velocity of the world.
    *
    * @return The fluid velocity of the world.
    */
   const Vec2f& getFluidVelocity() const;

   /**
    * Returns the fluid drag of the world.
    *
    * @return The fluid drag of the world.
    */
   float getFluidDrag() const;

   /**
    * Returns the time displacement done each step.
    *
    * @return The time displacement done each step.
    */
   float getDeltaTime() const;

   /**
    * Set's the World's gravity.
    *
    * @param gravity The new gravity of the world.
    */
   void setGravity(const Vec2f& gravity);

   /**
    * Set's the World's fluid velocity.
    *
    * @param velocity The new fluid velocity of the world.
    */
   void setFluidVelocity(const Vec2f& velocity);

   /**
    * Set's the World's fluid drag.
    *
    * @param drag The new drag constant of the world.
    */
   void setFluidDrag(float drag);

   /**
    * Set's the World's time displacement.
    *
    * @param detlaTime The time displacement done each step.
    */
   void setDeltaTime(float detlaTime);
};

}

#endif /*FZX_WORLD_HPP_*/
