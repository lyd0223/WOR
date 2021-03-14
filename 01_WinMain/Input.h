#pragma once
#include <bitset>

#define KEYMAX 256


class Input final
{
	enum keyStat : int {
		None = 0,
		Down,
		Up,
		Cont
	};
	//static Input* GetInstance()
	//{
	//	static Input _instance;
	//	return &_instance;
	//}
	Singleton(Input)
private:
	enum : int { KeyMax = 256 };
	bool mIsKeyCheck = true;
private:
	//�ߺ� Ű ����� ���� ���� Ű�� ���� Ű ���� ���
	bool mKeyUpList[KEYMAX];		//� Ű���� ���� ������
	bool mKeyDownList[KEYMAX];		//� Ű�� �������� 
	bool mKeyList[KEYMAX];		//� Ű�� ������ �ִ��� üũ
public:
	Input();
	bool GetKeyDown(int key);	//Ű�� �������� true��ȯ
	bool GetKeyUp(int key);		//Ű���� ���� ���� �� true��ȯ
	bool GetKey(int key);		//Ű�� ��� ������ �ִٸ� true��ȯ
	bool GetToggleKey(int key);	//Toggle

	bool GetIsKeyCheck() { return mIsKeyCheck; }
	void SetIsKeyCheck(bool d) { mIsKeyCheck = d; }
};
