#pragma once

class DepthStencil
{
public:

	explicit DepthStencil(DXGI_FORMAT foramat) noexcept;

	DepthStencil(DepthStencil&&) = default;
	DepthStencil& operator = (DepthStencil&&) = default;

	DepthStencil(DepthStencil const&) = default;
	DepthStencil& operator = (DepthStencil const&) = default;

	void SetDevice(_In_ ID3D11Device* device);

	void SizeResources(size_t width, size_t height);

	void ReleaseDevice() noexcept;

	void SetWindow(const RECT& rect);

	ID3D11Texture2D* GetTexture2D() const noexcept { return m_texture2D.Get(); }
	ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_depthStencilView.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	DXGI_FORMAT m_format;

	size_t m_width;
	size_t m_height;
};