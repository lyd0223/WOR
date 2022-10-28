#pragma once

/*
싱글턴 패턴 : 단 하나의 인스턴스만을 가지게 만들고 전역적으로 접근하기 편하게 
하는 패턴
*/
#include <random>

class Random
{
private:
	static Random* m_Instance;
	mt19937 m_Generator;
public:
	//싱글톤 인스턴스 접근자 함수
	static Random* GetInstance()
	{
		if (m_Instance == NULL)
		{
			m_Instance = new Random();
		}
		return m_Instance;
	}

	static void ReleaseInstance()
	{
		if (m_Instance != NULL)
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}
public:
	Random();

	//0~num까지의 랜덤값 반환
	inline int RandomInt(int num) { return rand() % num; }	
	//startNum ~ endNum까지의 랜덤값 반환하는 함수
	inline int RandomInt(int startNum, int endNum)
	{
		return rand() % (endNum - startNum + 1) + startNum;
	}
	
	//정규분포 랜덤
	int NDRandomInt(int num)
	{ 
		int standardDeviation = num / 10;
		normal_distribution<double> dist(/* 평균 = */ num / 2, /* 표준 편차 = */ standardDeviation);

		return round(dist(m_Generator));

		return rand() % num; 
	}
	int NDRandomInt(int startNum, int endNum)
	{
		int avg = (startNum + endNum) / 2;
		int standardDeviation = (endNum - startNum) / 10;
		normal_distribution<double> dist(/* 평균 = */ avg, /* 표준 편차 = */ standardDeviation);

		return round(dist(m_Generator));
	}
};

