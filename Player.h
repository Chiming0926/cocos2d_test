#ifndef PLAYER_H_
#define PLAYER_H_
#include "cocos2d.h"
USING_NS_CC;

enum MOVE
{
	MOVE_STOP,
	MOVE_LEFT,
	MOVE_RIGHT,
};


class Player : public cocos2d::Node
{
private:
	Sprite*		m_Player;
	Animation*	m_StopAnimation;
	Animation*	m_WalkRightAnimation;
	Animation*	m_WalkLeftAnimation;
	
	Animate*	m_WalkRightAnimate;
	Animate*	m_WalkLeftAnimate;
	Animate*	m_StopAnimate;
	int			status;
	bool		m_jump;
	int			m_action_tag[2];
public:
	virtual ~Player();

	bool		init();
	Sprite*		getPlayer();
	void		SetPosition(Vec2);
	Animate*	getWalkAnimate();
	Animate*	getStayAnimate();
	void		onKeyPressed(EventKeyboard::KeyCode code, Event* event);
	void		onKeyReleased(EventKeyboard::KeyCode code, Event* event);
	bool		onContactBegin(PhysicsContact &contact);
	void		update(float dt);
	void		moveRight(CCNode* sender);
	void		moveLeft(CCNode* sender);
	void		jump();
	void		jumpCallback(CCNode* sender);

};

#endif /* PLAYER_H_ */
