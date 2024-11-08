/*
* @file		PostEffectManager.h
* @brief	ポストエフェクトマネージャー
* @author	Morita
* @date		2024/10/01
*/

#pragma once

#include "Common/RenderTexture.h"

#include "Library/Shader/StandardShader.h"

#include "PostEffectCommonProcess.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "PostEffectObjectShader.h"

#include "IPostEffect.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/Menu/MenuInformation.h"

class Bler;

class PostEffectManager
{
public:

	//		コンストラクタ
	PostEffectManager(GameManager* gameManager, MenuInformation* menuInformation);

	//		デストラクタ
	~PostEffectManager();

	//		初期化処理
	void Initialize(DirectX::XMVECTORF32 color);

	//		更新処理
	void Update(PostEffectFlag::Flag flag);

	//		描画処理
	void Render(PostEffectFlag::Flag flag);

	//		最終描画処理
	void RastRender(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

	//		サンプラーの作製
	void CreateSampler();

	//		レンダーターゲットの変更
	ID3D11ShaderResourceView* ChangeRenderTarget(DX::RenderTexture* renderTarget,
		ID3D11DepthStencilView* depthStencil);

	//		レンダーターゲットを基に戻す
	void ResetRenderTarget();

	//		レンダーテクスチャの描画
	void RenderTextureView();

public:

	enum UIType
	{
		RastTexture,
		UITexture,
	};

private:

	//		ポストエフェクトの共通処理
	std::unique_ptr<PostEffectCommonProcess> m_commonProcess;

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

	//		サンプラー(一部を取り出す物)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		メニューの情報
	MenuInformation* m_menuInformation;

	ID3D11ShaderResourceView* m_shaderResourceView;

	//		ブラーの処理
	std::unique_ptr<Bler> m_bler;

	//		ポストエフェクト
	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>> m_postEffectProcess;

	//		背景色
	DirectX::XMVECTORF32 m_backColor;

	//		背景描画色
	DirectX::XMVECTORF32 m_backRenderColor;

	//		オブジェクトに対するシェーダー
	std::unique_ptr<PostEffectObjectShader> m_objectShader;

public:

	/*
	*	スタンダードシェーダーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	ブラーの処理を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	Bler* GetBler() { return m_bler.get(); }

	/*
	*	背景色を受け取る
	*
	*  @return 背景色
	*/
	DirectX::XMVECTORF32 GetBackColor() { return m_backColor; };

	/*
	*	描画背景色を受け取る
	*
	*	@return 描画背景色
	*/
	DirectX::XMVECTORF32 GetBackRenderColor() { return m_backRenderColor; }

	/*
	*	描画背景色を設定する
	*
	*	@param	(背景色) 色
	*/
	void SetBackRenderColor(DirectX::XMVECTORF32 color) { m_backRenderColor = color; }

	/*
	*	共通処理を受け取る
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectCommonProcess* GetCommonProcess() { return m_commonProcess.get(); }

	/*
	*	オブジェクトシェーダーを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectObjectShader* GetPostObjectShader() { return m_objectShader.get(); }

	/*
	*	シェーダーリソースビューを受け取る
	* 
	*	@return	ポインタ
	*/
	ID3D11ShaderResourceView* GetShaderTexture() { return m_shaderResourceView; }

	/*
	*	ゲームマネージャを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	メニューの情報を受け取る
	*	
	*	@return インスタンスのポインタ
	*/
	MenuInformation* GetMenuInformation() { return m_menuInformation; }

	void SetShaderTexture(ID3D11ShaderResourceView* texture) { m_shaderResourceView = texture; }

	std::unordered_map<PostEffectFlag::Flag, std::unique_ptr<IPostEffect>>* GetPostEffectProcess() { return &m_postEffectProcess; }
};
