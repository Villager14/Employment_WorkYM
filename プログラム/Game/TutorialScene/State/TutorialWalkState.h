/*
* @file		TutorialWalkState.h
* @brief	�`���[�g���A������
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "../ITutorialManager.h"

class TutorialManager;

class TutorialWalkState : public ITutorialManager
{
public:

	//		�R���X�g���N�^
	TutorialWalkState(TutorialManager* tutorialManager);

	//		�f�X�g���N�^
	~TutorialWalkState();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		�`���[�g���A���}�l�[�W���̃C���X�^���X�̃|�C���^
	TutorialManager* m_tutorialManager;


};
