/*
* @file		PlayerCameraInformation.cpp
* @brief	�v���C���[�̃J�����̏��
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "pch.h"

class PlayerCameraInformation
{
public:
	//		�R���X�g���N�^
	PlayerCameraInformation()
		:
		m_angleMin(0.0f),
		m_viewAngle(70.0f),
		m_mouseSpeed(5.0f)
	{};

	//		�f�X�g���N�^
	~PlayerCameraInformation() {};

	void Initialize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_up = DirectX::SimpleMath::Vector3::Zero;
		m_target = DirectX::SimpleMath::Vector3::Zero;
		m_eye = DirectX::SimpleMath::Vector3::Zero;
		m_cameraMove = DirectX::SimpleMath::Vector2::Zero;
	}

public:

	//		�ő�p�xY
	const float ANGLE_Y_MAX = 50.0f;

	//		�ŏ��p�xY
	const float ANGLE_Y_MIN = -50.0f;

private:

	//		����p
	float m_viewAngle;

	//		�}�E�X�̑��x
	float m_mouseSpeed;

	//		�ŏ��l
	float m_angleMin;

	//		�J�����̊p�x
	DirectX::SimpleMath::Vector2 m_angle;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		�J�����̈ړ���
	DirectX::SimpleMath::Vector2 m_cameraMove;

public:

	/*
	*	����p��ݒ肷��
	* 
	*	@param	(angle)	�p�x
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	����p���󂯎��
	* 
	*	@return	�p�x
	*/
	float GetViewAngle() { return m_viewAngle; }

	/*
	*	�J�����̊p�x���󂯂Ƃ�
	*
	*	@return �p�x
	*/
	const DirectX::SimpleMath::Vector2 GetAngle() { return m_angle; }

	/*
	*	�J�����̊p�x��ݒ肷��
	*
	*	@param	(angle)	�p�x
	*/
	void SetAngle(DirectX::SimpleMath::Vector2 angle) { m_angle = angle; }

	/*
	*	�����x�N�g����ݒ肷��
	*
	*	@param	(velocity)	�x�N�g��
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& velicity) { m_viewVelocity = velicity; }

	/*
	*	�����x�N�g�����󂯎��
	*
	*	@return �x�N�g��
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	Eye�x�N�g����ݒ肷��
	*
	*	@param	(eye)	�����x�N�g��
	*/
	void SetEye(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }

	/*
	*	Eye�x�N�g�����󂯎��
	*
	*	@return �����x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetEye() { return m_eye; }

	/*
	*	�^�[�Q�b�g��ݒ肷��
	*
	*	@param	(target)	�^�[�Q�b�g�x�N�g��
	*/
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	/*
	*	�^�[�Q�b�g���󂯎��
	*
	*	@return �^�[�Q�b�g
	*/
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }

	/*
	*	�A�b�v�x�N�g����ݒ肷��
	*
	*	@param	(up)	�A�b�v�x�N�g��
	*/
	void SetUp(DirectX::SimpleMath::Vector3 up) { m_up = up; }

	/*
	*	�A�b�v�x�N�g�����󂯎��
	*
	*	@return �A�b�v�x�N�g��
	*/
	DirectX::SimpleMath::Vector3 GetUP() { return m_up; }

	/*
	*	�J�����̈ړ��ʂ�ݒ肷��
	*
	*	@param	(move)	�ړ���
	*/
	void SetCameraMove(DirectX::SimpleMath::Vector2 move) { m_cameraMove = move; }

	/*
	*	�J�����̈ړ��ʂ��󂯎��
	*
	*	@return �ړ���
	*/
	DirectX::SimpleMath::Vector2 GetCameraMove() { return m_cameraMove; }

	/*
	*	�J�����p�x�̍ŏ��l���󂯎��
	*
	*	@return �ŏ��l
	*/
	float GetCameraAngleMin() { return m_angleMin; }

	/*
	*	�J�����p�x�̍ŏ��l��ݒ肷��
	* 
	*	@param	(angle)	�p�x
	*/
	void SetCameraAngleMin(float angle) { m_angleMin = angle; }

	/*
	*	�}�E�X�̑��x���󂯎��
	* 
	*	@return	���x
	*/
	float GetCameraSpeed() { return m_mouseSpeed; }

	/*
	*	�}�E�X�̑��x��ݒ肷��
	* 
	*	@param	(speed)
	*/
	void SetCameraSpeed(float speed) { m_mouseSpeed = speed; }

};
