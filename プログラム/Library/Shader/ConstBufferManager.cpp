

#include "pch.h"

#include "ConstBufferManager.h"

ConstBufferManager::ConstBufferManager()
{

}

ConstBufferManager::~ConstBufferManager()
{
}

void ConstBufferManager::BindBuffer()
{
	auto context = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//		シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_buffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
}


