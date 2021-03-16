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
	ID2D1Bitmap* mBitmap;		//HBitmap���� ��Ʈ�� ���� �ҷ��� �༮
	float				mAlpha;			//�׸� ���İ�

	Vector2				mSize;			//�׸� ������ 
	float				mScale;			//�׸� ������
	float				mAngle;			//�׸� ����

	TagLoadedImageInfo	mLoadInfo;		//�̹��� �ҷ����� ����

	vector<Image::FrameRect>	mFrameInfo;	//����������
	int							mMaxFrameX;	//���������� ��
	int							mMaxFrameY;	//���� ������ �� 
private:
	friend class ImageManager;
	//�⺻ ������ ������ ���ֹ����� ���!!!!
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

