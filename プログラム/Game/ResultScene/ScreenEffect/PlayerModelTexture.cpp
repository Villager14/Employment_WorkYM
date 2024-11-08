/*
* @file		PlayerModelTexture.h
* @brief	プレイヤーモデルのテクスチャ化
* @author	Morita
* @date		2024/06/28
*/

#include "pch.h"

#include "PlayerModelTexture.h"
#include "Common/BinaryFile.h"
#include "Library/Library.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> PlayerModelTexture::INPUT_LAYOUT =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	0,										D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,	sizeof(DirectX::SimpleMath::Vector3),	D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	   0,	sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4),	D3D11_INPUT_PER_VERTEX_DATA, 0},
};

PlayerModelTexture::PlayerModelTexture()
	:
	m_rotationMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_baseScale(0.0f),
	m_grayJudgement(false)
{

}

PlayerModelTexture::~PlayerModelTexture()
{
}

//		シェーダーを読み込む
void PlayerModelTexture::Create(
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale)
{
	m_position = position;
	m_baseScale = m_scale = scale;

	//		シェーダーの作製
	CreateShader();
}

void PlayerModelTexture::Update()
{
}

void PlayerModelTexture::Render(ID3D11ShaderResourceView* shaderResouceView)
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(2)),
		DirectX::SimpleMath::Vector4(m_position.x, m_position.y,
		LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y),
		DirectX::SimpleMath::Vector2(1.0f,1.0f))
	};

	//		シェーダに渡す追加のバッファを作成する
	ConstBuffer cbuff;
	cbuff.rotationMatrix = m_rotationMatrix.Transpose();
	cbuff.windowSize = DirectX::SimpleMath::Vector4(LibrarySingleton::GetInstance()->GetScreenSize().x,
		LibrarySingleton::GetInstance()->GetScreenSize().y, 1, 1);

	//		受け渡し用バッファ
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//		シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//		画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { LibrarySingleton::GetInstance()->GetCommonState()->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//		半透明描画指定
	ID3D11BlendState* blendestate = LibrarySingleton::GetInstance()->GetCommonState()->NonPremultiplied();

	//		透明判定処理
	context->OMSetBlendState(blendestate, nullptr, 0xFFFFFFFF);

	//		深度バッファに書き込み参照
	context->OMSetDepthStencilState(LibrarySingleton::GetInstance()->GetCommonState()->DepthDefault(), 0);

	//		カリングは左回り
	context->RSSetState(LibrarySingleton::GetInstance()->GetCommonState()->CullNone());

	//		シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometoryShaer.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//		ピクセルシェーダにテクスチャを登録する
	context->PSSetShaderResources(0, 1, &shaderResouceView);

	//		インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//		板ポリゴンを描画
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Begin();
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	LibrarySingleton::GetInstance()->GetVertexPositionColorTexture()->End();

	//		シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

//		シェーダーの読み込み
void PlayerModelTexture::CreateShader()
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//		コンパイルされたシェーダファイルを読み込み
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shader/PlayerModelTexture/PlayerModelTexturePS.cso");
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shader/PlayerModelTexture/PlayerModelTextureVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shader/PlayerModelTexture/PlayerModelTextureGS.cso");

	//		インプットレイアウトの作製
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	//		頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		//		エラー
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);
		return;
	}

	//		ジオメトリックシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometoryShaer.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader failed", NULL, MB_OK);

		return;
	}

	//		ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreatePixelShader Failde", NULL, MB_OK);
		return;
	}

	//		シェーダにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}
