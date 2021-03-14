#pragma once
class ImageManager
{
	Singleton(ImageManager)
private:
	typedef map<wstring, class Image*>::iterator ImageIter;
	map<wstring, class Image*> mImageList;

	IWICImagingFactory* mWicFactory;	//PNG이미지를 얘를 가지고 D2D용 비트맵으로 변환
public:
	ImageManager();
	~ImageManager();

	void LoadFromFile(const wstring& key, const wstring& file);
	void LoadFromFile(const wstring& key, const wstring& file,
		int frameX, int frameY);
	class Image* FindImage(const wstring& key);
private:
	ID2D1Bitmap* CreateD2DBitmapFromFile(const wstring& file);
};