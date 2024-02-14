#include "TITLE.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

TITLE::TITLE(GameObject* parent)
	:GameObject(parent, "TITLE"), hpict_(-1)
{
}

void TITLE::Initialize()
{
	hpict_ = Image::Load("TITLE.png");
	assert(hpict_ >= 0);
}

void TITLE::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		SceneManager* pSM = (SceneManager*)(FindObject("SceneManager"));
		pSM->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

void TITLE::Draw()
{
	Image::SetTransform(hpict_, transform_);
	Image::Draw(hpict_);
}

void TITLE::Release()
{
}
