#include "pch.h"
#include "Random.h"
#include <random>
#include <ctime>
//static 변수는 반드시 cpp에서 초기화 및 선언을 해주어야 한다.
Random* Random::m_Instance = NULL;

Random::Random()
{
	srand(time(NULL));

	random_device m_RandomDevice;
	m_Generator = mt19937(m_RandomDevice());
}

