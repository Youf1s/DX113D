#pragma once
#include"DrawItBase.h"
#include <random>

class Cube	: public DrawItBase<Cube>
{
public:
	Cube(Graphics& Gfx, std::mt19937& rng, std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist);
	void Update(float DA) override;
	DirectX::XMMATRIX GetTransform() const override;
	
private:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;


	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;

};

