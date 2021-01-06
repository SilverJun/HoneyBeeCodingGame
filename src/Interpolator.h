#pragma once
#include "Singleton.h"
#include "System.h"
#include <unordered_map>
#include <vector>

// http://www.gizma.com/easing/#l

enum ease
{
	Linear,
	QuadIn,
	QuadOut,
	QuadInOut,
	CubicIn,
	CubicOut,
	CubicInOut,
	ExpoIn,
	ExpoOut,
	ExpoInOut,
	CircIn,
	CircOut,
	CircInOut,
	EaseNum
};

using EaseFunction = float(float, float, float, float);

struct Tween
{
	ease _ease;
	float* _value;
	float _duration;
	float _start;
	float _end;
	std::function<void(Tween)> _doneCallback;
	bool _isDone = false;
	std::chrono::high_resolution_clock::time_point _startTime;
};

class Interpolator : public System, public Singleton<Interpolator>
{
	std::unordered_map<ease, std::function<EaseFunction>> _easeFunctions;
	std::vector<Tween> _tweenList;

public:
	Interpolator();
	virtual ~Interpolator() = default;
	void Init() override;
	void Update() override;
	void Release() override;

	Tween* AddTween(Tween tween);
	void DeleteTween(Tween* tween);
};

