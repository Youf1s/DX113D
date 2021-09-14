cbuffer CBuf 
{
	float4 FaceColor[6];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return FaceColor[tid/2];
}