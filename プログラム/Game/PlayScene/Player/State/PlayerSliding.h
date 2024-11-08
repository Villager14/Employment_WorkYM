/*
* @file		PlayerSliding.h
* @brief	�v���C���[�̃X���C�f�B���O
* @author	Morita
* @date		2024/04/17
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerSliding : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerSliding(Player* player);
	//		�f�X�g���N�^

	~PlayerSliding();

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

	//		�⓹���ǂ������f����
	void SlopeJudgement();

private:

	//		�X���C�f�B���O�̉���
	const float SLIDING_ACCELERATION_SPEED = 20.0f;

	//		�X���C�f�B���O�̒ǉ�����
	const float INTIAL_VELOCITY = 5.0f;

private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�����̍���
	float m_firstHeight;

	//		�������x
	float m_decelerationSpeed;

	//		�������x
	float m_firstSpeed;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;

	//		���x
	float m_speed;

	//		��������
	float m_accelerationTime;

	//		�₩�ǂ���
	bool m_slopeJudgement;

	DirectX::SimpleMath::Vector2 m_slidingVelocity;
};
