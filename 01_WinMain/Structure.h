#pragma once
#include "GameObject.h"
class Structure : public GameObject
{
	Image* mImage;
	Image* mPortalImage;
	bool mPortalOn;

public:
	Structure(const string& name, Image* image, float x, float y, float sizex, float sizey);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render()override;
	
	Image* GetImage() { return mImage; };
};

