/*
* @file		TitleScene.h
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/TitleScene/TitleSelectManager.h"

class SceneManager;

class TitleScene : public IScene
{
public:

	//		�R���X�g���N�^
	TitleScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~TitleScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	void CreateView();

	void CreateProj();

private:
	//		�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	SceneManager* m_sceneManager;

	//		�^�C�g���I���}�l�[�W���[
	std::unique_ptr<TitleSelectManager> m_titleSelectManager;
};
