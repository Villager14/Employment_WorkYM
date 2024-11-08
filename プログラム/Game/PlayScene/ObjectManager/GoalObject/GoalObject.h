/*
* @file		GoalObject.h
* @brief	ゴールオブジェクトの描画
* @author	Morita
* @date		2024/05/27
*/
#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class GoalObject : public IFactory
{
public:

	//		コンストラクタ
	GoalObject(ObjectManager* objectManager);

	//		デストラクタ
	~GoalObject();

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
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)override;

	//		終了処理
	void Finalize() override;

	/*
	*	オブジェクトタイプを受け取る
	*
	*	@return　オブジェクトタイプ
	*/
	Factory::Object GetObjectType() override { return Factory::Goal; }


	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return メッシュの情報
	*/
	ObjectMesh* GetObjectMesh(int index) override {
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }

	/*
	*	ポストエフェクトフラグ
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}

public:

	const float GOAL_ROTATION_SPEED = 10.0f;

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_goalModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// テクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	//		回転量
	DirectX::SimpleMath::Vector3 m_rotation;

	ObjectManager* m_objectManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
