/*
* @file		PlayerDash.h
* @brief	�v���C���[�̃_�b�V��
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerDash : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	*
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerDash(Player* player);

	//		�f�X�g���N�^
	~PlayerDash();

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

	//		��������
	void Acceratation();

	void Deceleration();

	//		��ԑJ�ڔ��f
	void ChangeStateJudgement();

private:

	//		�_�b�V���̍ō����x
	const float DASH_MAX_SPEED = 110.0f;

private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		����
	float m_acceraration;

	//		����
	float m_deceleration;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;

	//		�ړ�����
	DirectX::SimpleMath::Vector3 m_direction;

	//		�����̑���
	float m_firstSpeed;

	//		�����̍���
	float m_firstHeight;
};
