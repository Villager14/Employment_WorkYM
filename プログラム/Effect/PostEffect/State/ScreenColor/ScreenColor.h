/*
* @file		ScreenColor.h
* @brief	スクリーンの色
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "../../PostEffectManager.h"

#include "../../PostEffectObjectShader.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"


class ScreenColor : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	ScreenColor(PostEffectManager* postEffectManager);

	//		デストラクタ
	~ScreenColor();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		オブジェクト描画
	void ObjectRender() override;

	//		ポストエフェクト後の描画
	void PostEffectRender() override;

	//		終了処理
	void Filanize() override;

	//		テクスチャを受け取る
	ID3D11ShaderResourceView* GetTexture() override { return nullptr; };

	//		赤い画面
	bool RedScreen();

	//		グレー画面
	bool GrayScreen();

	//		レンダーターゲットを作成する
	void CreateRenderTarget();

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;			//		画面スケール
		DirectX::SimpleMath::Matrix  rotationMatrix;		//		回転量
		float elasedTime = 0.0f;							//		経過時間
		DirectX::SimpleMath::Vector3 pad;
		DirectX::SimpleMath::Vector4 color;					//		色
	};

private:

	//		ポストエフェクトマネージャーのポインタのインスタンス
	PostEffectManager* m_postEffectManager;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	//		フォグテクスチャ
	ID3D11ShaderResourceView* m_colorTexture;

	//		深度の描画
	std::unique_ptr<UIRenderManager> m_depthShaderView;

	//		フォグシェーダー定数バッファ
	ConstBuffer m_constBuffer;

	//		経過時間
	float m_elapsedTime;

	//		フラグ
	bool m_menuOpenJudgement;

};