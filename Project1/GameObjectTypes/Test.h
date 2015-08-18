#ifndef TEST_H
#define TEST_H
#pragma once
#include "GameObject.h"
class Test :
	public GameObject
{
public:
	Test(float x = 0, float y= 0, float rotation = 0);
	virtual ~Test();

	// Inherited via GameObject
	virtual void update() const override;
	virtual void render() const override;
};
#endif
