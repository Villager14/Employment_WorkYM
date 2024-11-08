/*
* @file		PlayerWallWalk.cpp
* @brief	�v���C���[�̕Ǖ������
* @author	Morita
* @date		2024/04/30
*/
#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWallWalk : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerWallWalk(Player* player);

	//		�f�X�g���N�^
	~PlayerWallWalk();

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

	//		���̓���
	void HeadMove();

private:

	//		�����̑���
	const float WORK_ACCERARATION_SPEED = 0.8f;

	//		�ǈړ����̓��̍���
	const float HEAD_WALLWALK_HEIGHT = 2.5f;


private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�x���V�e�B
	DirectX::SimpleMath::Vector3 m_velocity;

	DirectX::SimpleMath::Vector2 m_moveAngle;


	float m_heightMove;

};
