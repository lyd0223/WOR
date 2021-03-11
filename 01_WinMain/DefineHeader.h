#pragma once
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 1280
#define WINSIZEY 720

//���ڷ� ���� p�� �����ϰ� NULL�� �ʱ�ȭ �ϴ� ��ũ�� �Լ�, �����ϰ� ����
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//�̱��� ��ũ��
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

#define Resources(Path) (wstring(L"../02_Resources/").append(Path))

//�ݼ�
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}

//D2D
#define Property(type, name)																	\
	public: __declspec(property(put = __typeToSet_##name, get = __typeToGet##name)) type name;	\
	void __typeToSet_##name(const type& value) { m##name = value; }							\
	type __typeToGet##name() const { return m##name; }											\
	private: type m##name;																		\

#define ReadonlyProperty(type, name)															\
	public: __declspec(property(get = __typeToGet_##name)) type name;							\
	type __typeToGet_##name() const { return m##name; }										\
	private: type m##name;																		\
