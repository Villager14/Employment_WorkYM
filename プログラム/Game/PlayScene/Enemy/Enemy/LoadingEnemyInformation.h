/*
* LoadingEnemyInformation.h
* @brief	敵の情報の読み込み
* @author	Morita
* @date		2024/08/29
*/

#pragma once

#include "EnemyInformation.h"

class LoadingEnemyInformation
{
public:

	LoadingEnemyInformation();

	~LoadingEnemyInformation();

	void Load(int stageNumber);

	//		情報の整理
	void OrganizingInformation(int count, std::string val, EnemyInformation* enemyInformation);

private:

	std::vector<EnemyInformation> m_enemyInformation;

public:

	/*
	*	エネミーの情報を受け取る
	* 
	*	@return 情報
	*/
	std::vector<EnemyInformation>* GetInformation() { return &m_enemyInformation; }

};
