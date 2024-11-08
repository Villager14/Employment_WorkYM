/*
* @file		BillboardEffect.cpp
* @brief	ビルボートエフェクト
* @author	Morita
* @date		2024/06/10
*
* @授業内資料を参考
*/

#include "pch.h"

#include "BillboardEffect.h"

#include <WICTextureLoader.h>
#include "Common/BinaryFile.h"


const std::vector<D3D11_INPUT_ELEMENT_DESC> BillboardEffect::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,																			D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(DirectX::SimpleMath::Vector3),										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0},
};


BillboardEffect::BillboardEffect()
{
}

BillboardEffect::~BillboardEffect()
{
}

void BillboardEffect::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	DirectX::CreateWICTextureFromFile(
		LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());

	m_texture = texture;
}

void BillboardEffect::Create()
{
	CreateShader();

	//		プリミティブバッチの作製
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext());
}

void BillboardEffect::Render(DirectX::SimpleMath::Vector3 position)
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

	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	context->IASetInputLayout(m_inputLayout.Get());

	//		コンストバッファの更新
	ConstBuffer cbuff;
	DirectX::SimpleMath::Matrix world;

	cbuff.matWorld = m_billboard.Transpose();

	cbuff.matView = LibrarySingleton::GetInstance()->GetView().Transpose();
	cbuff.matProj = LibrarySingleton::GetInstance()->GetProj().Transpose();

	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);

	context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11Buffer* cb[1] = { m_constBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	DirectX::VertexPositionColorTexture m_vertices{};

	DirectX::VertexPositionColorTexture v;

	v.position = position;
	v.color = { 1,1,1,1 };
	v.textureCoordinate = DirectX::XMFLOAT2(m_scale, 0.0f);

	m_vertices = v;

	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices, 1);
	m_batch->End();

	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

void BillboardEffect::CreateBillboard(DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 up)
{
	m_billboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, eye - target, up);

	DirectX::SimpleMath::Matrix rot = DirectX::SimpleMath::Matrix::Identity;
	rot._11 = -1;
	rot._33 = -1;

	m_cameraPosition = eye;
	m_cameraTarget = target;
	m_billboard = rot * m_billboard;
}

void BillboardEffect::CreateShader()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	 m_pixelShader = LibrarySingleton::GetInstance()->CreatePSShader(L"Resources/Shader/EffectBillboard/EffectBillboardPS.cso");
	 m_geometryShader = LibrarySingleton::GetInstance()->CreateGSShader(L"Resources/Shader/EffectBillboard/EffectBillboardGS.cso");
	 BinaryFile VSData = LibrarySingleton::GetInstance()->CreateVSShader(L"Resources/Shader/EffectBillboard/EffectBillboardVS.cso", &m_vertexShader);

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf()
	);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constBuffer);
}
