/*
* @file		PlayerCamera.h
* @brief	�v���C���[�̃J����
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerCamera(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerCamera();
	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;

	//		���_�̗h��
	void ShakingView();

	//		���h��
	void HorizontalShaking();

	//		�c�h��
	void VerticalShaking();

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

	//		�n�_�̍��W
	DirectX::SimpleMath::Vector3 m_position;

	//		�h�ꎞ��
	float m_shakingTime;

	//		����U�銄��
	float m_shakingRatio;

	//		���𓮂������x
	float m_shakingSpeed;
};
