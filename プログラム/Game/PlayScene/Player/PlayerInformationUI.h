/*
* @file		PlayerInformationUI.h
* @brief	UI�p����p�v���C���[�̏��
* @author	Morita
* @date		2024/05/16
*/

#pragma once

#include "pch.h"

class PlayerInformationUI
{
public:
	//		�R���X�g���N�^
	PlayerInformationUI()
	:
		m_dashJudgement(false),
		m_dashCoolTime(0.0f),
		m_dashMaxTime(0.0f)
	{};

	//		�f�X�g���N�^
	~PlayerInformationUI() {};

private:

	//		�_�b�V�����Ă��邩�ǂ���
	bool m_dashJudgement;

	//		�_�b�V���̃N�[���^�C�����Ԃ��󂯎��
	float m_dashCoolTime;

	//		�_�b�V���̃N�[���^�C���ő厞��
	float m_dashMaxTime;

public:
};


