/*
* @file		PlayerInformation.cpp
* @brief	�v���C���[�̏��
* @author	Morita
* @date		2024/05/19
*/

#pragma once

#include "pch.h"

class PlayerInformation
{
public:
	//		�R���X�g���N�^
	PlayerInformation() 
		:
		m_position{ 0.0f, 0.0f, 0.0f },
		m_planPosition{ 0.0f, 0 ,0.0f },
		m_heightTime(0.0f),
		m_fallTime(0.0f),
		m_gravity(0.0f),
		m_meshHitJudgement(false),
		m_timeSpeed(1.0f),
		m_dashJudgement(true),
		m_dashCoolTime(0.0f),
		m_jumpJudgement(true),
		m_respownJudgement(false),
		m_headWallMove(0.0f),
		m_stopCamera(false),
		m_wireUseJudgement(false),
		m_playerHeadShakingJudgement(false)
	{};

	//		�f�X�g���N�^
	~PlayerInformation() {};

	void Initialize()
	{
		m_position = { 0.0f, 0.0f, 0.0f };
		m_planPosition = { 0.0f, 0 ,0.0f };
		m_playerHeight = { 0.0f, 5.0f, 0.0f };
		m_heightTime = 0.0f;
		m_fallTime = 0.0f;
		m_gravity = 0.0f;
		m_meshHitJudgement = false;
		m_timeSpeed = 1.0f;
		m_dashJudgement = true;
		m_dashCoolTime = 0.0f;
		m_jumpJudgement = true;
		m_respownJudgement = false;
		m_headWallMove = 0.0f;
		m_stopCamera = false;
		m_wireUseJudgement = false;
		m_playerHeadShakingJudgement = false;
		m_acceleration = { 0.0f, 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_position = { 0.0f, 0.0f, 0.0f };
		m_planPosition = { 0.0f, 0 ,0.0f };
		m_playerHeight = { 0.0f, STANDING_HEIGHT, 0.0f };
		m_cameraAngle = DirectX::SimpleMath::Vector2::Zero;
		m_world = DirectX::SimpleMath::Matrix::Identity;
		m_direction = DirectX::SimpleMath::Vector3::Zero;
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_wireMovePosition = DirectX::SimpleMath::Vector3::Zero;
		m_respawnPosition = DirectX::SimpleMath::Vector3::Zero;
		m_wallWalkNormalize = DirectX::SimpleMath::Vector3::Zero;
		m_acceleration = DirectX::SimpleMath::Vector3::Zero;
		m_wirePosition.clear();
		m_heightTime = 0.0f;
		m_fallTime = 0.0f;
		m_gravity = 0.0f;
		m_meshHitJudgement = false;
		m_timeSpeed = 1.0f;
		m_dashJudgement = true;
		m_dashCoolTime = 0.0f;
		m_jumpJudgement = true;
		m_respownJudgement = false;
		m_headWallMove = 0.0f;
		m_stopCamera = false;
		m_wireUseJudgement = false;
		m_playerHeadShakingJudgement = false;
	}

private:

	//		�����x
	const float STANDING_SPEED = 3.0f;

	//		�������x
	const float WALK_SPEED = 30.0f;

	//		�ō����x
	const float MAX_SPEED = 70.0f;

	//		���Ⴊ�ݑ��x 
	const float CROUCHING_SPEED = 30.0f;

	//		�v���C���[�̍���
	const float STANDING_HEIGHT = 4.0f;

	//		���Ⴊ�݂̍���
	const float CROUCHING_HEIGHT = 2.5f;

	//		�X���C�f�B���O�̍���
	const float SLIDING_HEIGHT = 2.5f;

	//		�������x
	const float DECELERATION_SPEED = 80.0f;

	//		�ǈړ����̍ō��ړ���
	//const float HEAD_MOVE_MAX = 3.0f;
	const float HEAD_MOVE_MAX = 1.0f;

	//		���̈ړ����x
	const float HEAD_MOVE_SPEED = 30.0f;

	//		�d�͂̉����x
	const float GRAVITATIONAL_ACCELERATION = 9.80665f;

public:

	/*
	*	�����̑���
	*
	*	@return ���x
	*/
	float GetWalkSpeed() { return WALK_SPEED; }

	/*
	*	�����̑���
	*
	*	@return ���x
	*/
	float GetDecelerationSpeed() { return DECELERATION_SPEED; }

	/*
	*	�ō����x
	* 
	*	@return ���x
	*/
	float GetMaxSpeed() { return MAX_SPEED; }

	/*
	*	���Ⴊ�݂̑���
	*
	*	@return ���x
	*/
	float GetCrouchingSpeed() { return CROUCHING_SPEED; }

	/*
	*	�����Ă���Ƃ��̍���
	*
	*	@return ����
	*/
	float GetStandingHeight() { return STANDING_HEIGHT; }

	/*
	*	���Ⴊ�ނƂ��̍���
	* 
	*	@return ����
	*/
	float GetCrouchingHeight() { return CROUCHING_HEIGHT; }

	/*
	*	�X���C�f�B���O�̍���
	* 
	*	@return ����
	*/
	float GetSlidngHeight() { return SLIDING_HEIGHT; }

	/*
	*	���̍ō��ړ��ʂ��󂯎��
	*
	*	@reutrn �ړ���
	*/
	inline constexpr float GetHeadMoveMAX() const noexcept { return HEAD_MOVE_MAX; }

	/*
	*	���̈ړ����x���󂯎��
	*
	*	@return �ړ����x
	*/
	inline constexpr float GetHeadMoveSpeed() const noexcept { return HEAD_MOVE_SPEED; }

	/*
	*	�d�͉����x���󂯎��
	* 
	*	@return �����x
	*/
	float GetGravitationalAcceleration() { return GRAVITATIONAL_ACCELERATION; }


private:

	//		�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_position;

	//		�ړ�����\��̍��W
	DirectX::SimpleMath::Vector3 m_planPosition;

	//		�v���C���[�̍���
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		�J�����̌����Ă���p�x
	DirectX::SimpleMath::Vector2 m_cameraAngle;

	//		��������
	float m_fallTime;

	//		�d��
	float m_gravity;

	//		���Ԃ̑��x
	float m_timeSpeed;

	//		�����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	//		���b�V���ɓ������Ă��邩�ǂ���
	bool m_meshHitJudgement;

	//		�����ϓ�����
	float m_heightTime;

	//		�v���C���[�̃��[���h���W
	DirectX::SimpleMath::Matrix m_world;

	//		�ړ��������
	DirectX::SimpleMath::Vector3 m_direction;

	//		���C���[�̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		�����x�N�g��
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	//		�ړ����郏�C���[�̍��W
	DirectX::SimpleMath::Vector3 m_wireMovePosition;

	//		���X�|�[�����W
	DirectX::SimpleMath::Vector3 m_respawnPosition;

	//		�_�b�V���̃N�[���^�C��
	float m_dashCoolTime;

	//		�_�b�V�����ł��邩�ǂ���
	bool m_dashJudgement;

	//		�W�����v�ł��邩�ǂ���
	bool m_jumpJudgement;

	//		���X�|�[�����邩�ǂ���
	bool m_respownJudgement;

	//		���̓���
	float m_headWallMove;

	//		�ǈړ����̖@��
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		�J�������~�����邩����
	bool m_stopCamera;

	//		���C���[���g�����Ƃ��ł��邩
	bool m_wireUseJudgement;

	//		�v���C���[�̓���h�炷���ǂ���
	bool m_playerHeadShakingJudgement;

public:

	/*
	*	�ǈړ����̖@�����󂯎��
	*
	*	@return �@��
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	�ǈړ����̖@����ݒ肷��
	*
	*	@param	(normalize)	�@��
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	���̓������󂯎��
	*
	*	@return �ړ���
	*/
	float GetHeadMove() { return m_headWallMove; }

	/*
	*	���̓�����ݒ肷��
	*
	*	@parma	�ړ���
	*/
	void SetHeadMove(float headWallMove) { m_headWallMove = headWallMove; }

	/*
	*	���[���h���W���󂯎��
	*
	*	@return ���[���h���W
	*/
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

	/*
	*	���[���h���W��ݒ肷��
	*
	*	@param	(world)	���[���h���W
	*/
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/*
	*	���W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	���W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	�ړ��\����W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetPlanPosition() { return m_planPosition; }

	/*
	*	�ړ��\����W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetPlanPosition(const DirectX::SimpleMath::Vector3& position) { m_planPosition = position; }

	/*
	*	�J�����̊p�x��ݒ肷��
	*
	*	@param	(angle)	�p�x
	*/
	void SetCameraAngle(DirectX::SimpleMath::Vector2 angle) { m_cameraAngle = angle; }

	/*
	*	�J�����̊p�x���󂯎��
	*
	*	@return �p�x
	*/
	const DirectX::SimpleMath::Vector2& GetCameraAngle() { return m_cameraAngle; }

	/*
	*	�v���C���[�̍�����ݒ肷��
	*
	*	@param	(position)	����
	*/
	void SetPlayerHeight(const DirectX::SimpleMath::Vector3& position) { m_playerHeight = position; }

	/*
	*	�v���C���[�̍������󂯎��
	*
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	�ړ�����������󂯎��
	*
	*	@return ����
	*/
	const DirectX::SimpleMath::Vector3& GetDirection() { return m_direction; }

	/*
	*	�ړ����������ݒ肷��
	*
	*	@param	(direction)	����
	*/
	void SetDirection(const DirectX::SimpleMath::Vector3& direction) { m_direction = direction; }

	/*
	*	�������Ԃ�ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetFallTime(const float& time) { m_fallTime = time; }

	/*
	*	�������Ԃ�ݒ肷��
	*
	*	@param	(time)	����
	*/
	float GetFallTime() { return m_fallTime; }

	/*
	*	���Ԃ̑��x���󂯎��
	*
	*	@return ���Ԃ̑��x
	*/
	const float& GetTimeSpeed() { return m_timeSpeed; }

	/*
	*	���Ԃ̑��x��ݒ肷��
	*
	*	@param	(speed)	���x
	*/
	void SetTimeSpeed(const float& speed) { m_timeSpeed = speed; }

	/*
	*	�����ϓ����Ԃ�ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetHeightTime(float time) { m_heightTime = time; }

	/*
	*	�����ϓ����Ԃ��󂯎��
	* 
	*	@return ����
	*/
	float GetHeightTime() { return m_heightTime; }

	/*
	*	�����x���󂯎��
	*
	*	@return �����x
	*/
	const DirectX::SimpleMath::Vector3& GetAcceleration() { return m_acceleration; }

	/*
	*	�����x��ݒ肷��
	*
	*	@param	(acceleration)	�����x
	*/
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }

	/*
	*	�d�͂�ݒ肷��
	*
	*	@param	(gravity)	�d��
	*/
	void SetGravity(float gravity) { m_gravity = gravity; }

	/*
	*	�d�͂��󂯎��
	*
	*	@return �d��
	*/
	float GetGravity() { return m_gravity; }

	/*
	*	���C���[�̍��W���󂯎��
	*
	*	@return ���W
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }

	/*
	*	���C���[�̍��W��ݒ肷��
	*
	*	@param	(position)	���W
	*/
	void SetWirePosition(const std::vector<DirectX::SimpleMath::Vector3>& position) { m_wirePosition = position; }

	/*
	*	�����x�N�g����ݒ肷��
	*
	*	@param	(velocity)
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& veloicty) { m_viewVelocity = veloicty; }

	/*
	*	�����x�N�g�����󂯎��
	* 
	*	@return �x�N�g��
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	���C���[�̈ړ����W���󂯎��
	*
	*	@return ���W
	*/
	const DirectX::SimpleMath::Vector3& GetWireMovePosition() { return m_wireMovePosition; }

	/*
	*	���C���[�̈ړ����W��ݒ肷��
	* 
	*	@param	(wirePosition)	���W
	*/
	void SetWireMovePosition(const DirectX::SimpleMath::Vector3& wirePosition) { m_wireMovePosition = wirePosition; }

	/*
	*	���X�|�[�����W���󂯎��
	* 
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector3 GetRespawnPosition() { return m_respawnPosition; }

	/*
	*	���X�|�[�����W��ݒ肷��
	* 
	*	@param	(position)	���W
	*/
	void SetRespawnPosition(DirectX::SimpleMath::Vector3 position) { m_respawnPosition = position; }

	/*
	*	�_�b�V�������邩�ǂ������f����
	*
	*	@return true : �_�b�V�������� �ł��� : �_�b�V�����ł��Ȃ�
	*/
	bool GetDashJudgement() { return m_dashJudgement; }

	/*
	*	�_�b�V�������Ă��邩�ݒ肷��
	*
	*	@param	(judgemnet)	true : �_�b�V���ł��� false : �_�b�V�����ł��Ȃ�
	*/
	void SetDashJudgement(bool judgement) { m_dashJudgement = judgement; }

	/*
	*	�W�����v�����邩�ǂ������f����
	*
	*	@return true : �W�����v�ł��� false : �W�����v�ł��Ȃ�
	*/
	bool GetJumpJudgement() { return m_jumpJudgement; }

	/*
	*	�W�����v�����Ă��邩�ݒ肷��
	*
	*	@param	(judgemnet)	true : �W�����v�ł��� false : �W�����v�ł��Ȃ�
	*/
	void SetJumpJudgement(bool judgement) { m_jumpJudgement = judgement; }

	/*
	*	���X�|�[�����邩�ǂ�����ݒ肷��
	*
	*	@param	(judgement)	true : ���X�|�[����ԁ@false : ���X�|�[����Ԃł͂Ȃ�
	*/
	void SetRespownJudgement(bool judgement) { m_respownJudgement = judgement; }

	/*
	*	���X�|�[�����邩�ǂ����󂯎��
	*
	*	@return true : ���X�|�[����ԁ@false : ���X�|�[����Ԃł͂Ȃ�
	*/
	bool GetRespownJugement() { return m_respownJudgement; }

	/*
*	�_�b�V���̃N�[���^�C�����󂯎��
*
*	@return ����
*/
	float GetDashCoolTime() { return m_dashCoolTime; }

	/*
	*	�_�b�V���̃N�[���^�C����ݒ肷��
	*
	*	@param	(time)	����
	*/
	void SetDashCoolTime(float time) { m_dashCoolTime = time; }

	/*
	*	�J�������~�����邩�ǂ����ݒ肷��
	* 
	*	@param	(judgement) true : ��~������ false : ��~���I������
	*/
	void SetCameraStop(bool judgement) { m_stopCamera = judgement; }
	
	/*
	*	�J�������~�����邩�ǂ����󂯎��
	* 
	*	@return true : ��~������ false : ��~���I������
	*/
	bool GetCameraStop() { return m_stopCamera; }

	/*
	*	���C���[���g�����Ƃ��ł��邩�ݒ肷��
	* 
	*	@param	(judgement)	true : true �g�p�ł��� false : �g�p�ł��Ȃ�
	*/
	void SetWireJudgement(bool judgement) { m_wireUseJudgement = judgement; }

	/*
	*	���C���[���g�����Ƃ��ł��邩�󂯎��
	* 
	*	@return true : true �g�p�ł��� false : �g�p�ł��Ȃ�
	*/
	bool GetWireJudgement() { return m_wireUseJudgement; }

	/*
	*	����h�炷���ǂ����ݒ肷��
	* 
	*	@param	(judgement) true : �h�炷 false : �h�炳�Ȃ�
	*/
	void SetHeadShakingJudgement(bool judgement) { m_playerHeadShakingJudgement = judgement; }

	/*
	*	����h�炷���ǂ����󂯎��
	* 
	*	@return true : �h�炷 false : �h�炳�Ȃ�
	*/
	bool GetHeadShakingJudgement() { return m_playerHeadShakingJudgement; }
};