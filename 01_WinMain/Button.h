#pragma once
#include "GameObject.h"

class Button : public GameObject
{
	Image* mImage;
	
public:
	Button(string name,float x, float y, float sizex, float sizey);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render()override;
	void BookOpen();
	void BookClose();
};

