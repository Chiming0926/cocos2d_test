#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;


#define MOVE_IMPLUSE 100000.0f

bool Player::init() 
{
	m_Player = Sprite::create();
	m_Player->setSpriteFrame(SpriteFrame::create("Hero/hero_stop.png", Rect(3, 2, 67, 95)));
	auto body = PhysicsBody::createBox(m_Player->getContentSize(), PhysicsMaterial(0, 0, 0));
//	body->setDynamic(true);
	body->setRotationEnable(false);
	body->setGravityEnable(true);
	body->setCollisionBitmask(0x01); body->setContactTestBitmask(true);
	m_Player->setPhysicsBody(body);
	Vector<SpriteFrame*> frameVector;
	
	Rect rect[4];
	rect[0].setRect(3, 2, 67, 95);
	rect[1].setRect(3, 2, 67, 95);
	for (int i = 0; i <2; i++) 
		frameVector.pushBack(SpriteFrame::create("Hero/hero_stop.png", rect[i]));

	m_StopAnimation = Animation::createWithSpriteFrames(frameVector, 0.25f);
	m_StopAnimation->setRestoreOriginalFrame(false);
	m_StopAnimation->setLoops(1);
	m_StopAnimate = Animate::create(m_StopAnimation);
	m_StopAnimate->retain();

	frameVector.clear();
	rect[0].setRect(3,  7,   70, 91);
	rect[1].setRect(78, 7,   70, 91);
	rect[2].setRect(3,  111, 70, 91);
	rect[3].setRect(78, 111, 70, 91);
	for (int i = 0; i <4; i++)
		frameVector.pushBack(SpriteFrame::create("Hero/hero_walk_right.png", rect[i]));
	m_WalkRightAnimation = Animation::createWithSpriteFrames(frameVector, 0.25f);
	m_WalkRightAnimation->setRestoreOriginalFrame(false);
	m_WalkRightAnimation->setLoops(1000);
	m_WalkRightAnimate = Animate::create(m_WalkRightAnimation);
	m_WalkRightAnimate->retain();

	frameVector.clear();
	for (int i = 0; i <4; i++)
		frameVector.pushBack(SpriteFrame::create("Hero/hero_walk_left.png", rect[i]));

	m_WalkLeftAnimation = Animation::createWithSpriteFrames(frameVector, 0.25f);
	m_WalkLeftAnimation->setRestoreOriginalFrame(false);
	m_WalkLeftAnimation->setLoops(1000);
	m_WalkLeftAnimate = Animate::create(m_WalkLeftAnimation);
	m_WalkLeftAnimate->retain();

	addChild(m_Player);

	m_action_tag[0] = 0xc0c05001;
	m_action_tag[1] = 0xc0c05002; 
	m_jump = false;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contact = EventListenerPhysicsContact::create();
	contact->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);
 	return true;
}

bool Player::onContactBegin(PhysicsContact &contact)
{
	return true;
}

//3
void Player::SetPosition(Vec2 _pos) 
{
	log("%s", "Player::SetPosition()");
	m_Player->setPosition(_pos);
}

Sprite* Player::getPlayer() 
{
	return m_Player;
}

Player::~Player()
{
	m_WalkRightAnimate->release();
}

void Player::moveRight(CCNode* sender)
{
	if (status != MOVE_RIGHT)
	{
		m_Player->stopActionByTag(m_action_tag[0]);
		m_Player->stopAction(m_WalkLeftAnimate);
		status = MOVE_RIGHT;
		auto action = Sequence::create(
			MoveBy::create(2.0f, Vec2(150, 0)),
			CallFuncN::create(CC_CALLBACK_1(Player::moveRight, this)),
			nullptr);
		action->setTag(m_action_tag[1]);
		m_Player->runAction(action);
		m_Player->runAction(m_WalkRightAnimate);
	}
	else
	{
		auto action = Sequence::create(
			MoveBy::create(2.0f, Vec2(150, 0)),
			CallFuncN::create(CC_CALLBACK_1(Player::moveRight, this)),
			nullptr);
		action->setTag(m_action_tag[1]);
		m_Player->runAction(action);
	}
}

void Player::jumpCallback(CCNode* sender)
{
	m_jump = false;
}
void Player::jump()
{
	if (!m_jump)
	{
		auto action = Sequence::create(
			JumpBy::create(1.8f, Vec2(0, 150), 150, 1),
			CallFuncN::create(CC_CALLBACK_1(Player::jumpCallback, this)),
			nullptr);
		m_Player->runAction(action);
		m_jump = true;
		
		/* method 2: Change the body's velocity, but the velocity of jump is not faster */
	//	m_Player->getPhysicsBody()->setVelocity(Vec2(0, 150));
	}
}

void Player::moveLeft(CCNode* sender)
{
	if (status != MOVE_LEFT)
	{
		m_Player->stopActionByTag(m_action_tag[1]);
		m_Player->stopAction(m_WalkRightAnimate);
		status = MOVE_LEFT;
		auto action = Sequence::create(
			MoveBy::create(2.0f, Vec2(-150, 0)),
			CallFuncN::create(CC_CALLBACK_1(Player::moveLeft, this)),
			nullptr);
		action->setTag(m_action_tag[0]);
		m_Player->runAction(action);
		m_Player->runAction(m_WalkLeftAnimate);
	}
	else
	{
		auto action = Sequence::create(
			MoveBy::create(2.0f, Vec2(-150, 0)),
			CallFuncN::create(CC_CALLBACK_1(Player::moveLeft, this)),
			nullptr);
		action->setTag(m_action_tag[0]);
		m_Player->runAction(action);
	}
}

void Player::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
	if (code == EventKeyboard::KeyCode::KEY_K)
	{
	}
	else if (code == EventKeyboard::KeyCode::KEY_A)
	{
	}
	else if (code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		this->moveRight(0);
	}
	else if (code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		this->moveLeft(0);
	}
	else if (code == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		this->jump();
	}
}

void Player::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
	if (status == MOVE_RIGHT && code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		status = MOVE_STOP;
		m_Player->stopActionByTag(m_action_tag[1]);
		m_Player->stopAction(m_WalkRightAnimate);
		m_Player->runAction(m_StopAnimate);
	}
	if (status == MOVE_LEFT && code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		status = MOVE_STOP;
		m_Player->stopActionByTag(m_action_tag[0]);
		m_Player->stopAction(m_WalkLeftAnimate);
		m_Player->runAction(m_StopAnimate);
	}
}

void Player::update(float dt)
{

}
