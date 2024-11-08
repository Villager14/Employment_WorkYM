/*
* @file		TutorialScene.h
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/09/17
*/

#pragma once

#include "Scene/IScene.h"

#include "Game/TutorialScene/TutorialManager.h"

class SceneManager;

class TutorialScene : public IScene
{
public:

	//		�R���X�g���N�^
	TutorialScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TutorialScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

private:

	//		�`���[�g���A���}�l�[�W��
	std::unique_ptr<TutorialManager> m_tutorialManager;

};