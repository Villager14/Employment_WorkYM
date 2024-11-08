/*
* @file		ScreenEffectManager.h
* @brief	�X�N���[���G�t�F�N�g�̃}�l�[�W���[
* @author	Morita
* @date		2024/05/22
*/

#pragma once

#include "Common/RenderTexture.h"

#include "Game/ResultScene/ScreenEffect/PlayerModelTexture.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/Menu/MenuInformation.h"

#include "Library/Shader/UIRenderManager.h"

class ScreenEffectManager
{
public:

	enum Scene
	{
		PlayScene,
		ResultScene,
	};

public:

	//		�R���X�g���N�^
	ScreenEffectManager(Scene scene, GameManager* gameManager);

	//		�f�X�g���N�^
	~ScreenEffectManager();

	//		����������
	void Initialize();

	//		�A�b�v�f�[�g
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

	//		�����_�[�e�N�X�`�����쐬����
	void CreateRenderTexture();

	//		�����_�[�^�[�Q�b�g��ύX����
	void ChangeRenderTarget();

	//		�����̃����_�[�^�[�Q�b�g�ɂ���
	void FirstRenderTarget();

private:

	//		���݂̃V�[��
	Scene m_scene;

	//		�w�i�̐F
	DirectX::XMVECTORF32 m_backColor;

	//		�����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		�T���v���[(�ꕔ�����o����)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	//		�V�F�[�_�[���\�[�X
	ID3D11ShaderResourceView* m_shaderResouceView;

	//		�v���C���[���f���e�N�X�`��
	std::unique_ptr<PlayerModelTexture> m_playerModelTexture;

	//		�Q�[���}�l�[�W���[
	GameManager* m_gameManager;

	std::unique_ptr<UIRenderManager> m_playerTexture;
};
