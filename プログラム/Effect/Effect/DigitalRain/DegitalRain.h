/*
* @file		DegitalRain.h
* @brief	�f�W�^���J�}�l�[�W���[
* @author	Morita
* @date		2024/10/14
*/

#pragma once

#include "Library/Shader/EffectShaderManager.h"

#include "DegitalRainParameter.h"

#include "Effect/PostEffect/PostEffectFlag.h"

class EffectManager;

class DegitalRain
{
public:

	DegitalRain(EffectManager* effectManager);

	~DegitalRain();

	//		����������
	void Initialzie();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render(PostEffectFlag::Flag flag);

	int BinaryDigits(int number);

	//		�\�[�g����
	void Sort();

	//		�����̐���
	void CreateNumber(int index);

	//		�N�[���^�C��
	void CoolTime();

	/*
	*	�������W�P
	* 
	*/
	void GenerationPosition(int index);

	//		�r���{�[�h�̍쐻
	void Billbord(DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up, int index);

	//		�I������
	void Finalize();

private:

	struct  ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
		int number = 0;
		DirectX::SimpleMath::Vector3 pad;
	};

public:

	const float MAX_LENGTH = 50.0f;

	const float MIN_LENGTH = 40.0f;

private:

	ConstBuffer m_constBuffer;

	//		�G�t�F�N�g�}�l�[�W���[
	EffectManager* m_effectManager;

	//		�G�t�F�N�g�V�F�[�_�[�}�l�[�W���[
	std::unique_ptr<EffectShaderManager<ConstBuffer>> m_effectShaderManager;

	//		�p�����[�^�[
	std::vector<DegitalRainParameter> m_parameta;

	//		�|�X�g�G�t�F�N�g�t���O
	std::unique_ptr<PostEffectFlag> m_postEffectFlag;

	float m_time;
};