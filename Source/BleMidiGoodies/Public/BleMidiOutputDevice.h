﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif

#include "BleMidiOutputDevice.generated.h"

UCLASS(BlueprintType)
class BLEMIDIGOODIES_API UBleMidiOutputDevice : public UObject
{
	GENERATED_BODY()
public:
	~UBleMidiOutputDevice();
	
	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	FString GetName();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	FString GetAddress();

	UFUNCTION(BlueprintCallable, Category = "Ble Midi|Output Device")
	void SendMessage(int Type, TArray<int> Data);

#if PLATFORM_ANDROID
	void Init(jobject Object);
#endif

private:
#if PLATFORM_ANDROID
	jobject OutputDevice;
#endif

public:
#if PLATFORM_ANDROID
	jobject GetOutputDevice() { return OutputDevice; }
#endif

};
