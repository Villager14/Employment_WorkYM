/*
* @file		TutorialInformation.h
* @brief	�`���[�g���A�����
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "../PlayScene/Player/Player.h"

class TutorialInformation
{
public:

	//		�R���X�g���N�^
	TutorialInformation()
	:
		m_player{nullptr}
	{};

	//		�f�X�g���N�^
	~TutorialInformation() {};

	//		����������
	void Initialize(Player* player)
	{
		m_player = player;
	}

public:


private:

	//		�v���C���[
	Player* m_player;

public:

	/*
	*	�v���C���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	Player* GetPlayer() { return m_player; }

};