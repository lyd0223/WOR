#include "pch.h"
#include "Input.h"

/****************************************************
## Input ##
*****************************************************/
Input::Input()
{
	//ó���� ��� Ű�� �������� ���� ���·� �ʱ�ȭ
	ZeroMemory(mKeyDownList, sizeof(bool) * KEYMAX);
	ZeroMemory(mKeyUpList, sizeof(bool) * KEYMAX);
	ZeroMemory(mKeyList, sizeof(bool) * KEYMAX);
}
bool Input::GetKeyDown(int key)
{
	if (!mIsKeyCheck)
		return false;
	//GetAsyncKeyState : ���� Ű�� ���ȴ��� �ȴ��ȴ��� �� Ű�� ���� ���¸� ��ȯ���ִ� �Լ�
	//�ش� Ű�� �����ִٸ�
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (key == VK_UP) {
			if (mKeyDownList[VK_DOWN])
				return false;
		}
		else if (key == VK_DOWN) {
			if (mKeyDownList[VK_UP])
				return false;
		}
		else if (key == VK_LEFT) {
			if (mKeyDownList[VK_RIGHT])
				return false;
		}
		else if (key == VK_RIGHT) {
			if (mKeyDownList[VK_LEFT])
				return false;
		}
		//�ش�Ű�� ������ �ʾҴٸ�
		if (mKeyDownList[key] == false)
		{
			mKeyDownList[key] = true;
			return true;
		}
	}
	//�ش� Ű�� �������� �ʴٸ�
	else
	{
		//Ű���� ���´� false
		mKeyDownList[key] = false;
	}

	return false;
}

bool Input::GetKeyUp(int key)
{
	if (!mIsKeyCheck)
		return false;
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (key == VK_UP) {
			if (mKeyUpList[VK_DOWN])
				return false;
		}
		else if (key == VK_DOWN) {
			if (mKeyUpList[VK_UP])
				return false;
		}
		else if (key == VK_LEFT) {
			if (mKeyUpList[VK_RIGHT])
				return false;
		}
		else if (key == VK_RIGHT) {
			if (mKeyUpList[VK_LEFT])
				return false;
		}
		mKeyUpList[key] = true;
	}
	else
	{
		if (mKeyUpList[key] == true)
		{
			mKeyUpList[key] = false;
			return true;
		}
	}

	return false;
}

bool Input::GetKey(int key)
{
	if (!mIsKeyCheck)
		return false;
	if (GetAsyncKeyState(key) & 0x8000) {
		if (key == VK_UP) {
			if (mKeyList[VK_DOWN])
				return false;
		}
		else if (key == VK_DOWN) {
			if (mKeyList[VK_UP])
				return false;
		}
		else if (key == VK_LEFT) {
			if (mKeyList[VK_RIGHT])
				return false;
		}
		else if (key == VK_RIGHT) {
			if (mKeyList[VK_LEFT])
				return false;
		}
		mKeyList[key] = true;
		return true;
	}
	mKeyList[key] = false;
	return false;
}

bool Input::GetToggleKey(int key)
{
	if (!mIsKeyCheck)
		return false;
	if (GetAsyncKeyState(key) & 0x0001)
		return true;

	return false;
}
