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

#include "Effect/PostEffect/PostEffectFlag.h"

class FloorObject : public IFactory
{
public:

	//		コンストラクタ
	FloorObject(ObjectManager* objectManager);

	//		デストラクタ
	~FloorObject();

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
	Factory::Object GetObjectType() override { return Factory::Wall; }


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
	{ return m_postEffectFlag.get(); }

private:

	//		床モデル
	std::unique_ptr<DirectX::Model> m_floorModel;

	//		オブジェクトのメッシュ
	std::unique_ptr<ObjectMesh> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// テクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	ObjectManager* m_objectManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

public:

	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return インスタンス
	*/
	ObjectMesh* GetObjectMesh() const { return m_objectMesh.get(); }
};
