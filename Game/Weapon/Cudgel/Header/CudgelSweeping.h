// ----------------------------------------------------------
// 名前:	CudgeSweeping
// 
// 内容:	ボス鬼の武器の金棒　薙ぎ払いのステート
// 			ステートマシーンを使用
//
// 制作:	池田桜輔
// ----------------------------------------------------------
#pragma once
// インクルード
#include "pch.h"
#include "Interface/IWeapon.h"

class Cudgel;
class Boss;

/// <summary>
/// 攻撃状態
/// </summary>
class CudgelSweeping : public IWeapon
{
	// --------------------------
	// 固定値
	// ---------------------------
public:
	// 攻撃の貯めモーションの時間
	static constexpr float CHARGE_TIME = 0.8f;
	// 攻撃する前の時間
	static constexpr float WINDUP_TIME = 0.9f;
	// 攻撃する時間
	static constexpr float ATTACK_TIME = 2.0f;
	// 攻撃（全体）が終了する時間
	static constexpr float END_TIME = 2.3f;

	// 初期回転角
	static constexpr float INITIAL_ROTATE_UD = 93.0f;
	// 攻撃の貯めモーションの角度
	static constexpr float CHARGE_ROTATE_ANGLE = 30.0f;
	// 攻撃後の角度
	static constexpr float WINDUP_ROTATE_ANGLE = 240.0f;

	// 腕の長さ
	static constexpr DirectX::SimpleMath::Vector3 ARM_LENGTH = { 0.0f, 5.0f, 0.0f };
	// 減点から移動する位置
	static constexpr DirectX::SimpleMath::Vector3 ZERO_DIREC = { 6.0f, 1.0f, 0.0f };

	// ---------------------------
	// メンバ関数(公開)
	// ---------------------------
public:
	// コンストラクタ
	CudgelSweeping(Cudgel* cudgel);
	// デストラクタ
	~CudgelSweeping()override;
	// 初期化処理
	void Initialize()override;
	// 事前処理
	void PreUpdate()override;
	// 更新処理
	void Update(float elapsedTime)override;
	// 事後処理
	void PostUpdate()override;
	// 終了処理
	void Finalize()override;
	// 衝突イベント
	void HitAction(InterSectData data)override;

	// ---------------------------
	// メンバ関数(非公開)
	// ---------------------------
private:
	// Cudgelの回転を計算する関数
	void UpdateCudgelRotation();
	// チャージアニメーション
	void ChargeAnimation();
	// 攻撃モーション
	void AttackAnimation();
	// 終了モーション
	void EndAnimation();
	// 初期値として使用するワールド行列を計算する関数
	void CalculateModelMatrix();
	// Cudgelの攻撃モーションの回転を計算する関数
	DirectX::SimpleMath::Matrix CalculateAttackMatrix();
	// 根本と頂点の座標を取得する ※ both ends = 両端
	void GetCudgelBothEnds();

	// -----------------------------
	// メンバ変数
	// -----------------------------
private:
	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 左右角度
	float m_angleRL;
	// 上下角度
	float m_angleUD;
	// 親の左右角度
	float m_parentAngleRL;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 当たり判定用の行列
	DirectX::SimpleMath::Matrix m_collMatrix;
	// ステートの経過時間
	float m_totalSeconds;

	// ステートを所有する親
	Cudgel* m_cudgel;
	// ボス
	Boss* m_boss;

	// 根本の座標配列
	std::vector<DirectX::SimpleMath::Vector3> m_rootPos;
	// 先端の座標配列
	std::vector<DirectX::SimpleMath::Vector3> m_tipPos;
	// 効果音を再生したかのフラグ
	bool m_playSound;
	// プレイヤーがヒットできるかのフラグ
	bool m_playerCanHit;
};