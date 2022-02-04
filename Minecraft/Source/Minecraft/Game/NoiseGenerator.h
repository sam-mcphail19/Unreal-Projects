
#pragma once

class NoiseGenerator {
public:
	NoiseGenerator();
	
	float Noise2D(int X, int Y, int Seed);
	float Noise2D(FVector2D Pos, int Seed);
	float Gradient2D(float X, float Y, int Seed, bool Eased);
	float Perlin2D(float X, float Y, int Octaves, float Persistence, int Seed, bool Eased);
	
	float Noise3D(int X, int Y, int Z, int Seed);
	float Noise3D(FVector Pos, int Seed);
	
	float LinearInterpolation(float v0, float v1, float t);
	float BiLinearInterpolation(float V00, float V10, float V01, float V11, float X, float Y);
	float BiLinearInterpolationNoEase(float V00, float V10, float V01, float V11, float X, float Y);
	float EaseCurve(float T);
};