/*
*	�G�l�~�[�̏��
* @brief	�G�̏��
* @author	Morita
* @date		2024/08/29
*/

#pragma once

#include "pch.h"


struct EnemyInformation
{
	enum EnemyType
	{
		NormalEnemy,	//		��ʃG�l�~�[

		Empty,
	};

	//		���W
	DirectX::SimpleMath::Vector3 position;

	//		���E�ړ����̉�]��(�n��)
	DirectX::SimpleMath::Quaternion startQuaternion;

	//		���E�ړ����̉�]��(�I���)
	DirectX::SimpleMath::Quaternion endQuaternion;

	//		���
	EnemyType enemyType = EnemyType::Empty;
};