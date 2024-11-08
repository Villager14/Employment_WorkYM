/*
* @file		FloorObject.h
* @brief	床オブジェクトの描画
* @author	Morita
* @date		2024/04/04
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Shader/ObjectShaderManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class WallObject : public IFactory
{
public:

	//		コンストラクタ
	WallObject(ObjectManager* objectManager);

	//		デストラクタ
	~WallObject();

	/*
	*	初期化処理
	*
	*	@param	(position)	座標
	*/
	void Initialize(ObjectInformation information) override;

	//		更新処理
	void Update() override;

	//	描画処理
	void Render(PostEffectFlag::Flag flag, PostEffectObjectShader* postEffectObjectShader)override ;

	//		終了処理
	void Finalize() override;

	/*
	*	オブジェクトタイプを受け取る
	*
	*	@return　オブジェクトタイプ
	*/
	Factory::Object GetObjectType() override { return Factory::Wall; }


	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return メッシュの情報
	*/
	ObjectMesh* GetObjectMesh(int index) override {
		UNREFERENCED_PARAMETER(index);
		return m_objectMesh.get(); }


	//		モデルの描画
	void LoadModel(ObjectInformation information);

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

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 Time;				//		時間
	};

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_wallModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		オブジェクトマネージャーのインスタンスのポインタ
	ObjectManager* m_objectManager;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		オブジェクトシェーダー
	std::unique_ptr<ObjectShaderManager> m_objectShader;

	//		時間
	float m_time;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
