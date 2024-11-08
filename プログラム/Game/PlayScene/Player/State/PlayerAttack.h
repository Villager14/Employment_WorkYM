/*
* @file		PlayerAttack.h
* @brief	�v���C���[�̍U�����
* @author	Morita
* @date		2024/04/30
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerAttack
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerAttack(Player* player);

	//		�f�X�g���N�^
	~PlayerAttack();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�ړ�����
	void Move();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		��������
	void Deceleration();
	
private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	float m_time;
};
