#pragma once
class Image
{
public:
	struct TagLoadedImageInfo
	{
		wstring key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const wstring& key, const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap* mBitmap;		//HBitmap같은 비트맵 파일 불러온 녀석
	float				mAlpha;			//그릴 알파값

	Vector2				mSize;			//그릴 사이즈 
	float				mScale;			//그릴 스케일
	float				mAngle;			//그릴 각도

	TagLoadedImageInfo	mLoadInfo;		//이미지 불러오는 정보

	vector<Image::FrameRect>	mFrameInfo;	//프레임정보
	int							mMaxFrameX;	//가로프레임 수
	int							mMaxFrameY;	//세로 프레임 수 
private:
	friend class ImageManager;
	//기본 생성자 못쓰게 없애버리는 방법!!!!
	Image() = delete;
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo);
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY);

	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	void Render(const float x, const float y);
	void RenderFromBottom(const float x, const float y);
	void ScaleRender(const float x, const float y, const float sizeX, const float sizeY);
	void FrameRender(const float x, const float y, const int frameX, const int frameY);
	void FrameRenderFromBottom(const float x, const float y, const int frameX, const int frameY);
	void ScaleFrameRender(const float x, const float y, const int frameX, const int frameY, const int sizeX, const int sizeY);
	wstring GetKey() { return mLoadInfo.key; };
	void SetKey(wstring key) { mLoadInfo.key = key; };
	void ResetRenderOption();

	void SetSize(const Vector2& vec) { this->mSize = vec; }
	void SetAlpha(const float alpha) { this->mAlpha = alpha; }
	void SetScale(const float scale) { this->mScale = scale; }
	void SetAngle(const float angle) { this->mAngle = angle; }

	const int GetMaxFrameX()const { return mMaxFrameX; }
	const int GetMaxFrameY()const { return mMaxFrameY; }
	const wstring GetKey() const { return this->mLoadInfo.key; }
	const UINT GetWidth() const { return mBitmap->GetPixelSize().width; }
	const UINT GetHeight()const { return mBitmap->GetPixelSize().height; }
	const Vector2 GetSize()const { return this->mSize; }
	Vector2 GetFrameSize(const int& frame = 0) const { return Vector2(mFrameInfo[frame].width, mFrameInfo[frame].height); }
	const TagLoadedImageInfo& GetLoadInfo() const { return mLoadInfo; }

	inline ID2D1Bitmap* GetBitmap()const { return mBitmap; }
};

