#pragma once

/*
## ObjectManager ##
GameObject 관리하는 클래스
*/

//enum (열거자) : 정수를 다른 이름으로 표현하는 것
enum class ObjectLayer : int
{
	Background = 0,
	Tile,
	Player,
	Particle,
	Enemy,
	Structure,
	Skill,
	UI,

	End
};

class ObjectManager
{
	Singleton(ObjectManager)
private:
	typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	map<ObjectLayer, vector<class GameObject*>> mObjectList;
	stack<class GameObject*>  mInterface;
	//map<class Scene, map<ObjectLayer, vector<class GameObject*>>> mObjectListOfScene;

public:
	ObjectManager();

	void Init();
	void Release();
	void Update();
	void Render();

	void AddObject(ObjectLayer layer, class GameObject* object);
	void AddInterface(class GameObject* object);
	void PopInterface();
	void InterfaceClear();
	void DeleteObjects(ObjectLayer layer);

	class GameObject* FindObject(const string& name);
	class GameObject* FindObject(ObjectLayer layer, const string& name);
	vector<class GameObject*> FindObjects(const string& name);
	vector<class GameObject*> FindObjects(ObjectLayer layer, const string& name);
	vector<class GameObject*> GetObjectList(ObjectLayer layer);
	stack<class GameObject*> GetInterfaceList() { return mInterface; }

};