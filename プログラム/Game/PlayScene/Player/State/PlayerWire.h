/*
* @file		PlayerWire.h
* @brief	�v���C���[�̃��C���[���
* @author	Morita
* @date		2024/05/13
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWire : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerWire(Player* player);

	//		�f�X�g���N�^
	~PlayerWire();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�ړ�����
	void Move() override;

	//		�A�j���[�V�����̏���
	void Animation() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�ړ�����
	void MoveProcessing();

	//		��ԑJ�ڔ��f
	void ChangeStateJudgement();

	//		�����񂹂鎞�̏���
	void AttractProcess();

	//		��������
	void AccelerationProcess();

	//		��������
	void DecelerationProcess();

	//		�������̏���
	void FallProcess();

	//		������Ԃɂ��邩�ǂ���
	void FallJudgement();

	//		���x�̏���������
	void SpeedInitlaize();

private:
	
	//		����
	const float DECELERATION_SPEED = 8.0f;

	//		�ő呬�x
	const float MAX_SPEED = 150.0f;

	//		�����̊���
	const float ACCELERATION_RATE = 0.7f;

	//		�����̊������x
	const float ACCELERATION_RATE_SPEED = 3.0f;

private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�o�ߎ���
	float m_time;

	//		�����̍���
	float m_firstHeight;

	//		����
	float m_length;

	//		�������邩�ǂ���
	bool m_decelerationJudgement;

	//		�ړ�����
	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_acceleation;

	//		���x���󂯎��
	float m_speed;

	//		�������x
	float m_firstSpeed;

	//		�������̍ō����x
	float m_accelerationSpeed;

	//		�������f
	bool m_fallJudgement;

	//		�����ɓ��������ꍇ
	bool m_floorHitJudgement;

	//		�ǂɓ����������H
	bool m_wallHitJudgement;
};
