#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

#define PLATFORM_NUM_HORIZONTAL 20
#define PLATFORM_NUM_VERTICAL 2
USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float dt);
	int m_Counter;
	float m_Distance;
	cocos2d::CCSprite *m_Background;
//	cocos2d::CCSprite * _foreground;
	cocos2d::CCSprite*	m_Platform[PLATFORM_NUM_HORIZONTAL];
	Player* m_Player;

private:
	cocos2d::PhysicsWorld *m_PhyWorld;

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_PhyWorld = world; };
};

#endif // __HELLOWORLD_SCENE_H__
