/*
* LoadingEnemyInformation.h
* @brief	�G�̏��̓ǂݍ���
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

	//		���̐���
	void OrganizingInformation(int count, std::string val, EnemyInformation* enemyInformation);

private:

	std::vector<EnemyInformation> m_enemyInformation;

public:

	/*
	*	�G�l�~�[�̏����󂯎��
	* 
	*	@return ���
	*/
	std::vector<EnemyInformation>* GetInformation() { return &m_enemyInformation; }

};
