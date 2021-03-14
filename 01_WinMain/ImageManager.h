#pragma once
class ImageManager
{
	Singleton(ImageManager)
private:
	typedef map<wstring, class Image*>::iterator ImageIter;
	map<wstring, class Image*> mImageList;

	IWICImagingFactory* mWicFactory;	//PNG�̹����� �긦 ������ D2D�� ��Ʈ������ ��ȯ
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