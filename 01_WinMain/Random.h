#pragma once

/*
�̱��� ���� : �� �ϳ��� �ν��Ͻ����� ������ ����� ���������� �����ϱ� ���ϰ� 
�ϴ� ����
*/
#include <random>

class Random
{
private:
	static Random* m_Instance;
	mt19937 m_Generator;
public:
	//�̱��� �ν��Ͻ� ������ �Լ�
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

	//0~num������ ������ ��ȯ
	inline int RandomInt(int num) { return rand() % num; }	
	//startNum ~ endNum������ ������ ��ȯ�ϴ� �Լ�
	inline int RandomInt(int startNum, int endNum)
	{
		return rand() % (endNum - startNum + 1) + startNum;
	}
	
	//���Ժ��� ����
	int NDRandomInt(int num)
	{ 
		int standardDeviation = num / 10;
		normal_distribution<double> dist(/* ��� = */ num / 2, /* ǥ�� ���� = */ standardDeviation);

		return round(dist(m_Generator));

		return rand() % num; 
	}
	int NDRandomInt(int startNum, int endNum)
	{
		int avg = (startNum + endNum) / 2;
		int standardDeviation = (endNum - startNum) / 10;
		normal_distribution<double> dist(/* ��� = */ avg, /* ǥ�� ���� = */ standardDeviation);

		return round(dist(m_Generator));
	}
};

