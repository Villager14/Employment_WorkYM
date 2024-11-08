/*
* @file		Instancing.h
* @brief	�C���X�^���V���O
* @author	Morita
* @date		2024/10/04
* 
* �Q�l : http://maverickproj.web.fc2.com/d3d11_18.html
*/

#pragma once

#include "Library/Mesh/LeadMesh.h"

class Instancing
{
public:
	//		�R���X�g���N�^
	Instancing();

	//		�f�X�g���N�^
	~Instancing();
	
	/*
	*	����������
	* 
	*	@param	(�`�搔)
	*/
	void Initilaize(int count, const wchar_t* psPath, const wchar_t* vsPath);

	//		�`�揈��
	void Render();


	//		���b�V���̏��
	void MeshInformation(const wchar_t* path);

	/*
	*	�e�N�X�`���̓ǂݍ���
	*
	*	@param	(path)	�t�@�C���p�X
	*/
	void LoadTexture(const wchar_t* path, int index = 0);

private:
	//		�V�F�[�_�[�̓ǂݍ���
	void ShaderRead(const wchar_t* psPath, const wchar_t* vsPath);

public:

	//		���_
	std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	
	//		���_�V�F�[�_�[�p�̃o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_instanceBuffer;

	//		���_�C���f�b�N�X�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexIndexBuffer;

	//		���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;


	//		���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		�e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	Microsoft::WRL::ComPtr<ID3D11Resource> m_resource;

	//		���b�V���̓ǂݍ���
	std::unique_ptr<LeadMesh> m_learMesh;

	//		�`�悷�鐔
	int m_count;

	//		���b�V���̒��_�̐�
	int m_meshIndexCount;

	//		���_�̐�
	int m_vertexCount;

	//		���_�C���f�b�N�X
	std::vector<int> m_vertexIndex;

	//		���_���
	std::vector<DirectX::SimpleMath::Vector3> m_vertex;

	float time;
};