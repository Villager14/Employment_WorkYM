/*
* @file		PlayerModelTexture.h
* @brief	�v���C���[���f���̃e�N�X�`����
* @author	Morita
* @date		2024/06/28
*/

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Game/Camera/PlaySceneCamera/PlayerCameraInformation.h"

class PlayerModelTexture
{
public:
	//		�R���X�g�o�b�t�@
	struct  ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Matrix		rotationMatrix;
	};
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//		�R���X�g���N�^
	PlayerModelTexture();

	//		�f�X�g���N�^
	~PlayerModelTexture();

	/*
	*	�쐬
	*
	*	@param	(position)	���W
	*	@param	(scale)		�X�P�[��
	*/
	void Create(
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale);

	/*
	*	�X�V����
	*
	*	@param	(timer)	DX::StepTimer
	*/
	void Update();

	/*
	*	�`�揈��
	*
	*	@param (shaderResouceView)	�e�N�X�`�����
	*/
	void Render(ID3D11ShaderResourceView* shaderResouceView);

	/*
	*	�X�P�[����ݒ肷��
	*
	*	@param	(scale) �X�P�[��
	*/
	void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; };

	/*
	*	�X�P�[�����󂯎��
	*
	*	@return �X�P�[��
	*/
	DirectX::SimpleMath::Vector2 GetScale() { return m_scale; }

	/*
	*	�x�[�X�̃X�P�[�����󂯎��
	*
	*	@return �x�[�X�X�P�[��
	*/
	DirectX::SimpleMath::Vector2 GetBaseScale() { return m_baseScale; }

	/*
	*	���W��ݒ肷��
	*
	*	@param	(position)
	*/
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	/*
	*	���W���󂯎��
	*
	*	@return ���W
	*/
	DirectX::SimpleMath::Vector2 GetPosition() { return m_position; }

	/*
	*	��]�s����󂯎��
	*
	*	@param	(rotatonMatrix)	��]�s��
	*/
	void SetRotationMatrix(DirectX::SimpleMath::Matrix rotatonMatrix) { m_rotationMatrix = rotatonMatrix; }

	/*
	*	�O���C�ɂ��邩�ǂ����ݒ肷��
	*
	*	@param	(judgement)	true : �O���C�ɂ��� false : �O���C�ɂ��Ȃ�
	*/
	void SetGrayJudgement(bool judgement) { m_grayJudgement = judgement; }

private:

	void CreateShader();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;

	//		���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	//		�W�I���g���b�N�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometoryShaer;

	//		�X�P�[��
	DirectX::SimpleMath::Vector2 m_scale;

	//		�����X�P�[��
	DirectX::SimpleMath::Vector2 m_baseScale;

	//		���W
	DirectX::SimpleMath::Vector2 m_position;

	//		��]�s��
	DirectX::SimpleMath::Matrix m_rotationMatrix;

	//		�O���C�ɂ��邩�ǂ���
	bool m_grayJudgement;
};