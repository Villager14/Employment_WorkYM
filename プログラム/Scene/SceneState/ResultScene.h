/*
* @file		ResultScene.h
* @brief	���U���g�V�[��
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "Scene/IScene.h"

#include "../SceneManager.h"

#include "Game/ResultScene/ResultManager.h"

class SceneManager;

class ResultScene : public IScene
{
public:

	/*
	*	�R���X�g���N�^
	* 
	*	@param	(sceneManager)	�C���X�^���X�̃|�C���^	
	*/
	ResultScene(SceneManager* sceneManager);

	//		�f�X�g���N�^
	~ResultScene();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	//		�`�揈��
	void Render() override;

	//		�I������
	void Finalize() override;

	//		�v���W�F�N�V�����s����쐬
	void CreateProj();

	//		�r���[�s��̍쐻
	void CreateView();

private:
	//		�V�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	SceneManager* m_sceneManager;

	//		���U���g�}�l�[�W���[
	std::unique_ptr<ResultManager> m_resultManager;

	float m_score;

};