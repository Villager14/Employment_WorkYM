/*
* @file		BillboardEffect.h
* @brief	�r���{�[�g�G�t�F�N�g
* @author	Morita
* @date		2024/06/10
*
* @���Ɠ��������Q�l
*/

#pragma once

class BillboardEffect
{
public:

	struct  ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};

public:
	//		�R���X�g���N�^
	BillboardEffect();

	//		�f�X�g���N�^
	~BillboardEffect();

	/*
	*	�e�N�X�`���̓ǂݍ���
	* 
	*	@param	(path)	�t�@�C���p�X
	*/
	void LoadTexture(const wchar_t* path);

	//		�G�t�F�N�g�̍쐻
	void Create();

	//		�`�揈��
	void Render(DirectX::SimpleMath::Vector3 position);

	/*
	*	�r���{�[�h�̍쐻
	* 
	*	@param	(target)	�^�[�Q�b�g
	*	@param	(eye)		����
	*	@param	(up)		
	*/
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up
	);

	void CreateShader();

private:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//		�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//		�r���{�[�h
	DirectX::SimpleMath::Matrix m_billboard;

	//		�J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPosition;

	//		�J�����̃^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_cameraTarget;

	//		�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//		�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//		�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBuffer;

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;

	//		�X�P�[��
	float m_scale;

public:

	/*
	*	�X�P�[����ݒ肷��
	* 
	*	@parma	(scale)	�X�P�[��
	*/
	void SetScale(float scale) { m_scale = scale; }
};
