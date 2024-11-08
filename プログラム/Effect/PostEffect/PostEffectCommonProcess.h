/*
* @file		PostEffectCommonProcess.h
* @brief	ポストエフェクト共通処理
* @author	Morita
* @date		2024/10/07
*/

#pragma once

#include "Common/RenderTexture.h"

class PostEffectManager;

class PostEffectCommonProcess
{
public:

	//		コンストラクタ
	PostEffectCommonProcess(PostEffectManager* postEffectManager);

	//		デストラクタ
	~PostEffectCommonProcess();

	//		レンダーテクスチャの作製
	/*
	*	レンダーテクスチャの作製
	* 
	*	@param	(size)	画面のサイズ
	*	@return レンダーテクスチャのインスタンス
	*/
	std::unique_ptr<DX::RenderTexture> CreateRenderTexture(DirectX::SimpleMath::Vector2 size =
		LibrarySingleton::GetInstance()->GetScreenSize());

	/*
	*	テクスチャの作製
	* 
	*	@param	(index)	要素数
	*/
	void CreateTexture(int index);

private:

	//		ポストエフェクトマネージャー
	PostEffectManager* m_postEffectManager;
};