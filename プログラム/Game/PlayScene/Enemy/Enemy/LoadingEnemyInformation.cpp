/*
* LoadingEnemyInformation.cpp
* @brief	敵の情報の読み込み
* @author	Morita
* @date		2024/08/29
*/

#include "pch.h"

#include "LoadingEnemyInformation.h"

#include <fstream>

LoadingEnemyInformation::LoadingEnemyInformation()
{
}

LoadingEnemyInformation::~LoadingEnemyInformation()
{
}

void LoadingEnemyInformation::Load(int stageNumber)
{
	std::string path = "";

	switch (stageNumber)
	{
	case 1:
		path = "Resources/Excel/Enemy/EnemyStage1.csv";
		break;
	default:
		break;
	}

	//		ファイルを開く
	std::fstream file(path);

	//		ファイルが開いていない場合処理をしない
	if (!file.is_open()) return;

	std::string line;

	for (int i = 0; std::getline(file, line); ++i)
	{
		std::stringstream ss(line);

		std::string value;

		EnemyInformation enemyInformation;

		int count = 0;

		while (std::getline(ss, value, ','))
		{
			OrganizingInformation(count, value, &enemyInformation);

			count++;
		}

		m_enemyInformation.push_back(enemyInformation);
	}

	//		ファイルを閉じる
	file.close();
}

void LoadingEnemyInformation::OrganizingInformation(int count, std::string val, EnemyInformation* enemyInformation)
{
	if (count == 0) enemyInformation->position.x = std::stof(val);
	else if (count == 1) enemyInformation->position.y = std::stof(val);
	else if (count == 2) enemyInformation->position.z = std::stof(val);


	else if (count == 3) enemyInformation->startQuaternion.x = std::stof(val);
	else if (count == 4) enemyInformation->startQuaternion.y = std::stof(val);
	else if (count == 5) enemyInformation->startQuaternion.z = std::stof(val);

	else if (count == 6) enemyInformation->endQuaternion.x = std::stof(val);
	else if (count == 7) enemyInformation->endQuaternion.y = std::stof(val);
	else if (count == 8) enemyInformation->endQuaternion.z = std::stof(val);

	else if (count == 9)
	{
		switch (std::stoi(val))
		{
		default:
		case 1:
			enemyInformation->enemyType = EnemyInformation::NormalEnemy;
			break;
		}
	}
}
