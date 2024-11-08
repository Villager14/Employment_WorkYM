/*
* @file		EffectManager.h
* @brief	エフェクトマネージャー
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "WireUseEffect/WireUseEffect.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

#include "../Player/PlayerInformation.h"

#include "Game/PlayScene/ObjectManager/WireObject/WireObjectInformation.h"

#include "Effect/Effect/DigitalRain/DegitalRain.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/Effect/Signboard/SignboardEffect.h"

class EffectManager
{
public:

	//		コンストラクタ
	EffectManager(PlayerInformation* playerInformation, PlayerCameraInformation* cameraInformation);

	//		デストラクタ
	~EffectManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update();

	/*
	*	描画処理
	*
	*	@param	(cameraVelocity)	視線ベクトル
	*/
	void Render(PostEffectFlag::Flag flag);

	//		終了処理
	void Finalize();

private:

	//		ワイヤーエフェクト
	std::unique_ptr<WireUseEffect> m_wireUseEffect;

	//		プレイヤーの情報
	PlayerInformation* m_playerInformation;

	//		ワイヤーの情報
	std::vector<WireObjectInformation>* m_wireInformation;

	//		デジタル雨
	std::unique_ptr<DegitalRain> m_degitalRain;

	//		カメラの情報
	PlayerCameraInformation* m_cameraInformation;

	//		看板
	std::unique_ptr<SignboardEffect> m_signboardEffect;

public:

	void SetWireInformation(std::vector<WireObjectInformation>* wire) { m_wireInformation = wire; }

	//		カメラの情報
	PlayerCameraInformation* GetCameraInformation() { return m_cameraInformation; }

	PlayerInformation* GetPlayerInformation() { return m_playerInformation; }
};
