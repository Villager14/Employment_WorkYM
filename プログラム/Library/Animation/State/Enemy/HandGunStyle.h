/*
* @file		HandGunStay.h
* @brief	�n���h�K���\���̃A�j���[�V����
* @author	Morita
* @date		2024/08/27
*/

#pragma once

#include "../../IAnimation.h"

class AnimationManager;

class HandGunStyle : public IAnimation
{
public:

	HandGunStyle(AnimationManager* PlayerAnimation);

	~HandGunStyle();

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