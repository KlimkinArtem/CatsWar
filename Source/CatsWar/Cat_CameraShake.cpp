// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat_CameraShake.h"

UCat_CameraShake::UCat_CameraShake()
{
	OscillationDuration = 0.25f;
	OscillationBlendInTime = 0.05f;
	OscillationBlendOutTime = 0.05f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(2.5f, 5.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(12.5f, 17.5f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(2.5f, 5.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(12.5f, 17.5f);
}