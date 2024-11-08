/*
* @file		PlayerWallJump.h
* @brief	�v���C���[�̕ǃW�����v
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWallJump : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerWallJump(Player* player);

	//		�f�X�g���N�^
	~PlayerWallJump();

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

	//		�W�����v�̏���
	void Jump();

	//		��ԑJ�ڂ����邩�ǂ���
	void ChangeStateJudgement();

private:

	//		�W�����v�̑���
	const float JUMP_SPEED = 2.0f;

	//		�W�����v�̍ō����x
	const float JUMP_MAX_SPEED = 20.0f;

	//		�W�����v�̍Œᑬ�x
	const float JUMP_MIN_SPEED = 2.0f;

private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;

	//		�����̍���
	float m_firstHeight;

	//		��~������Ԃ���W�����v�������ǂ���
	bool m_stopJump;

	//		���C�̏����̔��f
	bool m_rayprocessJudgement;

	//		���C�ɓ����������ǂ������f����
	bool m_rayHitJudgement;
};
