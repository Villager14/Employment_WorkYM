/*
* @file		PostEffectObjectShader.h
* @brief	ポストエフェクトオブジェクトに対するシェーダー
* @author	Morita
* @date		2024/10/10
*/

#pragma once

#include "pch.h"

class PostEffectObjectShader
{
public:

	//		コンストラクタ
	PostEffectObjectShader()
	:
	m_useJudgement(false)
	{};

	//		デストラクタ
	~PostEffectObjectShader() {};

private:

	//		使うかどうか
	bool m_useJudgement;

	//		ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixselShader;

	//		頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;

	//		サンプラー(一部を取り出す物)
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

public:

	/*
	*	使うかどうか受け取る
	* 
	*	@return true : 使う false : 使わない
	*/
	bool GetUseJudgement() { return m_useJudgement; }

	/*
	*	使うかどうか設定する
	* 
	*	@param	(judgement) true : 使う false : 使わない
	*/
	void SetUseJudgement(bool judgement) { m_useJudgement = judgement; }

	/*
	*	ピクセルシェーダーを設定する
	* 
	*	@param	(shader)　ピクセルシェーダーのポインタ
	*/
	void SetPixselShader(ID3D11PixelShader* shader) { m_pixselShader = shader; }

	/*
	*	頂点シェーダーを設定する
	* 
	*	@param	(shader)	頂点シェーダーのポインタ
	*/
	void SetVertexShader(ID3D11VertexShader* shader) { m_vertexShader = shader; }

	/*
	*	ピクセルシェーダーを受け取る
	*
	*	@return ポインタ
	*/
	ID3D11PixelShader* GetPixselShader() { return m_pixselShader.Get(); }

	/*
	*	頂点シェーダーを受け取る
	* 
	*	@return ポインタ
	*/
	ID3D11VertexShader* GetVertexShader() { return m_vertexShader.Get(); }

	/*
	*	サンプラーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ID3D11SamplerState* GetSampler() { return m_sampler.Get(); }

	/*
	*	サンプラーを設定する
	* 
	*	@param	(sampler)	インスタンスのポインタ
	*/
	void SetSampler(ID3D11SamplerState* sampler) {m_sampler = sampler;}
};