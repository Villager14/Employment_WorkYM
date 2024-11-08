/*
* @file		PlayerSlowTime.cpp
* @brief	�v���C���[�̒ᑬ���ԏ��
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerSlowTime : public IPlayer
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(player) ��ԊǗ��N���X�̃|�C���^
	*/
	PlayerSlowTime(Player* player);

	//		�f�X�g���N�^
	~PlayerSlowTime();

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

private:
	//		��ԊǗ��N���X�̃|�C���^
	Player* m_player;

	//		�ړ�����
	DirectX::SimpleMath::Vector3 m_direction;

	//		�J�����̃}�g���b�N�X���
	DirectX::SimpleMath::Matrix m_cameraMatrix;

	//		����
	float m_time;

	//		�����̍���
	float m_firstHeight;

};
