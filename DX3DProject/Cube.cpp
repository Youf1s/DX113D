#include "Cube.h"
#include"AllBindabls.h"



Cube::Cube(Graphics& Gfx, std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist)
	:
	r(rdist(rng)),
	droll(ddist(rng)),
	dpitch(ddist(rng)),
	dyaw(ddist(rng)),
	dphi(odist(rng)),
	dtheta(odist(rng)),
	dchi(odist(rng)),
	chi(adist(rng)),
	theta(adist(rng)),
	phi(adist(rng))
{

	
	
	if (!IsStaticInitialized())
	{



		struct Vertex
		{
			struct
			{
				float x;
				float y;
				float z;
			} Pos;
		};
		const std::vector<Vertex> Vertices =
		{
			{ -1.0f,-1.0f,-1.0f },
			{ 1.0f,-1.0f,-1.0f },
			{ -1.0f,1.0f,-1.0f },
			{ 1.0f,1.0f,-1.0f },
			{ -1.0f,-1.0f,1.0f },
			{ 1.0f,-1.0f,1.0f },
			{ -1.0f,1.0f,1.0f },
			{ 1.0f,1.0f,1.0f },
		};

		AddStaticBind(std::make_unique<VertexBuffer>(Gfx, Vertices));

		auto pvs = std::make_unique<VertexShader>(Gfx, L"VertexShader.cso");
		auto pvsbc = pvs->GetpBlob();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(Gfx, L"PixelShader.cso"));

		const std::vector<unsigned short> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(Gfx, indices));

		struct ConstantBuffer2
		{
			struct
			{
				float r;
				float g;
				float b;
				float a;
			} face_colors[6];
		};
		const ConstantBuffer2 cb2 =
		{
			{
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,1.0f,1.0f },
			}
		};

		AddStaticBind(std::make_unique<PixelConstantBuf<ConstantBuffer2>>(Gfx, cb2));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(Gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topolagy>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

		AddBind(std::make_unique<TransformCBuf>(Gfx, *this));

}

void Cube::Update(float DA)
{
	roll += droll * DA;
	pitch += dpitch * DA;
	yaw += dyaw * DA;
	theta += dtheta * DA;
	phi += dphi * DA;
	chi += dchi * DA;
}

DirectX::XMMATRIX Cube::GetTransform() const
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
		DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
		DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
