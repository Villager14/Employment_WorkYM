/*
* @file		AnimationCommonProcess.h
* @brief	�A�j���[�V�����̋��ʏ���
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "../Bones/ModelBones.h"

#include "../Bones/BonInformation.h"

class AnimationManager;

class AnimationCommonProcess
{
public:

	//		�R���X�g���N�^
	AnimationCommonProcess(AnimationManager* animationManager);

	//		�f�X�g���N�^
	~AnimationCommonProcess();

	/*
	*	�A�j���[�V�����̓���
	* 
	*	@param	(type)				�ړ�������{�[��
	*	@param	(bonesInformation)	�{�[���̏��
	*	@param	(firstVal)			�����̒l
	*	@param	(endVal)			�ŏI�̒l
	*	@param	(transrationSPeed)	�J�ڂ̑��x
	*/
	void AnimationMovement(BonsType type,
		std::vector<PlayerBonsInformation>* bonesInformation,
		DirectX::SimpleMath::Quaternion firstVal,
		DirectX::SimpleMath::Quaternion endVal,
		float transrationSpeed);

	/*
	*	�����g�̒l��J�ڌ�̒l�ɂ���
	* 
	*	@param	(bonesInformation)	�{�[���̏��
	*	@param	(transrationSpeed)	�J�ڑ��x
	*/
	void AnimationLegInitialValue(
		std::vector<PlayerBonsInformation>* bonesInformation,
		float transrationSpeed);

	//		���n����
	void Landing(float height);

private:

	//		�A�j���[�V�����}�l�[�W���[
	AnimationManager* m_animationManager;
};
