#include "BleMidiInputDevice.h"

UBleMidiInputDevice::UBleMidiInputDevice()
{
	
}

#if PLATFORM_ANDROID

UBleMidiInputDevice::Init(jobject Object)
{
	InputDevice = Object;
}

#endif