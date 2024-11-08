/*
* @file		Slider.h
* @brief	�X���C�_�[�̏���
* @author	Morita
* @date		2024/07/10
*/
#pragma once

#include "Library/Shader/UIRenderManager.h"

class Slider
{
public:

	//		�R���X�g���N�^
	Slider();

	//		�f�X�g���N�^
	~Slider();

	//		����������
	void Initialize();
public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 time;					//		����
		DirectX::SimpleMath::Vector4 slideVal;
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;		//		���W
		DirectX::SimpleMath::Vector2 scale;			//		�T�C�Y
		float slideVal = 0.0f;						//		�X���C�_�[�̒l
	};

	enum UIType
	{
		MastarVolum,
		BGMVolum,
		SoundEffect,
		FOV,
		Mouse,

		Empty,
	};

public:

	//		MastarVolumUI�̍��W
	const DirectX::SimpleMath::Vector2 MASTER_VOLUM_POSITION = { 200.0f, -100.0f };

	//		BGMVolumUI�̍��W
	const DirectX::SimpleMath::Vector2 BGM_VOLUM_POSITION = { 200.0f, 50.0f };

	//		SoundEffectUI�̍��W
	const DirectX::SimpleMath::Vector2 SOUND_EFFECT_POSITION = { 200.0f, 200.0f };

	//		FOVUI�̍��W
	const DirectX::SimpleMath::Vector2 FOV_POSITION = { 200.0f, -100.0f };

	//		MouseUI�̍��W
	const DirectX::SimpleMath::Vector2 MOUSE_POSITION = { 200.0f, 50.0f };

private:

	//		�V�F�[�_�[
	std::unique_ptr<UIRenderManager> m_shader;

	//		�R���X�g�o�b�t�@
	ConstBuffer m_constBuffer;

	//		�V�F�[�_�[�̏��
	std::unordered_map<UIType, UIInformation> m_shaderInformation;

public:

	/*
	*	UI�̏����쐬����
	*
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*	@param	(slideVal)	�X���C�_�[�̒l
	*	@param	(type)		UI�̎��
	*/
	void CreateUIInformation(
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		float slideVal,
		UIType type);

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};