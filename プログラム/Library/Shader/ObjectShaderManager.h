/*
* @file		ObjectShaderManager.h
* @brief	オブジェクトのシェーダーマネージャ
* @author	Morita
* @date		2024/09/24
*/

#pragma once

class ObjectShaderManager
{
public:

	enum ShaderType
	{
		None			= 0b000,	//		使っていない
		PixelShader		= 1 << 0,	//		ピクセルシェーダ
		VertexShader	= 1 << 1,	//		頂点シェーダー
		GeometryShader	= 1 << 2,	//		ジオメトリシェーダー
	};

public:

	//		コンストラクタ
	ObjectShaderManager();

	//		デストラクタ
	~ObjectShaderManager();

	/*
	*	テクスチャの読み込み
	*
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path);

	//		シェーダをセットする
	void SetShader(ID3D11DeviceContext1* context);

	/*
	*	コンストバッファの作製
	* 
	*	@param	(obj)	コンストバッファ
	*/
	template<typename UIType>
	void CreateConstBuffer(const UIType& obj);

	/*
	*	コンストバッファの更新
	* 
	*	@param	(data)	コンストバッファのデータ
	*/
	template<typename UIType>
	void UpdateBuffer(const UIType& data);

private:

	//		テクスチャ
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//		使用しているシェーダー
	int m_useShader;

public:

	/*
	*	シェーダーの読み込み
	*
	*	@param	(type)		シェーダーの種類
	*	@param	(filePath)	ファイルパス
	*/
	void LoadShader(ShaderType type, const wchar_t* filePath);

	/*
	*	ピクセルシェーダーを受け取る
	* 
	*	@return シェーダーのポインタを受け取る
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader>* GetPixelShader() { return &m_pixelShader; }


	/*
	*	頂点シェーダーを受け取る
	* 
	*	@return シェーダーのポインタを受け取る
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>* GetVertexShader() { return &m_vertexShader; }

	/*
	*	ジオメトリシェーダーを受け取る
	* 
	*	@return シェーダーのポインタを受け取る
	*/
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>* GetGeometryShader() { return &m_geometryShader; }
};

template<typename UIType>
inline void ObjectShaderManager::CreateConstBuffer(const UIType& obj)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(obj));	// 確保するサイズ（16の倍数で設定する）
	// GPU (読み取り専用) と CPU (書き込み専用) の両方からアクセスできるリソース
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 定数バッファとして扱う
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUが内容を変更できるようにする
	DX::ThrowIfFailed(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice()->CreateBuffer(&bufferDesc,
			nullptr, m_constantBuffer.ReleaseAndGetAddressOf()));
}

template<typename UIType>
inline void ObjectShaderManager::UpdateBuffer(const UIType& data)
{
	auto context = LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//		GPUが定数バッファに対してアクセスを行わないようにする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);

	*static_cast<UIType*>(mappedResource.pData) = data;

	//		GPUが定数バッファに対してのアクセスを許可する
	context->Unmap(m_constantBuffer.Get(), 0);
}
