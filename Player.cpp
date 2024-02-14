#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Stage.h"
#include "Gauge.h"
#include "Engine/SceneManager.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

enum Dir {
	UP, LEFT, DOWN, RIGHT, NONE,
};

float rotAngle[5]{ 0,-90,180,90,0 };

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),
	hModel_(-1),speed_(PLAYER_MOVE_SPEED),pStage_(nullptr),
	hpMax_(300),hpCrr_(300)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("Model\\Player.fbx");
	assert(hModel_ >= 0);

	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage*)FindObject("Stage");
}

void Player::Update()
{
	XMVECTOR vFront{ 0,0,1 };
	XMVECTOR move{ 0,0,0 };

	if (Input::IsKey(DIK_UP)) {
		move = { 0,0,1 };
		//moveDir = UP;
	}
	if (Input::IsKey(DIK_LEFT)) {
		move = { -1,0,0 };
		//moveDir = LEFT;
	}
	if (Input::IsKey(DIK_DOWN)) {
		move = { 0,0,-1 };
		//moveDir = DOWN;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		move = { 1,0,0 };
		//moveDir = RIGHT;
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero();//ゼロベクトルで初期化
	posTmp = pos + posTmp;
	pos = pos + speed_ * move;

	int tx, ty;
	tx = (int)(XMVectorGetX(pos) + 1.0f);
	ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(pos) + 1.0f);
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}
	
	if(!(pStage_->IsWall(tx, ty)))
	{
		hpCrr_ -= 2;
		if (hpCrr_ < 0) hpCrr_ = 0;
	}
	//posTmp.x , posTmp.z => int tx,ty:配列のインデックス
	//仮にmapの配列をmap[][]とする
	//移動先がフロア(STAGEOBJ::FLOOR=>0)だったら動く
	//if (map[ty][tx] == STAGEOBJ::FLOOR) {
	//	pos = postmp;
	//}

	/*if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		XMMATRIX rot = XMMatrixRotationY(XM_PIDIV2);
		XMVECTOR modifiedVec = XMVector3Transform(move, rot);

		float angle = atan2(XMVectorGetZmodifiedVec),);

		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0) {
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}*/
	if (!XMVector3Equal(move, XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		XMVECTOR vdot = XMVector3Dot(vFront, move);
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		float angle = acos(XMVectorGetX(vdot));

		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0) {
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}

	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetGaugeVal(hpCrr_, hpMax_);

	if (hpCrr_ <= 0) {
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID::SCENE_ID_OVER);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
