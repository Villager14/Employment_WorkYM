/*
* @file		FloorObject.h
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Factory/IFactory.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WireObject : public IFactory
{
public:

	//		コンストラクタ
	WireObject(ObjectManager* objectManager);

	//		デストラクタ
	~WireObject();

	/*
	*	初期化処理
	*
	*	@param	(position)	座標
	*/
	void Initialize(ObjectInformation information) override;

	//		更新処理
	void Update() override;

	/*
	*	描画処理
	*
	*	@param	(drawMesh)	メッシュ描画のインスタンスのポインタ
	*/
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader) override;

	//		終了処理
	void Finalize() override;

	/*
*	オブジェクトタイプを受け取る
*
*	@return　オブジェクトタイプ
*/
	Factory::Object GetObjectType() override { return Factory::Wire; }


	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return メッシュの情報
	*/
	ObjectMesh* GetObjectMesh(int index) override {
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get();
	}

	/*
	*	ポストエフェクトフラグ
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}

	//		デバックの描画
	void DebugRender();

	//		羽の描画
	void WingRender(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader);

private:
	//		羽座標1
	DirectX::SimpleMath::Vector3 WING_POSITION_0 = { 4.0f, 5.0f, 3.6f };
	//		羽座標2
	DirectX::SimpleMath::Vector3 WING_POSITION_1 = { 4.2f, 5.0f, -3.0f };
	//		羽座標3
	DirectX::SimpleMath::Vector3 WING_POSITION_2 = { -4.0f, 5.0f, 3.6f };
	//		羽座標4
	DirectX::SimpleMath::Vector3 WING_POSITION_3 = { -4.2f, 5.0f, -3.0f };

	//		ワイヤーの範囲
	float WIRE_RANGE = 120.0f;

	//		羽の回転速度
	float WING_ROTATION_SPEED = 10.0f;

private:

	//		ワイヤーモデル
	std::unique_ptr<DirectX::Model> m_wireModel;

	//		ワイヤーの範囲モデル
	std::unique_ptr<DirectX::Model> m_wireRangeModel;

	//		羽オブジェクト
	std::unique_ptr<DirectX::Model> m_wingModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		デバック用のワールド座標
	DirectX::SimpleMath::Matrix m_debugWorld;
	
	//		回転
	float m_rotation;

	//		羽の座標
	std::vector<DirectX::SimpleMath::Vector3> m_wingPosition;

	//		オブジェクトマネージャー
	ObjectManager* m_objectManager;

	//		番号
	int m_number;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;
};
