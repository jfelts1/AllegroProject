#ifndef TEST_H
#define TEST_H
#pragma once

#include "GameObject.h"
class Test :
	public GameObject
{
public:
	Test(float x = 0, float y = 0, float rotation = 0);
	virtual ~Test();
	//copy constructor
	Test(const Test& orig);
	//move conststructor
	Test(const Test&& orig) noexcept : GameObject(orig)
	{}
	

	// Inherited via GameObject
	virtual void update() override;
	virtual void render() const override;
};
#endif
