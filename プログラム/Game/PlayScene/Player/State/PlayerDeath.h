/*
* @file		PlayerDeath.h
* @brief	�v���C���[�̎��S���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerDeath : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerDeath(Player* player);

	//		�f�X�g���N�^
	~PlayerDeath();

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

	//		��������
	void Deceleration();

	//		��ԑJ�ڔ��f
	void ChangeStateJudgement();
private:
	
	//		����
	const float DECELERATION_SPEED = 8.0f;

private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�o�ߎ���
	float m_time;

	//		�����̍���
	float m_firstHeight;

	//		��������
	float m_slowTime;

	//		�����̉����x
	DirectX::SimpleMath::Vector3 m_firstAcceleration;

	//		�����̏d��
	float m_firstGravity;
};
