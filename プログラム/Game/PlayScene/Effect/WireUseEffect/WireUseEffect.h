/*
* @file		WireUseEffect.h
* @brief	ワイヤー使用エフェクト
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../Billboard/BillboardEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WireUseEffect
{
public:

	//		コンストラクタ
	WireUseEffect(PlayerInformation* m_playerInformation);

	//		デストラクタ
	~WireUseEffect();

	//		初期化処理
	void Initialize(int size);

	/*
	*	更新処理
	*
	*	@param	(index)	要素数
	*/
	void Update(DirectX::SimpleMath::Vector3 position, int index);

	/*
	*	ビルボードの更新処理
	*
	*	@param	(cameraInformation)	カメラの情報
	*/
	void BillbordUpdate(PlayerCameraInformation* cameraInformation);

	/*
	*	描画処理
	*
	*	@param	(cameraVelocity)	視線ベクトル
	*/
	void Render(DirectX::SimpleMath::Vector3 position, int index,
		PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

	struct WireStatas
	{
		bool firstJudgement = true;
		bool sclaeChangeJudgement = true;
		bool resetFlag = false;
		float scale = 30.0f;
		float time = 0.0f;
		float maxScale = 0.0f;
	};

	/*
	*	ワイヤーを使った際のリセット処理
	* 
	*	@param	(index)	要素数
	*/
	void ResetProcess(int index);

private:
	//		ビルボードエフェクト
	std::unique_ptr<BillboardEffect> m_billboardEffect;

	//		プレイヤーの情報
	PlayerInformation* m_playerInformation;

	//		ワイヤーのステータス
	std::vector<WireStatas> m_wireStatas;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};
