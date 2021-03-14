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
	//중복 키 허용을 위해 이전 키와 현재 키 변수 사용
	bool mKeyUpList[KEYMAX];		//어떤 키에서 손을 땠는지
	bool mKeyDownList[KEYMAX];		//어떤 키를 눌렀는지 
	bool mKeyList[KEYMAX];		//어떤 키를 눌려져 있는지 체크
public:
	Input();
	bool GetKeyDown(int key);	//키가 눌렸을때 true반환
	bool GetKeyUp(int key);		//키에서 손을 땠을 때 true반환
	bool GetKey(int key);		//키를 계속 누르고 있다면 true반환
	bool GetToggleKey(int key);	//Toggle

	bool GetIsKeyCheck() { return mIsKeyCheck; }
	void SetIsKeyCheck(bool d) { mIsKeyCheck = d; }
};
