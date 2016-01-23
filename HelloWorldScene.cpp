#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
   // auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
#if 1
	int i, j;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	log("@@@@@@@@@@@@@@@@ scence getScheduler = %p\n", getScheduler());
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int offset = 70;
	visibleSize.height -= offset;
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setDynamic(false);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + offset));
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);
		

	m_Counter = 0;
	m_Distance = 96;
	m_Background = Sprite::create("Background/BG_4.jpg");// CSLoader::createNode("MainScene.csb");
	m_Background->setPosition(Vec2(512, 384));
	addChild(m_Background);

	Sprite* sign = Sprite::create("Wooden_signs/Wooden_board_3.png");
	sign->setPosition(Vec2( 48, 116));
	sign->setScale(0.71f);
	addChild(sign);

	Sprite* door = Sprite::create("Door/Door_2_progress_1.png");
	door->setPosition(Vec2(423, 190));
	addChild(door);

	m_Player = new Player();
	m_Player->init();
	m_Player->getPlayer()->setPosition(Vec2(172, 348));
	this->addChild(m_Player, 1);
//	m_Player->Stay();



	for (i=0; i<PLATFORM_NUM_HORIZONTAL; i++)
	{
		//if (i != 0 && (i%5) ==  0)
		//	continue;
		m_Platform[i] = Sprite::create("Platforms/tiles_Green.png");
		m_Platform[i]->setScale(0.336f);
		m_Platform[i]->setPosition(Vec2(40+i*72, 34));
		addChild(m_Platform[i]);
	}

	
#endif
	this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update));
    return true;
}

void HelloWorld::update(float dt)
{
	//log("@@@@@@@@@@@@@@@ %s %s %d \n", __FUNCTION__, __FILE__, __LINE__);
//	m_Player->update(dt);
#if 0
	int i, j, distance;
	m_Counter++;
	if (m_Counter % 2)
		return;
	
	distance = m_Platform[0][0]->getPositionX() - 1;

	for (i = 0; i<PLATFORM_NUM_HORIZONTAL; i++)
	{
		if (i != 0 && (i % 5) == 0)
			continue;
		m_Platform[i][0]->setPositionX(distance + i * 70);
		m_Platform[i][1]->setPositionX(distance + i * 70);
	}
#endif
}

