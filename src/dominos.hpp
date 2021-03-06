/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Sharat Chandran
 */

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

namespace cs251
{
  //! This is the class that sets up the Box2D simulation world
  //! Notice the public inheritance 
  /**
   * Here we inherit dominos_t class from the base_sim_t class
   * This inheritence helps to inherit the variables and member
   * functions which are the oart of base_sim_t class
   * 
   * These member function and variables will help in the runnig of the simulatiom
   * */
  class dominos_t : public base_sim_t
  {
  public:
    
    
    dominos_t();
    
    static base_sim_t* create()
    {
      return new dominos_t;
    }
    void  CreateLeg(float32 s, const b2Vec2& wheelAnchor);
  };
}
  
#endif
