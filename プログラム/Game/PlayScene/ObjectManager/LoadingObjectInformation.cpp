/*
* LoadingObjectInformation.cpp
* @brief	�I�u�W�F�N�g�̏��̓ǂݍ���
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "LoadingObjectInformation.h"

#include <fstream>

LoadingObjectInformation::LoadingObjectInformation()
{
}

LoadingObjectInformation::~LoadingObjectInformation()
{
}

void LoadingObjectInformation::Load(int stageNumber)
{
	std::string path = "";

	switch (stageNumber)
	{
	case 0:
		path = "Resources/Excel/Stage/Tutorial.csv";
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
		//		��s�ڂ͓ǂ܂Ȃ�
		if (i == 0) continue;

		std::stringstream ss(line);

		std::string value;

		//		�I�u�W�F�N�g�̏��
		ObjectInformation objectInformation;

		int count = 0;

		while (std::getline(ss, value, ','))
		{
			OrganizingInformation(count, value,
				&objectInformation);

			count++;
		}

		m_objectInformation.push_back(objectInformation);
	}

	//		�t�@�C�������
	file.close();
}

void LoadingObjectInformation::OrganizingInformation(int count,
	std::string val, ObjectInformation* objectInformation)
{
	//		�I�u�W�F�N�g�̃^�C�v
	if (count == 0) objectInformation->objectType =
		ObjectInformation::ObjectType(std::stoi(val));

	//		�I�u�W�F�N�g�̃��f���p�X
	if (count == 1) objectInformation->modelPath = val;

	//		�I�u�W�F�N�g�̓����蔻��p�X
	if (count == 2) objectInformation->collitionPath = val;

	//		�I�u�W�F�N�g�̍��W
	if (count == 3) objectInformation->position.x = std::stof(val);
	else if (count == 4) objectInformation->position.y = std::stof(val);
	else if (count == 5) objectInformation->position.z = std::stof(val);

	//		�I�u�W�F�N�g�̉�]��
	else if (count == 6) objectInformation->rotation.x = std::stof(val);
	else if (count == 7) objectInformation->rotation.y = std::stof(val);
	else if (count == 8) objectInformation->rotation.z = std::stof(val);

	//		�G�t�F�N�g�t���O
	else if (count == 9) objectInformation->effectFlag = std::stoi(val);
}

void LoadingObjectInformation::Finalize()
{
	m_objectInformation.clear();
	m_objectInformation.shrink_to_fit();
}
