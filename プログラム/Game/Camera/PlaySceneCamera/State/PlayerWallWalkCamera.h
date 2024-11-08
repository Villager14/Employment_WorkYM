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

class PlayerWallWalkCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerWallWalkCamera(PlayerCameraManager* playerCameraManager);

	//		�f�X�g���N�^
	~PlayerWallWalkCamera();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�I������
	void Finalize() override;

	//		�p�x�̕Ԋҏ���
	/*
	*	�p�x�ϊ�����
	* 
	*	@param	(radian)	�p�x
	*	@return �p�x
	*/
	void RadianConversion(float* cameraangle, float* velocityRadian);


private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

	//		�o�ߎ���
	float m_time;
};
