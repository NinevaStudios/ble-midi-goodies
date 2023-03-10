﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiInputDevice.generated.h"

UCLASS()
class UBleMidiInputDevice : public UObject
{
	GENERATED_BODY()
public:
	UBleMidiInputDevice();

#if PLATFORM_ANDROID
	void Init(jobject Object);
#endif

private:
#if PLATFORM_ANDROID
	jobject InputDevice;
#endif

public:
#if PLATFORM_ANDROID
	FORCEINLINE jobject* GetInputDevice() const { return InputDevice; }
#endif

};