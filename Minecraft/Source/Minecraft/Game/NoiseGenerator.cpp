#include "NoiseGenerator.h"

NoiseGenerator::NoiseGenerator() {}

float NoiseGenerator::Noise2D(int X, int Y, int Seed) {
	unsigned int N = 1619 * X + 31337 * Y + 1013 * Seed & 0x7fffffff;
	N = N >> 13 ^ N;
	N = N * (N * N * 60493 + 19990303) + 1376312589 & 0x7fffffff;
	return 1.f - static_cast<float>(static_cast<int>(N)) / 0x40000000;
}

float NoiseGenerator::Noise2D(FVector2D Pos, int Seed) {
	return Noise2D(Pos.X, Pos.Y, Seed);
}

float NoiseGenerator::Gradient2D(float X, float Y, int Seed, bool Eased) {
	// Calculate the integer coordinates
	int X0 = FMath::Floor(X);
	int Y0 = FMath::Floor(Y);
	// Calculate the remaining part of the coordinates
	float XL = X - static_cast<float>(X0);
	float Yl = Y - static_cast<float>(Y0);
	// Get values for corners of square
	float V00 = Noise2D(X0, Y0, Seed);
	float V10 = Noise2D(X0 + 1, Y0, Seed);
	float V01 = Noise2D(X0, Y0 + 1, Seed);
	float V11 = Noise2D(X0 + 1, Y0 + 1, Seed);
	// Interpolate
	if (Eased)
		return BiLinearInterpolation(V00, V10, V01, V11, XL, Yl);

	return BiLinearInterpolationNoEase(V00, V10, V01, V11, XL, Yl);
}

float NoiseGenerator::Perlin2D(float X, float Y, int Octaves, float Persistence, int Seed, bool Eased) {
	float a = 0;
	float f = 1.0;
	float g = 1.0;
	for (int i = 0; i < Octaves; i++) {
		a += g * Gradient2D(X * f, Y * f, Seed + i, Eased);
		f *= 2.0;
		g *= Persistence;
	}
	return a;
}


float NoiseGenerator::Noise3D(int X, int Y, int Z, int Seed) {
	unsigned int N = 1619 * X + 31337 * Y + 52591 * Z + 1013 * Seed & 0x7fffffff;
	N = N >> 13 ^ N;
	N = N * (N * N * 60493 + 19990303) + 1376312589 & 0x7fffffff;
	return 1.f - static_cast<float>(static_cast<int>(N)) / 0x40000000;
}

float NoiseGenerator::Noise3D(FVector Pos, int Seed) {
	return Noise3D(Pos.X, Pos.Y, Pos.Z, Seed);
}

float NoiseGenerator::LinearInterpolation(float v0, float v1, float t) {
	return v0 + (v1 - v0) * t;
}

float NoiseGenerator::BiLinearInterpolation(float V00, float V10, float V01, float V11, float X, float Y) {
	float TX = EaseCurve(X);
	float TY = EaseCurve(Y);
	float U = LinearInterpolation(V00, V10, TX);
	float V = LinearInterpolation(V01, V11, TX);
	return LinearInterpolation(U, V, TY);
}


float NoiseGenerator::BiLinearInterpolationNoEase(float V00, float V10, float V01, float V11, float X, float Y) {
	float U = LinearInterpolation(V00, V10, X);
	float V = LinearInterpolation(V01, V11, X);
	return LinearInterpolation(U, V, Y);
}

float NoiseGenerator::EaseCurve(float T) {
	return T * T * T * (T * (6.f * T - 15.f) + 10.f);
}
