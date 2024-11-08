/*
* @file		PlayerStart.h
* @brief	�v���C���[�̃X�^�[�g���
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerStart : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerStart(Player* player);

	//		�f�X�g���N�^
	~PlayerStart();

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
	
private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;
};
