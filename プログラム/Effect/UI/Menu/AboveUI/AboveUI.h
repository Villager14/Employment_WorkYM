/*
* @file		AboveUI.h
* @brief	UI�̏㏸����
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class AboveUI
{
public:

	//		�R���X�g���N�^
	AboveUI();

	//		�f�X�g���N�^
	~AboveUI();

	//		����������
	void Initialize();

	//		�V�F�[�_�[UI�̍쐻
	void CreateShader();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		��ʃX�P�[��
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		��]��
		DirectX::SimpleMath::Vector4 time;					//		����
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		���W
		DirectX::SimpleMath::Vector2 scale;							//		�T�C�Y
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		�e�N�X�`��
		DirectX::SimpleMath::Vector2 textureSize;					//		�e�N�X�`���T�C�Y
		float time = 0.0f;											//		����
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER;
	};

	enum UIType
	{
		AudioSelect,
		OptionSelect,
		GamePlaySelect,
		Slide,
		AudioTitle,
		OptionTitle,
		GamePlayTitle,
		SliderBack,
		MastarVolume,
		BGMVolume,
		SoundEffectVolume,
		MasterKnob,
		BGMKnob,
		SoundEffectKnob,
		MenuClose,
		Exit,
		FOV,
		FOVKnob,
		Mouse,
		MouseKnob,

		Empty,
	};

public:

	//		�I�[�f�B�IUI�̍��W
	const DirectX::SimpleMath::Vector2 AUDIO_POSITION = { -380.0f, -200.0f };

	//		�Q�[���v���CUI�̍��W
	const DirectX::SimpleMath::Vector2 GAME_PLAY_POSITION = { -380.0f, 40.0f };

	//		�I�v�V����UI�̍��W
	const DirectX::SimpleMath::Vector2 OPTION_POSITION = { -380.0f, -80.0f };

	//		SettingTitleUI�̍��W
	const DirectX::SimpleMath::Vector2 SETTING_TITLE_POSITION = { 200.0f, -240.0f };

	//		SlideBackUI�̍��W
	const DirectX::SimpleMath::Vector2 SLIDE_BACK_POSITION = { 200.0f, -100.0f };

	//		MasterVolumeUI�̍��W
	const DirectX::SimpleMath::Vector2 MASTER_VOLUME_POSITION = { 70.0f, -160.0f };

	//		BGMUI�̍��W
	const DirectX::SimpleMath::Vector2 BGM_POSITION = { 25.0f, -10.0f };

	//		SoundEffectUI�̍��W
	const DirectX::SimpleMath::Vector2 SOUND_EFFECT_POSITION = { 150.0f, 140.0f };

	//		MasterKnobUI�̍��W
	const DirectX::SimpleMath::Vector2 MASTER_K_NOB_POSITION = { 480.0f, -100.0f };

	//		BGM�̂܂ݍ��WY
	const float BGM_K_NOB_Y_POSITION = 50.0f;

	//		SoundEffecr�̂܂ݍ��WY
	const float SOUND_K_NOB_Y_POSITION = 200.0f;

	//		�ő�܂ݍ��W
	const float MAX_K_NOB = 480.0f;

	//		�ŏ��܂ݍ��W
	const float MIN_K_NOB = -81.0f;

	//		ExitUI�̍��W
	const DirectX::SimpleMath::Vector2 EXIT_POSITION = { 200.0f, 50.0f };

	//		FovUI�̍��W
	const DirectX::SimpleMath::Vector2 FOV_POSITION = { -70.0f, -160.0f };

	//		FOVKnobUI�̍��W
	const DirectX::SimpleMath::Vector2 FOV_K_NOB_POSITION = { -80.0f, -100.0f };

	//		MouseUI�̍��W
	const DirectX::SimpleMath::Vector2 MOUSE_POSITION = { 90.0f, -10.0f };

	//		MouseKnobUI�̍��W
	const DirectX::SimpleMath::Vector2 MOUSE_K_NOB_POSITION = { 200.0f, 50.0f };

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
	*	@param	(path)		�e�N�X�`���̃p�X
	*	@param	(position)	���W
	*	@param	(size)		�T�C�Y
	*	@param	(type)		UI�̎��
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	/*
	*	�`�揈��
	*
	*	@param	(type)	�`�悷��UI�̎��
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};