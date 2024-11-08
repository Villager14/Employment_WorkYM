/*
* @file		EffectShaderManager.h
* @brief	エフェクトシェーダーマネージャ
* @author	Morita
* @date		2024/10/14
*/

#pragma once

#include <WICTextureLoader.h>

#include "Common/BinaryFile.h"

template<typename ConstBuffer>
class EffectShaderManager
{
public:

	EffectShaderManager() 
	{
		//		プリミティブバッチの作製
		m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());

		INPUT_LAYOUT =
		{
			{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,																			D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(DirectX::SimpleMath::Vector3),										D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
	};

	~EffectShaderManager() {};

	/*
	*	テクスチャの読み込み
	*
	*	@param	(path)	ファイルパス
	*/
	void LoadTexture(const wchar_t* path);

	void ChangeTexture(ID3D11ShaderResourceView* texture, int index);

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLoadTexture(const wchar_t* path);

	//		シェーダーの作製
	void CreateShader(
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath);

	/*
	*	ビルボードの作製
	*
	*	@param	(target)	ターゲット
	*	@param	(eye)		視線
	*	@param	(up)
	*/
	DirectX::SimpleMath::Matrix CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up
	);


	//		作成
	void Create(
		const wchar_t* texpath,
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath,
		const ConstBuffer& obj,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 scale);

	void CrateConstBuffer(const ConstBuffer& obj);

	void Render(const ConstBuffer& obj);

	void RenderProcedure();

	ConstBuffer GetConstBuffer() { return m_constBuffer; }

private:
	//		インプットレイアウト
	std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//		テクスチャ
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	//		インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//		ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		定数バッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//		ビルボード
	DirectX::SimpleMath::Matrix m_billboard;

	//		バッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector2 m_scale;

	ConstBuffer m_constBuffer;

public:

	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	DirectX::SimpleMath::Matrix GetBillbord() { return m_billboard; }
};

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture.push_back(texture);
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::ChangeTexture(ID3D11ShaderResourceView* texture, int index)
{
	m_texture[index] = texture;
}

template<typename ConstBuffer>
inline Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> EffectShaderManager<ConstBuffer>::GetLoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());

	return texture;
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::CreateShader(const wchar_t* vsPath, const wchar_t* gsPath, const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_pixelShader = LibrarySingleton::GetInstance()->CreatePSShader(psPath);
	m_geometryShader = LibrarySingleton::GetInstance()->CreateGSShader(gsPath);
	BinaryFile VSData = LibrarySingleton::GetInstance()->CreateVSShader(vsPath, &m_vertexShader);

	//		インプットレイアウトの作製
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf()
	);
}

template<typename ConstBuffer>
inline DirectX::SimpleMath::Matrix EffectShaderManager<ConstBuffer>::CreateBillboard(
			DirectX::SimpleMath::Vector3 target,
			DirectX::SimpleMath::Vector3 eye,
			DirectX::SimpleMath::Vector3 up)
{
	m_billboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, eye - target, up);

	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	//m_cameraPosition = eye;
	//m_cameraTarget = target;
	m_billboard = rot * m_billboard;

	return m_billboard;
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::Create(
		const wchar_t* texpath,
		const wchar_t* vsPath,
		const wchar_t* gsPath,
		const wchar_t* psPath,
		const ConstBuffer& obj,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 scale)
{
	m_position = position;
	m_scale = scale;

		//		テクスチャの読み込み
	LoadTexture(texpath);

	//		シェーダーの作製
	CreateShader(vsPath, gsPath, psPath);

	//		コンストバッファの作製
	CrateConstBuffer(obj);
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::CrateConstBuffer(const ConstBuffer& obj)
{
	UNREFERENCED_PARAMETER(obj);

	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::Render(const ConstBuffer& obj)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	for (int i = 0; i < m_texture.size(); ++i)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	context->IASetInputLayout(m_inputLayout.Get());

	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &obj, 0, 0);

	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	DirectX::VertexPositionColorTexture m_vertices{};

	DirectX::VertexPositionColorTexture v;

	v.position = m_position;
	v.color = { 1,1,1,1 };
	v.textureCoordinate = DirectX::XMFLOAT2(m_scale.x, m_scale.y);

	m_vertices = v;

	m_batch->Begin();

	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices, 1);

	m_batch->End();

	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

template<typename ConstBuffer>
inline void EffectShaderManager<ConstBuffer>::RenderProcedure()
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto state = LibrarySingleton::GetInstance()->GetCommonState();

	//		画像用サンプラの登録
	ID3D11SamplerState* samPler[1] = {
		state->LinearWrap() };
	context->PSSetSamplers(0, 1, samPler);

	//半透明描画指定
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(state->DepthDefault(), 0);

	//		カリング左
	context->RSSetState(state->CullNone());

	m_constBuffer.matView = LibrarySingleton::GetInstance()->GetView().Transpose();
	m_constBuffer.matProj = LibrarySingleton::GetInstance()->GetProj().Transpose();
	m_constBuffer.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
}
