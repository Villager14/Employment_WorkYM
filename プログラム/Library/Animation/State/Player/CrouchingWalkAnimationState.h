/*
* @file		CrouchingWalkAnimationState.h
* @brief	���Ⴊ�ݕ����̃A�j���[�V����
* @author	Morita
* @date		2024/06/25
*/

#pragma once

#include "../../IAnimation.h"

#include "../../../Bones/BonInformation.h"

class AnimationManager;

class CrouchingWalkAnimationState : public IAnimation
{
public:

	//		�R���X�g���N�^
	/*
	*	�R���X�g���N�^
	* 
	*	@param	(playerBons) �v���C���[�A�j���[�V�����̃C���X�^���X�̃|�C���^
	*/
	CrouchingWalkAnimationState(AnimationManager* PlayerAnimation);
	
	//		�f�X�g���N�^
	~CrouchingWalkAnimationState();

	//		����������
	void Initialize() override;

	/*
	*	�X�V����
	*
	*	@param	(speed)		���x
	*	@param	(position)	���W
	*	@param	(angle)		�p�x
	*	@param	(height)	���̍���
	*/
	void Update(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle, float height,
		std::vector<PlayerBonsInformation>* bonesInformation) override;

	//		�I������
	void Finalize() override;

private:

	//		�v���C���[�̃A�j���[�V����
	AnimationManager* m_playerAnimation;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�A�j���[�V�����J��
	float m_animationTransration;
};