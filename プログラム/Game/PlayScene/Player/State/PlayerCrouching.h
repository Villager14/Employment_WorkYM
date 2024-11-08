/*
* @file		class PlayerCrouching.h
* @brief	�v���C���[�̂��Ⴊ�ݏ��
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerCrouching : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerCrouching(Player* player);

	//		�f�X�g���N�^
	~PlayerCrouching();

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

	//		���x����
	void SpeedProcessing();
	
private:

private:

	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�������Ⴊ�ݍ���
	float m_firstHeight;

	//		�L�[�������Ă��邩�ǂ���
	bool m_keyInputJudgement;
};
