#include "pch.h"
#include "Random.h"
#include <random>
#include <ctime>
//static ������ �ݵ�� cpp���� �ʱ�ȭ �� ������ ���־�� �Ѵ�.
Random* Random::m_Instance = NULL;

Random::Random()
{
	srand(time(NULL));

	random_device m_RandomDevice;
	m_Generator = mt19937(m_RandomDevice());
}

