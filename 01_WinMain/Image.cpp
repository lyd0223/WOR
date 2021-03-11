#include "pch.h"
#include "Image.h"

Image::Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mScale(1.f), mAlpha(1.f), mAngle(0.f), mMaxFrameX(1), mMaxFrameY(1)
{
	this->mSize.X = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.Y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.X;
	rc.height = mSize.Y;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}

Image::Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mMaxFrameX(maxFrameX), mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.X = (float)mBitmap->GetPixelSize().width;
	this->mSize.Y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.X / (float)this->mMaxFrameX;
	float frameY = mSize.Y / (float)this->mMaxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = (float)i * (frameX);
			rc.y = (float)j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->mFrameInfo.push_back(rc);
		}
	}

	this->ResetRenderOption();
}

Image::~Image()
{
	mBitmap->Release();
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void Image::Render(const float x, const float y)
{
	Vector2 size = mSize * mScale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x - size.X / 2.f, y - size.Y / 2.f);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}
void Image::ScaleRender(const float x, const float y,const float sizeX, const float sizeY)
{
	Vector2 size;
	size.__typeToSet_X(sizeX);
	size.__typeToSet_Y(sizeY);

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x - size.X / 2.f, y - size.Y / 2.f);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::FrameRender(const float x, const float y, const int frameX, const int frameY)
{
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize * mScale;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x - size.X / 2.f, y - size.Y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}


void Image::ScaleFrameRender(const float x, const float y, const int frameX, const int frameY, const int sizeX, const int sizeY)
{
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size;
	size.__typeToSet_X(sizeX);
	size.__typeToSet_Y(sizeY);

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x - size.X / 2.f, y - size.Y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.X = (float)mBitmap->GetPixelSize().width;
		this->mSize.Y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.X = mFrameInfo[0].width;
		this->mSize.Y = mFrameInfo[0].height;
	}
}
