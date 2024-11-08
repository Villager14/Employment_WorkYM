/*
* @file		PostEffectObjectShader.h
* @brief	�|�X�g�G�t�F�N�g�I�u�W�F�N�g�ɑ΂���V�F�[�_�[
* @author	Morita
* @date		2024/10/10
*/

#pragma once

#include "pch.h"

class PostEffectObjectShader
{
public:

	//		�R���X�g���N�^
	PostEffectObjectShader()
	:
	m_useJudgement(false)
	{};

	//		�f�X�g���N�^
	~PostEffectObjectShader() {};

private:

	//		�g�����ǂ���
	bool m_useJudgement;

	//		�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		�T���v���[(�ꕔ�����o����)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

public:

	/*
	*	�g�����ǂ����󂯎��
	* 
	*	@return true : �g�� false : �g��Ȃ�
	*/
	bool GetUseJudgement() { return m_useJudgement; }

	/*
	*	�g�����ǂ����ݒ肷��
	* 
	*	@param	(judgement) true : �g�� false : �g��Ȃ�
	*/
	void SetUseJudgement(bool judgement) { m_useJudgement = judgement; }

	/*
	*	�s�N�Z���V�F�[�_�[��ݒ肷��
	* 
	*	@param	(shader)�@�s�N�Z���V�F�[�_�[�̃|�C���^
	*/
	void SetPixselShader(ID3D11PixelShader* shader) { m_pixselShader = shader; }

	/*
	*	���_�V�F�[�_�[��ݒ肷��
	* 
	*	@param	(shader)	���_�V�F�[�_�[�̃|�C���^
	*/
	void SetVertexShader(ID3D11VertexShader* shader) { m_vertexShader = shader; }

	/*
	*	�s�N�Z���V�F�[�_�[���󂯎��
	*
	*	@return �|�C���^
	*/
	ID3D11PixelShader* GetPixselShader() { return m_pixselShader.Get(); }

	/*
	*	���_�V�F�[�_�[���󂯎��
	* 
	*	@return �|�C���^
	*/
	ID3D11VertexShader* GetVertexShader() { return m_vertexShader.Get(); }

	/*
	*	�T���v���[���󂯎��
	* 
	*	@return �C���X�^���X�̃|�C���^
	*/
	ID3D11SamplerState* GetSampler() { return m_sampler.Get(); }

	/*
	*	�T���v���[��ݒ肷��
	* 
	*	@param	(sampler)	�C���X�^���X�̃|�C���^
	*/
	void SetSampler(ID3D11SamplerState* sampler) {m_sampler = sampler;}
};