/*
* @file		AboveUI.h
* @brief	UIの上昇処理
* @author	Morita
* @date		2024/07/09
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class AboveUI
{
public:

	//		コンストラクタ
	AboveUI();

	//		デストラクタ
	~AboveUI();

	//		初期化処理
	void Initialize();

	//		シェーダーUIの作製
	void CreateShader();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 time;					//		時間
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;						//		座標
		DirectX::SimpleMath::Vector2 scale;							//		サイズ
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;	//		テクスチャ
		DirectX::SimpleMath::Vector2 textureSize;					//		テクスチャサイズ
		float time = 0.0f;											//		時間
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

	//		オーディオUIの座標
	const DirectX::SimpleMath::Vector2 AUDIO_POSITION = { -380.0f, -200.0f };

	//		ゲームプレイUIの座標
	const DirectX::SimpleMath::Vector2 GAME_PLAY_POSITION = { -380.0f, 40.0f };

	//		オプションUIの座標
	const DirectX::SimpleMath::Vector2 OPTION_POSITION = { -380.0f, -80.0f };

	//		SettingTitleUIの座標
	const DirectX::SimpleMath::Vector2 SETTING_TITLE_POSITION = { 200.0f, -240.0f };

	//		SlideBackUIの座標
	const DirectX::SimpleMath::Vector2 SLIDE_BACK_POSITION = { 200.0f, -100.0f };

	//		MasterVolumeUIの座標
	const DirectX::SimpleMath::Vector2 MASTER_VOLUME_POSITION = { 70.0f, -160.0f };

	//		BGMUIの座標
	const DirectX::SimpleMath::Vector2 BGM_POSITION = { 25.0f, -10.0f };

	//		SoundEffectUIの座標
	const DirectX::SimpleMath::Vector2 SOUND_EFFECT_POSITION = { 150.0f, 140.0f };

	//		MasterKnobUIの座標
	const DirectX::SimpleMath::Vector2 MASTER_K_NOB_POSITION = { 480.0f, -100.0f };

	//		BGMのつまみ座標Y
	const float BGM_K_NOB_Y_POSITION = 50.0f;

	//		SoundEffecrのつまみ座標Y
	const float SOUND_K_NOB_Y_POSITION = 200.0f;

	//		最大つまみ座標
	const float MAX_K_NOB = 480.0f;

	//		最小つまみ座標
	const float MIN_K_NOB = -81.0f;

	//		ExitUIの座標
	const DirectX::SimpleMath::Vector2 EXIT_POSITION = { 200.0f, 50.0f };

	//		FovUIの座標
	const DirectX::SimpleMath::Vector2 FOV_POSITION = { -70.0f, -160.0f };

	//		FOVKnobUIの座標
	const DirectX::SimpleMath::Vector2 FOV_K_NOB_POSITION = { -80.0f, -100.0f };

	//		MouseUIの座標
	const DirectX::SimpleMath::Vector2 MOUSE_POSITION = { 90.0f, -10.0f };

	//		MouseKnobUIの座標
	const DirectX::SimpleMath::Vector2 MOUSE_K_NOB_POSITION = { 200.0f, 50.0f };

private:

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_shader;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		シェーダーの情報
	std::unordered_map<UIType, UIInformation> m_shaderInformation;


public:

	/*
	*	UIの情報を作成する
	*
	*	@param	(path)		テクスチャのパス
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*	@param	(type)		UIの種類
	*/
	void CreateUIInformation(const wchar_t* path,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		UIType type,
		CENTER_POINT centerPoint = CENTER_POINT::MIDDLE_CENTER);

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};