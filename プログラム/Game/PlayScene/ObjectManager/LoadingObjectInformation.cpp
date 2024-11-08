/*
* LoadingObjectInformation.cpp
* @brief	オブジェクトの情報の読み込み
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

	//		ファイルを開く
	std::fstream file(path);

	//		ファイルが開いていない場合処理をしない
	if (!file.is_open()) return;

	std::string line;

	for (int i = 0; std::getline(file, line); ++i)
	{
		//		一行目は読まない
		if (i == 0) continue;

		std::stringstream ss(line);

		std::string value;

		//		オブジェクトの情報
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

	//		ファイルを閉じる
	file.close();
}

void LoadingObjectInformation::OrganizingInformation(int count,
	std::string val, ObjectInformation* objectInformation)
{
	//		オブジェクトのタイプ
	if (count == 0) objectInformation->objectType =
		ObjectInformation::ObjectType(std::stoi(val));

	//		オブジェクトのモデルパス
	if (count == 1) objectInformation->modelPath = val;

	//		オブジェクトの当たり判定パス
	if (count == 2) objectInformation->collitionPath = val;

	//		オブジェクトの座標
	if (count == 3) objectInformation->position.x = std::stof(val);
	else if (count == 4) objectInformation->position.y = std::stof(val);
	else if (count == 5) objectInformation->position.z = std::stof(val);

	//		オブジェクトの回転量
	else if (count == 6) objectInformation->rotation.x = std::stof(val);
	else if (count == 7) objectInformation->rotation.y = std::stof(val);
	else if (count == 8) objectInformation->rotation.z = std::stof(val);

	//		エフェクトフラグ
	else if (count == 9) objectInformation->effectFlag = std::stoi(val);
}

void LoadingObjectInformation::Finalize()
{
	m_objectInformation.clear();
	m_objectInformation.shrink_to_fit();
}
