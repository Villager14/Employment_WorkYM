/*
* @file		ObjectShaderManager.h
* @brief	�I�u�W�F�N�g�̃V�F�[�_�[�}�l�[�W��
* @author	Morita
* @date		2024/09/24
*/

#pragma once

class ObjectShaderManager
{
public:

	enum ShaderType
	{
		None			= 0b000,	//		�g���Ă��Ȃ�
		PixelShader		= 1 << 0,	//		�s�N�Z���V�F�[�_
		VertexShader	= 1 << 1,	//		���_�V�F�[�_�[
		GeometryShader	= 1 << 2,	//		�W�I���g���V�F�[�_�[
	};

public:

	//		�R���X�g���N�^
	ObjectShaderManager();

	//		�f�X�g���N�^
	~ObjectShaderManager();

	/*
	*	�e�N�X�`���̓ǂݍ���
	*
	*	@param	(path)	�t�@�C���p�X
	*/
	void LoadTexture(const wchar_t* path);

	//		�V�F�[�_���Z�b�g����
	void SetShader(ID3D11DeviceContext1* context);

	/*
	*	�R���X�g�o�b�t�@�̍쐻
	* 
	*	@param	(obj)	�R���X�g�o�b�t�@
	*/
	template<typename UIType>
	void CreateConstBuffer(const UIType& obj);

	/*
	*	�R���X�g�o�b�t�@�̍X�V
	* 
	*	@param	(data)	�R���X�g�o�b�t�@�̃f�[�^
	*/
	template<typename UIType>
	void UpdateBuffer(const UIType& data);

private:

	//		�e�N�X�`��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		�萔�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	//		�g�p���Ă���V�F�[�_�[
	int m_useShader;

public:

	/*
	*	�V�F�[�_�[�̓ǂݍ���
	*
	*	@param	(type)		�V�F�[�_�[�̎��
	*	@param	(filePath)	�t�@�C���p�X
	*/
	void LoadShader(ShaderType type, const wchar_t* filePath);

	/*
	*	�s�N�Z���V�F�[�_�[���󂯎��
	* 
	*	@return �V�F�[�_�[�̃|�C���^���󂯎��
	*/
	Microsoft::WRL::ComPtr<ID3D11PixelShader>* GetPixelShader() { return &m_pixelShader; }


	/*
	*	���_�V�F�[�_�[���󂯎��
	* 
	*	@return �V�F�[�_�[�̃|�C���^���󂯎��
	*/
	Microsoft::WRL::ComPtr<ID3D11VertexShader>* GetVertexShader() { return &m_vertexShader; }

	/*
	*	�W�I���g���V�F�[�_�[���󂯎��
	* 
	*	@return �V�F�[�_�[�̃|�C���^���󂯎��
	*/
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>* GetGeometryShader() { return &m_geometryShader; }
};

template<typename UIType>
inline void ObjectShaderManager::CreateConstBuffer(const UIType& obj)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(obj));	// �m�ۂ���T�C�Y�i16�̔{���Őݒ肷��j
	// GPU (�ǂݎ���p) �� CPU (�������ݐ�p) �̗�������A�N�Z�X�ł��郊�\�[�X
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// �萔�o�b�t�@�Ƃ��Ĉ���
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPU�����e��ύX�ł���悤�ɂ���
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
	//		GPU���萔�o�b�t�@�ɑ΂��ăA�N�Z�X���s��Ȃ��悤�ɂ���
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);

	*static_cast<UIType*>(mappedResource.pData) = data;

	//		GPU���萔�o�b�t�@�ɑ΂��ẴA�N�Z�X��������
	context->Unmap(m_constantBuffer.Get(), 0);
}
