/*
* @file		BillboardEffect.h
* @brief	ビルボートエフェクト
* @author	Morita
* @date		2024/06/10
*
* @授業内資料を参考
*/

#pragma once

class BillboardEffect
{
public:

	struct  ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};

public:
	//		コンストラクタ
	BillboardEffect();

	//		デストラクタ
	~BillboardEffect();

	/*
	*	テクスチャの読み込み
	* 
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path);

	//		エフェクトの作製
	void Create();

	//		描画処理
	void Render(DirectX::SimpleMath::Vector3 position);

	/*
	*	ビルボードの作製
	* 
	*	@param	(target)	ターゲット
	*	@param	(eye)		視線
	*	@param	(up)		
	*/
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up
	);

	void CreateShader();

private:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//		テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		ビルボード
	DirectX::SimpleMath::Matrix m_billboard;

	//		カメラの座標
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		カメラのターゲット
	DirectX::SimpleMath::Vector3 m_cameraTarget;

	//		インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//		ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBuffer;

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//		スケール
	float m_scale;

public:

	/*
	*	スケールを設定する
	* 
	*	@parma	(scale)	スケール
	*/
	void SetScale(float scale) { m_scale = scale; }
};
