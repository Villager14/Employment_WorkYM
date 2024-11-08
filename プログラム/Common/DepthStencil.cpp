#include "pch.h"

#include "DepthStencil.h"

DepthStencil::DepthStencil(DXGI_FORMAT foramat) noexcept
	:
	m_format(foramat),
	m_width(0),
	m_height(0)
{
}

void DepthStencil::SetDevice(_In_ ID3D11Device* device)
{
	//		現在のデバイスと同じ場合は処理をしない
	if (device == m_device.Get())
		return;

	//		デバイスの中身がある場合は削除する
	if (m_device)
	{
		ReleaseDevice();
	}

	UINT formatSupport = 0;

	if (FAILED(device->CheckFormatSupport(m_format, &formatSupport)))
	{
		throw std::runtime_error("ChackFormatSupport");
	}

	constexpr UINT32 required = D3D11_FORMAT_SUPPORT_TEXTURE2D |
		D3D11_FORMAT_SUPPORT_DEPTH_STENCIL;

	if ((formatSupport & required) != required)
	{
#ifdef _DEBUG
		char buff[128] = {};
		sprintf_s(buff, "DepthStencil : Device does not support the requestedformat(%u)!\n", m_format);
		OutputDebugStringA(buff);
#endif
		throw std::runtime_error("DepthStencil");
	}

	m_device = device;
}

void DepthStencil::SizeResources(size_t width, size_t height)
{
	if (width == m_width && height == m_height)
		return;

	if (m_width > UINT32_MAX || m_height > UINT32_MAX)
	{
		throw std::out_of_range("Invalid width / height");
	}

	if (!m_device)
		return;

	m_width = m_height = 0;

	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		m_format,
		static_cast<UINT>(width),
		static_cast<UINT>(height),
		1, 1,
		D3D11_BIND_DEPTH_STENCIL 
	);

	DX::ThrowIfFailed(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice()
		->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			m_texture2D.ReleaseAndGetAddressOf()
		));

	DX::ThrowIfFailed(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDevice()
		->CreateDepthStencilView(
		m_texture2D.Get(),
		nullptr,
		m_depthStencilView.ReleaseAndGetAddressOf()
	));
}

void DepthStencil::ReleaseDevice() noexcept
{
	m_depthStencilView.Reset();
	m_texture2D.Reset();
	m_device.Reset();
	m_width = m_height = 0;
}

void DepthStencil::SetWindow(const RECT& rect)
{
	auto const width = size_t(std::max<LONG>(rect.right - rect.left, 1));
	auto const height = size_t(std::max<LONG>(rect.bottom - rect.top, 1));

	SizeResources(width, height);

}
