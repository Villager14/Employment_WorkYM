/*
* @file		DebugCamera.h
* @brief	�f�o�b�N�J����
* @author	Morita
* @date		2024/04/23
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class DebugCamera : public IPlayerCamera
{
public:
	
	//		�R���X�g���N�^
	DebugCamera(PlayerCameraManager* playerCameraManager);

	//		�f�X�g���N�^
	~DebugCamera();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

};


