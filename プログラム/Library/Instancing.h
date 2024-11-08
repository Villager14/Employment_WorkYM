/*
* @file		Instancing.h
* @brief	インスタンシング
* @author	Morita
* @date		2024/10/04
* 
* 参考 : http://maverickproj.web.fc2.com/d3d11_18.html
*/

#pragma once

#include "Library/Mesh/LeadMesh.h"

class Instancing
{
public:
	//		コンストラクタ
	Instancing();

	//		デストラクタ
	~Instancing();
	
	/*
	*	初期化処理
	* 
	*	@param	(描画数)
	*/
	void Initilaize(int count, const wchar_t* psPath, const wchar_t* vsPath);

	//		描画処理
	void Render();


	//		メッシュの情報
	void MeshInformation(const wchar_t* path);

	/*
	*	テクスチャの読み込み
	*
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path, int index = 0);

private:
	//		シェーダーの読み込み
	void ShaderRead(const wchar_t* psPath, const wchar_t* vsPath);

public:

	//		頂点
	std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	
	//		頂点シェーダー用のバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;

	//		頂点インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexIndexBuffer;

	//		頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;


	//		入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		メッシュの読み込み
	std::unique_ptr<LeadMesh> m_learMesh;

	//		描画する数
	int m_count;

	//		メッシュの頂点の数
	int m_meshIndexCount;

	//		頂点の数
	int m_vertexCount;

	//		頂点インデックス
	std::vector<int> m_vertexIndex;

	//		頂点情報
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	float time;
};