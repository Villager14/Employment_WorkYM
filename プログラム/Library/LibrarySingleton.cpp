/*
* @file		LibraySingleton.cpp
* @brief	ライブラリシングルトン
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "LibrarySingleton.h"


std::unique_ptr<LibrarySingleton> LibrarySingleton::m_library = nullptr;

LibrarySingleton::LibrarySingleton()
	:
	m_debugViewJudgment(false)
{
	//		デバイスリソースを生成する
	m_device = std::make_unique<DX::DeviceResources>();
}

LibrarySingleton::~LibrarySingleton()
{
}

LibrarySingleton* const LibrarySingleton::GetInstance()
{
	if (m_library == nullptr)
	{
		m_library.reset(new LibrarySingleton());
	}

	return m_library.get();
}

void LibrarySingleton::Initialize()
{
	//		コモンステートを生成する
	m_commonState = std::make_unique<DirectX::CommonStates>(m_device->GetD3DDevice());

	//		スプライトバッチを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_device->GetD3DDeviceContext());

	//		スプライトフォントを生成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device->GetD3DDevice(), L"Resources/Font/SegoeUI_18.spritefont");

	//		バーテックポジションカラーを生成する
	m_vertexPositionColor = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>
		(m_device->GetD3DDeviceContext());

	//		バーテックスポジションカラーテクスチャを生成する
	m_vertexPositionColorTexture = std::make_unique
		<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>
		(m_device->GetD3DDeviceContext());

	//		エフェクトファクトリーを生成する
	m_effectFactory = std::make_unique
		<DirectX::EffectFactory>
		(m_device->GetD3DDevice());
}

float LibrarySingleton::Random(float min, float max)
{
	//		ランダムデバイスを作成
	std::random_device seed;
	std::default_random_engine  engine(seed());

	//		数字の範囲を指定する
	std::uniform_real_distribution<> dist(min, max);

	return static_cast<float>(dist(engine));
}

Microsoft::WRL::ComPtr<ID3D11PixelShader> LibrarySingleton::CreatePSShader(const wchar_t* path)
{
		BinaryFile PSData = BinaryFile::LoadFile(path);

		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixselShsder;

		//		ピクセルシェーダ作成
		if (FAILED(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
			->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL,
				pixselShsder.ReleaseAndGetAddressOf())))
		{
			MessageBox(0, L"CreatePixelShader Failed", NULL, MB_OK);

			return nullptr;
		}

		return pixselShsder;
}

BinaryFile LibrarySingleton::CreateVSShader(const wchar_t* path, Microsoft::WRL::ComPtr<ID3D11VertexShader>* vsshader)
{
	BinaryFile VSData = BinaryFile::LoadFile(path);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;

	//		ピクセルシェーダ作成
	if (FAILED(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL,
			vertexShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateVertexShader Failed", NULL, MB_OK);

		return VSData;
	}

	*vsshader = vertexShader.Get();

	return VSData;
}

Microsoft::WRL::ComPtr<ID3D11GeometryShader> LibrarySingleton::CreateGSShader(const wchar_t* path)
{
	BinaryFile GSData = BinaryFile::LoadFile(path);

	Microsoft::WRL::ComPtr<ID3D11GeometryShader> geometoryShader;

	//		ピクセルシェーダ作成
	if (FAILED(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice()
		->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL,
			geometoryShader.ReleaseAndGetAddressOf())))
	{
		MessageBox(0, L"CreateGeometryShader Failed", NULL, MB_OK);

		return nullptr;
	}

	return geometoryShader;
}
