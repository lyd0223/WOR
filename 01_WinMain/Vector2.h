#pragma once

//���Ϻ��� Ŭ���� ����ǵ� �� �𸣰����� �׳� x,y �ִ� ����ü��� �����ϸ� �ȴ�
class Vector2 final
{
private:
	Property(float, X)
		Property(float, Y)
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	Vector2(POINT pt);

	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	Vector2 operator*(float scalar);
	Vector2 operator/(float scalar);
	bool operator==(const Vector2& v);
	bool operator!=(const Vector2& v);
public:
	static Vector2 Normalize(const Vector2& v);
	static float Length(const Vector2& v);
	static float Dot(const Vector2& v1, const Vector2& v2);
	static float Cross(const Vector2& v1, const Vector2& v2);
};

