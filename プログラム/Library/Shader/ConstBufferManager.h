

#pragma once

class ConstBufferManager
{
public:

	//		コンストラクタ
	ConstBufferManager();

	//		デストラクタ
	~ConstBufferManager();

	template<typename UIType>
	void CreateConstBuffer(const UIType& obj);

	template<typename UIType>
	void UpdateBuffer(const UIType& data);

	void BindBuffer();
private:

	//		バッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
};

template<typename UIType>
inline void ConstBufferManager::CreateConstBuffer(const UIType& obj)
{
	UNREFERENCED_PARAMETER(obj);

	UIType buffer = {};

	//		シェーダにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(buffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateBuffer(&bd, nullptr, &m_buffer);
}

template<typename UIType>
inline void ConstBufferManager::UpdateBuffer(const UIType& data)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()
				   ->GetD3DDeviceContext();

	context->UpdateSubresource(m_buffer.Get(), 0, NULL, &data, 0, 0);
}


