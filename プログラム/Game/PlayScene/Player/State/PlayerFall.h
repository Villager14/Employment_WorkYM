/*
* @file		PlayerFall.h
* @brief	�v���C���[�̗������
* @author	Morita
* @date		2024/07/19
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerFall : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerFall(Player* player);

	//		�f�X�g���N�^
	~PlayerFall();

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

	//		��ԑJ�ڔ��f
	void ChangeStateJudgement();
	
	void MoveProcess();

private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	float m_firstHeight;

	float m_speed;

	bool m_rayHitJudgement;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;

	//		�J�����̃}�g���b�N�X���
	DirectX::SimpleMath::Matrix m_cameraMatrix;
};
