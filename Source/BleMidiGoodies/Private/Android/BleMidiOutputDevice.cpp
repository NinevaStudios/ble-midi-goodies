// Copyright (c) 2023 Nineva Studios

#include "BleMidiOutputDevice.h"

UBleMidiOutputDevice::UBleMidiOutputDevice()
{
	
}

#if PLATFORM_ANDROID

UBleMidiOutputDevice::Init(jobject Object)
{
	OutputDevice = Object;
}

#endif
