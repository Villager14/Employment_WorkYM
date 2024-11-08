/*
* @file		ModelBones.h
* @brief	モデルのボーン
* @author	Morita
* @date		2024/08/26
*/

#pragma once

#include "BonInformation.h"

class ModelBones
{
public:

	//		コンストラクタ
	ModelBones(bool createHead = false, bool createGun = false);

	//		デストラクタ
	~ModelBones();

	//		初期化
	void Initialize();

	/*
	*	ボーンの作成
	*
	*	@param	(position)	座標
	*	@param	(length)	ボーンの長さ
	*	@paarm	(type)		自身のオブジェクトタイプ
	*	@param	(parent)	親オブジェクトタイプ
	*/
	void CrateBons(DirectX::SimpleMath::Vector3 position,
		float length, BonsType type,
		BonsType parent = BonsType::Empty);

	/*
*	ワールドを計算する(再帰処理)
*
*	@param	(world)		ワールド行列のポインタ
*	@param	(modelType)	モデルの種類
*/
	BonsType ParentProcess(DirectX::SimpleMath::Matrix* world, BonsType modelType);

	enum AnimationType
	{
		Start,			//		スタート
		Walk,			//		歩き
		Stay,			//		待機
		Jump,			//		ジャンプ
		Dash,			//		ダッシュ
		CrouchingStop,	//		しゃがみ停止
		CrouchingWalk,	//		しゃがみ移動
		Sliding,		//		スライディング
		WallWalk,		//		壁歩き
		WallJump,		//		壁ジャンプ
		WireJump,		//		ワイヤージャンプ
		Empty
	};

	std::vector<PlayerBonsInformation>* GetBonesInformation() { return &m_bonesInformation; }

private:

	std::vector<std::unique_ptr<DirectX::Model>> m_playerModel;

	//		角度
	float rotation;

	//		経過時間
	float m_elapsedTime;

	std::vector<PlayerBonsInformation> m_bonesInformation;

	//		アニメーションの種類
	AnimationType m_animationType;
};