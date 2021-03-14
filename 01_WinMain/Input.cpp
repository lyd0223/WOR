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
		if (key == 'W') {
			if (mKeyDownList['S'])
				return false;
		}
		else if (key == 'S') {
			if (mKeyDownList['W'])
				return false;
		}
		else if (key == 'A') {
			if (mKeyDownList['D'])
				return false;
		}
		else if (key == 'D') {
			if (mKeyDownList['A'])
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
		if (key == 'W') {
			if (mKeyUpList['S'])
				return false;
		}
		else if (key == 'S') {
			if (mKeyUpList['W'])
				return false;
		}
		else if (key == 'A') {
			if (mKeyUpList['D'])
				return false;
		}
		else if (key == 'D') {
			if (mKeyUpList['A'])
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
		if (key == 'W') {
			if (mKeyList['S'])
				return false;
		}
		else if (key == 'S') {
			if (mKeyList['W'])
				return false;
		}
		else if (key == 'A') {
			if (mKeyList['D'])
				return false;
		}
		else if (key == 'D') {
			if (mKeyList['A'])
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
