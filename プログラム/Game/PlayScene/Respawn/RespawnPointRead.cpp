/*
* @file		RespawnPointRead.cpp
* @brief	���X�|�[���|�C���g�̓ǂݍ��ݏ���
* @author	Morita
* @date		2024/10/03
*/

#include "pch.h"

#include <fstream>

#include "RespawnPointRead.h"

RespawnPointRead::RespawnPointRead()
	:
	m_direction{}
{
}

RespawnPointRead::~RespawnPointRead()
{
}

void RespawnPointRead::ReadProcess(int stageNumber)
{
	std::string path = "";

	switch (stageNumber)
	{
	case 0:
		path = "Resources/Excel/SpownPoint/SpownPoint.csv";
		break;
	default:
		break;
	}

	//		�t�@�C�����J��
	std::fstream file(path);

	//		�t�@�C�����J���Ă��Ȃ��ꍇ���������Ȃ�
	if (!file.is_open()) return;

	std::string line;

	for (int i = 0; std::getline(file, line); ++i)
	{
		std::stringstream ss(line);

		std::string value;

		int index = 0;

		//		���W
		DirectX::SimpleMath::Vector3 position;

		//		����
		float length = 0.0f;

		float direction = 0.0f;

		while (std::getline(ss, value, ','))
		{
			SetParameter(value, index, &position, &length, &direction);

			index++;
		}

		m_position.push_back(position);
		m_length.push_back(length);
		m_direction.push_back(direction);
	}

	//		�t�@�C�������
	file.close();

}

void RespawnPointRead::SetParameter(std::string val, int index,
	DirectX::SimpleMath::Vector3* position, float *length, float* direction)
{
	if (index == 0)			position->x = std::stof(val);
	else if (index == 1)	position->y = std::stof(val);
	else if (index == 2)	position->z = std::stof(val);
	else if (index == 3)	*length		= std::stof(val);
	else if (index == 4)	*direction	= std::stof(val);
}

void RespawnPointRead::Finalize()
{
	m_position.clear();
	m_position.shrink_to_fit();
	m_length.clear();
	m_length.shrink_to_fit();
	m_direction.clear();
	m_direction.shrink_to_fit();
}
