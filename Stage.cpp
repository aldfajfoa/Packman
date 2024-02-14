#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Camera.h"

bool Stage::IsWall(int _x, int _y)
{
	//assert();
	if(stageData_[_y][_x]==STAGE_OBJ::WALL)
		return false;
	else
		return true;
}

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
	CsvReader csv;
	csv.Load("mapdata.csv");
	stageWidth_ = csv.GetWidth();
	stageHeight_ = csv.GetHeight();

	for (int i = 0; i < stageHeight_; i++)
	{
		vector<int> sdata(stageWidth_, 0);//15ŒÂ‚Ì”z—ñ‚ğ0‚Å‰Šú‰»
		stageData_.push_back(sdata);
	}
	//vector<vector<int>> stagedata_(h, vector<int>(STAGE_Y, 0));
	
	for (int j = 0; j < stageHeight_; j++) {
		for (int i = 0; i < stageWidth_; i++) {
			stageData_[j][i] = csv.GetValue(i, j);
		}
	}
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);

	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hWall_ >= 0);

	Camera::SetPosition({ 6.5, 15, -3 });
	Camera::SetTarget({ 6.5, 0, 5.5 });
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	floorTrans.position_ = { 0,0,0 };

	for (int z = 0; z < stageHeight_; z++) {
		for (int x = 0; x < stageWidth_; x++) {
			floorTrans.position_ = { (float)x, 0, (float)(14 - z) };
			if (stageData_[z][x] == 1) {
				Model::SetTransform(hWall_, floorTrans);
				Model::Draw(hWall_);
			}
			else {
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}

void Stage::Release()
{
	//”z—ñ‚Ì‘|œ
	for (int i = 0; i < stageHeight_; i++)
	{
		stageData_[i].clear();
	}
	stageData_.clear();
}
