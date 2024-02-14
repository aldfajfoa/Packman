#include "Gauge.h"
#include "Engine/Image.h"

Gauge::Gauge(GameObject* parent)
	:GameObject(parent, "Gauge"), hGaugeBar_(-1), hGaugeFrame_(-1),
	gaugeMaxVal_(400), gaugeCrrVal_(400)
{
}

void Gauge::Initialize()
{
	hGaugeBar_ = Image::Load("HP.png");
	assert(hGaugeBar_ >= 0);
	hGaugeFrame_ = Image::Load("gauge.png");
	assert(hGaugeFrame_ >= 0);

	transform_.position_.x = 0.0f;
	transform_.position_.y = -0.9f;

	framesize = this->transform_;
	framesize.scale_.x = 1.0f;
	framesize.scale_.y = 0.6f;

	tr = this->transform_;
	tr.scale_.x = 2.0f;
	tr.scale_.y = 0.6f;
	tr.position_.x = -0.4f;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	tr.scale_.x = (float)gaugeCrrVal_ / ((float)gaugeMaxVal_/2);

	Image::SetTransform(hGaugeBar_, tr);
	Image::Draw(hGaugeBar_);

	Image::SetTransform(hGaugeFrame_, framesize);
	Image::Draw(hGaugeFrame_);
}

void Gauge::Release()
{
}
