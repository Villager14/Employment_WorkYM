/*
* @file		IAnimation
* @brief	�A�j���[�V�����C���^�[�t�F�[�X
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "pch.h"

#include "../Bones/BonInformation.h"

class IAnimation
{
public:

	//		����������
	virtual void Initialize() = 0;

	/*
	*	�X�V����
	*
	*	@param	(speed)		���x
	*	@param	(position)	���W
	*	@param	(angle)		�p�x
	*	@param	(height)	���̍���
	*	@param	(bonesInformation)	�{�[���̏��
	*/
	virtual void Update(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height, std::vector<PlayerBonsInformation>* bonesInformation) = 0;

	//		�I������
	virtual void Finalize() = 0;

	//		�f�X�g���N�^
	virtual ~IAnimation() = default;
};