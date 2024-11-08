/*
* @file		UIRender.h
* @brief	UIの描画処理
* @author	Morita
* @date		2024/10/20
*/


#pragma once

#include "../../PostEffectManager.h"

#include "Common/DepthStencil.h"

#include "Library/Shader/UIRenderManager.h"

#include "../../IPostEffect.h"

class UIRender : public IPostEffect
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(manager)	ポインタのインスタンス
	*/
	UIRender(PostEffectManager* manager);

	//		デストラクタ
	~UIRender();

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

	//		レンダーターゲットを作成する
	void CreateRenderTarget();

private:

	//		ポストエフェクトマネージャーのポインタのインスタンス
	PostEffectManager* m_postEffectManager;

	//		レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;


	//		透明テクスチャ
	ID3D11ShaderResourceView* m_alphaEffectTexture;
};