#include "pch.h"
#include "ImageManager.h"
#include <assert.h>
#include "Image.h"
ImageManager::ImageManager()
	:mWicFactory(nullptr)
{
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&mWicFactory));
	assert(SUCCEEDED(hr));
}

ImageManager::~ImageManager()
{
	ImageIter iter = mImageList.begin();
	for (; iter != mImageList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}

	mWicFactory->Release();
}

void ImageManager::LoadFromFile(const wstring& key, const wstring& file)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);

	if (bitmap != nullptr)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo);
		mImageList.insert(make_pair(key, image));
	}
	else
	{
		assert(SUCCEEDED(E_FAIL));
	}
}

void ImageManager::LoadFromFile(const wstring& key, const wstring& file, int frameX, int frameY)
{
	Image* image = FindImage(key);
	if (image != nullptr)
		return;

	ID2D1Bitmap* bitmap = CreateD2DBitmapFromFile(file);

	if (bitmap != nullptr)
	{
		Image::TagLoadedImageInfo loadInfo(key, file);
		image = new Image(bitmap, loadInfo, frameX, frameY);
		mImageList.insert(make_pair(key, image));
	}
	else
	{
		assert(SUCCEEDED(E_FAIL));
	}
}

Image* ImageManager::FindImage(const wstring& key)
{
	ImageIter iter = mImageList.find(key);
	if (iter != mImageList.end())
		return iter->second;
	return nullptr;
}

ID2D1Bitmap* ImageManager::CreateD2DBitmapFromFile(const wstring& file)
{
	IWICBitmapDecoder* decoder = nullptr;
	HRESULT hr;
	hr = mWicFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand, &decoder);
	assert(SUCCEEDED(hr));

	IWICBitmapFrameDecode* frame = nullptr;
	hr = decoder->GetFrame(0, &frame);
	assert(SUCCEEDED(hr));

	IWICFormatConverter* converter;
	hr = mWicFactory->CreateFormatConverter(&converter);
	assert(SUCCEEDED(hr));
	hr = converter->Initialize
	(
		frame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.f,
		WICBitmapPaletteTypeCustom
	);
	assert(SUCCEEDED(hr));

	ID2D1Bitmap* result;
	hr = D2DRenderer::GetInstance()->GetRenderTarget()
		->CreateBitmapFromWicBitmap(converter, nullptr, &result);
	assert(SUCCEEDED(hr));

	converter->Release();
	frame->Release();
	decoder->Release();

	return result;
}
