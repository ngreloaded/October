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

//! These are user defined include files
//! Included in double quotes - the path to find these has to be given at compile time
#include "cs251_base.hpp"
#include "render.hpp"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "GL/freeglut.h"
#endif

#include <cstring>
#include <iostream>
using namespace std;

#include "dominos.hpp"
//! The namespace protects the global variables and other names from
//! clashes in scope. Read about the use of named and unnamed
//! namespaces in C++ Figure out where all the datatypes used below
//! are defined
namespace cs251
{
    /**  This is the constructor
     * This is the documentation block for the constructor.
     */
    
    dominos_t::dominos_t()
    {
        b2Body* b1; //!b1 is b2Body type variable representing the body of ground\n
        {
            
            b2EdgeShape ground_shape; // this is for shape of ground
            ground_shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
            b2BodyDef ground_body_def; // body definition of ground
            b1 = m_world->CreateBody(&ground_body_def);
            b1->CreateFixture(&ground_shape, 0.0f);
        }
        
        {
            
            b2BodyDef *pulley_system_common_body_def = new b2BodyDef;            pulley_system_common_body_def->type = b2_dynamicBody; //! this is the common b2BodyDef variable used for various elements of pulley system.
            
            float y=15, b=2, a=2;
            
			b2PolygonShape pulley_shape; //pulley_shape is pulley shape variable used for two square boxes\n
			pulley_shape.SetAsBox(a, b);
            b2FixtureDef *pulley_fixture_def = new b2FixtureDef; // this is used to define the fixture for pulley shape variable used for two square boxes
            pulley_fixture_def->density = 20.0f;
            
			pulley_system_common_body_def->position.Set(70.0f, y);
			b2Body* pulley_body_1 = m_world->CreateBody(pulley_system_common_body_def);
			pulley_body_1->CreateFixture(&pulley_shape, 0.5f); // body of square box 1
            
			pulley_system_common_body_def->position.Set(80.0f, y);
			b2Body* pulley_body_2 = m_world->CreateBody(pulley_system_common_body_def);
			pulley_body_2->CreateFixture(&pulley_shape, 0.5f); // body of square box 2
            
			b2PulleyJointDef pulley_joint; //! pulley_joint is b2PulleyJointDef type variable used as definition of joint of pulley
			b2Vec2 anchor1(70.0f, y + b);
			b2Vec2 anchor2(80.0f, y + b);
			b2Vec2 groundAnchor1(70.0f, y +30);
			b2Vec2 groundAnchor2(80.0f, y +30);
			pulley_joint.Initialize(pulley_body_1, pulley_body_2, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.5f);
            
			m_world->CreateJoint(&pulley_joint);
            
        }
        
        
        
        /** BLOCK 9 :  BALL ON THE T SHAPE PLATFORM */
        {
            
            b2Body* sphere_body_common; //! sphere_body_common is b2Body shape variable used for all the four spheres
            b2CircleShape circle; // for the two smallest ball
            circle.m_radius = 1.0;
            b2CircleShape circle1; // for the medium sized ball
            circle1.m_radius = 1.5;
            b2CircleShape circle2; // for the largest ball
            circle2.m_radius = 2.0;
 
            
            b2FixtureDef ballfd; // for the two smallest ball
            ballfd.shape = &circle;
            ballfd.density = 10.64f;
            ballfd.friction = 0.2f;
            ballfd.restitution = 0.0f;
            b2FixtureDef ballfd1; // for the medium sized ball circle
            ballfd1.shape = &circle1;
            ballfd1.density = 10.0f;
            ballfd1.friction = 0.2f;
            ballfd1.restitution = 0.0f;
            b2FixtureDef ballfd2; // for the largest ball
            ballfd2.shape = &circle2;
            ballfd2.density = 10.0f;
            ballfd2.friction = 0.2f;
            ballfd2.restitution = 0.0f;
           
            b2BodyDef ball_common_body_def; //!ball_common_body_def is b2BodyDef type common body definition for all four balls
            ball_common_body_def.type = b2_dynamicBody;
            
            ball_common_body_def.position.Set(-42.f, 41.4f);
            sphere_body_common = m_world->CreateBody(&ball_common_body_def);
            sphere_body_common->CreateFixture(&ballfd);
            
            ball_common_body_def.position.Set(-40.f, 41.4f);
            sphere_body_common = m_world->CreateBody(&ball_common_body_def);
            sphere_body_common->CreateFixture(&ballfd);
            
            ball_common_body_def.position.Set(-37.5f, 41.9f);
            sphere_body_common = m_world->CreateBody(&ball_common_body_def);
            sphere_body_common->CreateFixture(&ballfd1);
            
            ball_common_body_def.position.Set(-33.5f, 42.9f);
            sphere_body_common = m_world->CreateBody(&ball_common_body_def);
            sphere_body_common->CreateFixture(&ballfd2);
            
        }
        {
            b2BodyDef killer_body_def; //! killer_body_def is b2BodyDef type variable for killer's body definition
            killer_body_def.position.Set(-50.f, 17.5f);
            b2Body* killer_body = m_world->CreateBody(&killer_body_def); // b2Body* type variable for killer's body
            
            b2PolygonShape killer_mid_body_shape;  // b2PolygonShape type variable for killer's mid_body shape
            killer_mid_body_shape.SetAsBox(2.f, 2.5f, b2Vec2(0,-3.5),0);
            b2FixtureDef *killer_mid_body_fixture = new b2FixtureDef;  // b2FixtureDef * type variable for killer's mid_body fixture
            killer_mid_body_fixture->shape = &killer_mid_body_shape;
            
            b2CircleShape killer_face_shape;  // b2CircleShape type variable for killer's face shape
            killer_face_shape.m_radius = 1.0;
            b2FixtureDef *killer_face_fixture = new b2FixtureDef;  // b2FixtureDef * type variable for killer's face fixture
            killer_face_fixture->shape = &killer_face_shape;
                        
            b2PolygonShape killer_left_leg_shape;  // b2PolygonShape type variable for killer's left leg shape
            killer_left_leg_shape.SetAsBox(0.3f, 2.f, b2Vec2(-1.5,-7),0);
            b2FixtureDef *killer_left_leg_fixture = new b2FixtureDef;  // b2FixtureDef * type variable for killer's left_leg fixture
            killer_left_leg_fixture->shape = &killer_left_leg_shape;
            
            b2PolygonShape killer_right_leg_shape;  // b2PolygonShape type variable for killer's right_leg shape
            killer_right_leg_shape.SetAsBox(0.3f, 2.f, b2Vec2(1.5,-7),0);
            b2FixtureDef *killer_right_leg_fixture = new b2FixtureDef;  // b2FixtureDef type variable for killer's right_leg fixture
            killer_right_leg_fixture->shape = &killer_right_leg_shape;
            
            b2PolygonShape killer_right_hand_shape; // b2PolygonShape type variable for killer's right_hand shape
            killer_right_hand_shape.SetAsBox(0.3f, 2.f, b2Vec2(2.5,-3),0.3);
            b2FixtureDef *killer_right_hand_fixture = new b2FixtureDef; // b2FixtureDef type variable for killer's right_hand fixture
            killer_right_hand_fixture->shape = &killer_right_hand_shape;
            
            b2PolygonShape killer_left_hand_shape; //b2PolygonShape type variable for killer's left_hand shape
            killer_left_hand_shape.SetAsBox(0.3f, 2.f, b2Vec2(-3.8,-1),-1.6);
            b2FixtureDef *killer_left_hand_fixture = new b2FixtureDef; // type variable for
            killer_left_hand_fixture->shape = &killer_left_hand_shape;
            
            killer_body->CreateFixture(killer_mid_body_fixture);
            killer_body->CreateFixture(killer_face_fixture);
            killer_body->CreateFixture(killer_left_leg_fixture);
            killer_body->CreateFixture(killer_right_leg_fixture);
            killer_body->CreateFixture(killer_right_hand_fixture);
            killer_body->CreateFixture(killer_left_hand_fixture);
        }
        {
            float x=0;
            b2BodyDef human_body_def; //!human_body_def is b2BodyDef type variable for human's body definition
            human_body_def.position.Set(-80.f, 17.5f);
            b2Body* human_body = m_world->CreateBody(&human_body_def); //b2Body* type variable for human's body
            
            b2PolygonShape human_mid_body_shape; // b2PolygonShape type variable for human's face
            human_mid_body_shape.SetAsBox(1.6f, 2.5f, b2Vec2(0-x,-3.5),0);
            b2FixtureDef *human_mid_body_fixture = new b2FixtureDef; // b2FixtureDef type variable for human's mid_body fixture
            human_mid_body_fixture->shape = &human_mid_body_shape;
            
            b2CircleShape human_face_shape; // b2CircleShape type variable for human's face shape
            human_face_shape.m_radius = 1.0;
            b2FixtureDef *human_face_fixture = new b2FixtureDef; // b2FixtureDef type variable for human's face fixture
            human_face_fixture->shape = &human_face_shape;
            
            b2PolygonShape human_left_leg_shape; // b2PolygonShape type variable for human's left leg shape
            human_left_leg_shape.SetAsBox(0.3f, 2.f, b2Vec2(-1.3-x,-7),0);
            b2FixtureDef *human_left_leg_fixture = new b2FixtureDef; // type variable for human's left_leg fixture
            human_left_leg_fixture->shape = &human_left_leg_shape;
            
            b2PolygonShape human_right_leg_shape; // b2PolygonShape type variable for human's right_leg shape
            human_right_leg_shape.SetAsBox(0.3f, 2.f, b2Vec2(1.3-x,-7),0);
            b2FixtureDef *human_right_leg_fixture = new b2FixtureDef; // type variable for human's right_leg fixture
            human_right_leg_fixture->shape = &human_right_leg_shape;
            
            b2PolygonShape human_right_hand_shape; // b2PolygonShape type variable for human's right_hand shape
            human_right_hand_shape.SetAsBox(0.3f, 2.2f, b2Vec2(2-x,1.2),3);
            b2FixtureDef *human_right_hand_fixture = new b2FixtureDef; // type variable for  human's right_hand fixture
            human_right_hand_fixture->shape = &human_right_hand_shape;
            
            b2PolygonShape human_left_hand_shape; // b2PolygonShape type variable for human's left_hand shape
            human_left_hand_shape.SetAsBox(0.3f, 2.2f, b2Vec2(-2-x,1.2),-3);
            b2FixtureDef *human_left_hand_fixture = new b2FixtureDef; // b2PolygonShape type variable for human's left_hand shape
            human_left_hand_fixture->shape = &human_left_hand_shape;
            
            human_body->CreateFixture(human_mid_body_fixture);
            human_body->CreateFixture(human_face_fixture);
            human_body->CreateFixture(human_left_leg_fixture);
            human_body->CreateFixture(human_right_leg_fixture);
            human_body->CreateFixture(human_right_hand_fixture);
            human_body->CreateFixture(human_left_hand_fixture);
        }
        {
            b2Body* hydrogen_sphere_body; //!hydrogen_sphere_body is b2Body* type variable for hydrogen sphere body
            b2CircleShape hydrogen_sphere_shape;  //b2CircleShape type variable for hydrogen sphere shape
            hydrogen_sphere_shape.m_radius = 1.0;
            
            b2FixtureDef hydrogen_sphere_fixture_def; //b2FixtureDef type variable for hydrogen sphere fixture definition
            hydrogen_sphere_fixture_def.shape = &hydrogen_sphere_shape;
            hydrogen_sphere_fixture_def.density = 15.0f;
            hydrogen_sphere_fixture_def.friction = 0.2f;
            hydrogen_sphere_fixture_def.restitution = 0.0f;
            b2BodyDef hydrogen_sphere_body_def; // b2BodyDef type variable for hydrogen sphere body definition
            hydrogen_sphere_body_def.type = b2_dynamicBody;
            hydrogen_sphere_body_def.position.Set(-74.f, 2.f);
            hydrogen_sphere_body = m_world->CreateBody(&hydrogen_sphere_body_def);
            hydrogen_sphere_body->CreateFixture(&hydrogen_sphere_fixture_def);
            hydrogen_sphere_body->SetGravityScale(-1);
            
            hydrogen_sphere_body_def.position.Set(-73.f, 2.f);
            hydrogen_sphere_body = m_world->CreateBody(&hydrogen_sphere_body_def);
            hydrogen_sphere_body->CreateFixture(&hydrogen_sphere_fixture_def);
            hydrogen_sphere_body->SetGravityScale(-1);
            
        }
        {
            b2BodyDef hinge_body_def; //!hinge_body_def is b2BodyDef type variable for hinge body definition
            hinge_body_def.position.Set(-80.f, 4.f);
            b2Body* hinge_body = m_world->CreateBody(&hinge_body_def);
            
            b2PolygonShape shape1; // b2PolygonShape type variable for body1
            shape1.SetAsBox(6.f, 4.f, b2Vec2(0,0),0);
            b2FixtureDef *fd1 = new b2FixtureDef;
            fd1->shape = &shape1;
            
            b2PolygonShape shape2; // b2PolygonShape type variable for body2
            shape2.SetAsBox(12.f, 4.f, b2Vec2(25,0),0);
            b2FixtureDef *fd2 = new b2FixtureDef;
            fd2->shape = &shape2;
            
            b2PolygonShape shape3; // b2PolygonShape type variable for body3
            shape3.SetAsBox(0.6f, 16.f, b2Vec2(36,20),0);
            b2FixtureDef *fd3 = new b2FixtureDef;
            fd3->shape = &shape3;

            
            
            b2PolygonShape shape10; //! shape10 is b2PolygonShape type variable for body 10. body10 = horizontal bar
            shape10.SetAsBox(32.f, 0.4f, b2Vec2(-20.f,0.f),0);
            
            b2PolygonShape shape11; //!shape11 b2PolygonShape type variable for body11. body11 = verticla bar.
            shape11.SetAsBox(0.2f, 8.0f , b2Vec2(-50.f,1.f),0);
			
            b2BodyDef bd10; // b2BodyDef type variable for body10
            bd10.position.Set(-44.0f, 40.0f);
            bd10.type = b2_dynamicBody;
            b2Body* body10 = m_world->CreateBody(&bd10);
            
            b2FixtureDef *fd10 = new b2FixtureDef; // b2FixtureDef type variable for body10
            fd10->density = 1.f;
            fd10->shape = new b2PolygonShape;
            fd10->shape = &shape10;
            
            b2FixtureDef *fd11 = new b2FixtureDef; // b2BodyDef type variable for body11
            fd11->density = 1.f;
            fd11->shape = new b2PolygonShape;
            fd11->shape = &shape11;
            
            body10->CreateFixture(fd10);
            body10->CreateFixture(fd11);
            
            b2BodyDef bd12; // b2BodyDef type variable for body12 which is hidden object.
            bd12.position.Set(-44.0f, 40.0f);
            b2Body* body12 = m_world->CreateBody(&bd12);
			
            b2RevoluteJointDef jointDef10; //!jointDef10 is b2RevoluteJointDef type variable used for the revolute joint
            jointDef10.bodyA = body10;
            jointDef10.bodyB = body12;
			
            jointDef10.localAnchorA.Set(+0.4,0);
            jointDef10.localAnchorB.Set(+0.4,0);
            jointDef10.collideConnected = false;
            
            m_world->CreateJoint(&jointDef10);

            hinge_body->CreateFixture(fd1);
            hinge_body->CreateFixture(fd2);
            hinge_body->CreateFixture(fd3);
        }

    }
    
    sim_t *sim = new sim_t("Dominos", dominos_t::create);
    
}
