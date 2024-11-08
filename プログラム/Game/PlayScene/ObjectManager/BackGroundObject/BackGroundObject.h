/*
* @file		BackGroundObject.cpp
* @brief	背景オブジェクト
* @author	Morita
* @date		2024/05/23
*/

#include "BackGroundObjectInformation.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Instancing.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"
class BackGroundObject
{
public:

	//		コンストラクタ
	BackGroundObject(ObjectManager* objectManager);

	//		デストラクタ
	~BackGroundObject();

	//		初期化処理
	void Initialize(std::vector<ObjectMesh*> mesh,
		const std::vector<DirectX::SimpleMath::Vector3>& m_wirePosition);

	//		更新処理
	void Update();

	//		描画オブジェクト
	void Render(PostEffectFlag::Flag flag,
				PostEffectObjectShader* objectShader);

	//		終了処理
	void Finalize();

private:

	std::unique_ptr<DirectX::Model> m_backGroundModel;

	//		ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	//		情報
	std::unique_ptr<BackGroundObjectInformation> m_information;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		バッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	//		ゲームマネージャー
	ObjectManager* m_objectManager;

	//		インスタンシング描画
	std::unique_ptr<Instancing> m_instancing;

	//		ポストエフェクトフラグ
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

public:

	/*
	*	ポストエフェクトフラグ
	* 
	*	@return インスタンスのポインタ
	*/
	PostEffectFlag* GetPostEffectFlag() { return m_postEffectFlag.get(); }
};
