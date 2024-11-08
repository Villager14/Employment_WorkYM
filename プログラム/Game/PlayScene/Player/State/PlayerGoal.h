/*
* @file		PlayerGoal.h
* @brief	�v���C���[�S�[�����
* @author	Morita
* @date		2024/05/27
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerGoal : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerGoal(Player* player);

	//		�f�X�g���N�^
	~PlayerGoal();

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
	
	//		�V�[����؂�ւ��邩�ǂ���
	void ChangeSceneJudgement();


private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�����̍���
	float m_firstHeight;
};
