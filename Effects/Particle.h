// --------------------------------------------------------------------
// パーティクルを一括管理するクラス
// --------------------------------------------------------------------
#pragma once

#include "pch.h"
#include <list>

class CustomShader;
class DustTrailParticle;
class SwordTrailParticle;

class Particle
{
	// ----------------------------
	// 構造体
	// ----------------------------
public:
	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	頂点入力レイアウト
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// ----------------------------
	// 定数
	// ----------------------------
private:
	// テクスチャ名
	static constexpr const wchar_t* TEXTURE_NAME = L"dust.png";

	// 軌跡シェーダー
	static constexpr  wchar_t SWORD_VS[] = L"Resources/cso/SwordTrailVS.cso";
	static constexpr  wchar_t SWORD_PS[] = L"Resources/cso/SwordTrailPS.cso";

	// 土煙シェーダー
	static constexpr  wchar_t DUST_VS[] = L"Resources/cso/DustVS.cso";
	static constexpr  wchar_t DUST_PS[] = L"Resources/cso/DustPS.cso";
	static constexpr  wchar_t DUST_GS[] = L"Resources/cso/DustGS.cso";

	// パーティクルの最大数
	static constexpr int	MAX_SMASH_ATTACK_DUST = 25;
	// 土埃のY軸の最小速度
	static constexpr float	MIN_SMASH_DUST_SPEED_Y = 1.0f;
	// 土埃のY軸の最大速度
	static constexpr float	MAX_SMASH_DUST_SPEED_Y = 5.0f;
	// 土埃の最小半径
	static constexpr float  SMASH_DUST_RADIUS = 1.0f;

	// ----------------------------
	// メンバ関数（公開）
	// ----------------------------
public:
	// コンストラクタ
	Particle();
	// デストラクタ
	~Particle();
	// パーティクルの生成を行う
	void Create();
	// パーティクルの更新処理
	void Update(float elapsedTimer, const DirectX::SimpleMath::Vector3 playerPosition, const DirectX::SimpleMath::Vector3 playerVelocity);
	// パーティクルの描画処理
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj);
	// ビルボード行列の作成
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);
	// 軌跡の土埃を生成する処理
	void CreateTrailDust();
	// 剣の軌跡を生成する処理
	void CreateSwordTrail(void* ver);
	// たたきつけの煙パーティクルの生成
	void CreateBashDust(void* center);

	// ----------------------------
	// メンバ関数（非公開）
	// ----------------------------
private:
	// 剣パーティクルの描画設定
	void DrawSwordParticle(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// 煙パーティクルの描画設定
	void DrawDustParticle(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Vector3 cameraDir);
	// シェーダーの作成
	inline void CreateShader();

	// ----------------------------
	// メンバ変数
	// ----------------------------
private:
	// バッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// シェーダー
	std::unique_ptr<CustomShader> m_swordShader;
	std::unique_ptr<CustomShader> m_dustShader;
	// ビルボード行列
	DirectX::SimpleMath::Matrix m_billboard;
	// 頂点カラーテクスチャー
	std::vector<DirectX::VertexPositionColorTexture> m_dustVertices;
	// カメラの座標
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	// 焦点
	DirectX::SimpleMath::Vector3 m_cameraTarget;
	// 軌跡ダスト
	std::list<DustTrailParticle> m_dustTrail;
	// 軌跡ダストの時間
	float m_timerDustTrail;
	// 剣の軌跡パーティクル
	std::list<SwordTrailParticle> m_swordTrail;
	// 剣の軌跡の時間
	float m_timerSwordTrail;
	// プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;
	// プレイヤーの速度
	DirectX::SimpleMath::Vector3 m_playerVelocity;
};