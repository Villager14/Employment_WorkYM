/*
* @file		ScreenEffectManager.h
* @brief	スクリーンエフェクトのマネージャー
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

	//		コンストラクタ
	ScreenEffectManager(Scene scene, GameManager* gameManager);

	//		デストラクタ
	~ScreenEffectManager();

	//		初期化処理
	void Initialize();

	//		アップデート
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		レンダーテクスチャを作成する
	void CreateRenderTexture();

	//		レンダーターゲットを変更する
	void ChangeRenderTarget();

	//		初期のレンダーターゲットにする
	void FirstRenderTarget();

private:

	//		現在のシーン
	Scene m_scene;

	//		背景の色
	DirectX::XMVECTORF32 m_backColor;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		サンプラー(一部を取り出す物)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	//		シェーダーリソース
	ID3D11ShaderResourceView* m_shaderResouceView;

	//		プレイヤーモデルテクスチャ
	std::unique_ptr<PlayerModelTexture> m_playerModelTexture;

	//		ゲームマネージャー
	GameManager* m_gameManager;

	std::unique_ptr<UIRenderManager> m_playerTexture;
};
