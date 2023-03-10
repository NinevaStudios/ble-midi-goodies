﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiOutputDevice.generated.h"

UCLASS()
class UBleMidiOutputDevice : public UObject
{
	GENERATED_BODY()
public:
	UBleMidiOutputDevice();


#if PLATFORM_ANDROID
	void Init(jobject Object);
#endif

private:
#if PLATFORM_ANDROID
	jobject OutputDevice;
#endif

public:
#if PLATFORM_ANDROID
	FORCEINLINE jobject* GetOutputDevice() const { return OutputDevice; }
#endif

};
