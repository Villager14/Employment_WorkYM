/*
* @file		WireObjectInformation.h
* @brief	�v���C���[�̏���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "pch.h"

struct WireObjectInformation
{
	int number = -1;							//		�ԍ�
	DirectX::SimpleMath::Vector3 position;		//		���W
	bool m_usedJudgement = false;				//		�g���邩�ǂ���
	bool m_actionJudgement = false;				//		�A�N�V�������s���Ă��邩�ǂ���
};