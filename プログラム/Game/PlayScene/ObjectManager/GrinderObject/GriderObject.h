/*
* @file		GriderObject.h
* @brief	破砕オブジェクトの描画
* @author	Morita
* @date		2024/08/09
*/

#pragma once

#include "Library/Mesh/ObjectMesh.h"

#include "Library/Mesh/DrawMesh.h"

#include "Library/Factory/IFactory.h"

#include "Library/Factory/Factory.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class GriderObject : public IFactory
{
public:

	//		コンストラクタ
	GriderObject(ObjectManager* objectManager);

	//		デストラクタ
	~GriderObject();

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
	*	オブジェクトメッシュの作製
	* 
	*	@param	(position)	座標
	*/
	void CreateObjectMesh();

	/*
	*	オブジェクトタイプを受け取る
	* 
	*	@return　オブジェクトタイプ
	*/
	Factory::Object GetObjectType() override { return Factory::Grider; }


	/*
	*	オブジェクトメッシュを受け取る
	*
	*	@return メッシュの情報
	*/
	ObjectMesh* GetObjectMesh(int index) override { return m_objectMesh[index].get(); }

	/*
	*	ポストエフェクトフラグ
	*
	*	@return インスタンスのポインタ
	*/
	PostEffectFlag* GetPostEffectFlag() override
	{
		return m_postEffectFlag.get();
	}
private:

	//		破砕オブジェクトモデル（回転）
	std::unique_ptr<DirectX::Model> m_griderRotationObject;

	//		破砕オブジェクトモデル（土台）
	std::unique_ptr<DirectX::Model> m_griderObject;

	//		オブジェクトのメッシュ
	std::vector<std::unique_ptr<ObjectMesh>> m_objectMesh;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		回転量
	DirectX::SimpleMath::Quaternion m_rotation;

	float m_rog;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_floorPS;

	// テクスチャハンドル 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	ObjectManager* m_objectManager;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;
};
