/*
* @file		Slider.h
* @brief	スライダーの処理
* @author	Morita
* @date		2024/07/10
*/
#pragma once

#include "Library/Shader/UIRenderManager.h"

class Slider
{
public:

	//		コンストラクタ
	Slider();

	//		デストラクタ
	~Slider();

	//		初期化処理
	void Initialize();
public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		DirectX::SimpleMath::Vector4 time;					//		時間
		DirectX::SimpleMath::Vector4 slideVal;
	};

	struct UIInformation
	{
		DirectX::SimpleMath::Vector2 position;		//		座標
		DirectX::SimpleMath::Vector2 scale;			//		サイズ
		float slideVal = 0.0f;						//		スライダーの値
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

	//		MastarVolumUIの座標
	const DirectX::SimpleMath::Vector2 MASTER_VOLUM_POSITION = { 200.0f, -100.0f };

	//		BGMVolumUIの座標
	const DirectX::SimpleMath::Vector2 BGM_VOLUM_POSITION = { 200.0f, 50.0f };

	//		SoundEffectUIの座標
	const DirectX::SimpleMath::Vector2 SOUND_EFFECT_POSITION = { 200.0f, 200.0f };

	//		FOVUIの座標
	const DirectX::SimpleMath::Vector2 FOV_POSITION = { 200.0f, -100.0f };

	//		MouseUIの座標
	const DirectX::SimpleMath::Vector2 MOUSE_POSITION = { 200.0f, 50.0f };

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
	*	@param	(position)	座標
	*	@param	(size)		サイズ
	*	@param	(slideVal)	スライダーの値
	*	@param	(type)		UIの種類
	*/
	void CreateUIInformation(
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 size,
		float slideVal,
		UIType type);

	/*
	*	描画処理
	*
	*	@param	(type)	描画するUIの種類
	*/
	void Render(UIType type, float time);

	std::unordered_map<UIType, UIInformation>* GetInformation() { return &m_shaderInformation; }
};