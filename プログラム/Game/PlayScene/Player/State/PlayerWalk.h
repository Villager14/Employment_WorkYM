/*
* @file		PlayerWalk.h
* @brief	�v���C���[�̕������
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWalk : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerWalk(Player* player);

	//		�f�X�g���N�^
	~PlayerWalk();

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

	//		��������
	void AccelerationProcess();

private:
	//		�����̑��x
	const float ACCELERATION_SPEED = 70.0f;

private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�����̍���
	float m_firstHeight;

	//		���x
	float m_speed;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;

	//		�������邩�ǂ���
	bool m_accelerationJudgement;
};
