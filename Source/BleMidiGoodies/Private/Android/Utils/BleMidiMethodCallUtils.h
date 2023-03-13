// Copyright (c) 2023 Nineva Studios

#pragma once

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

class UBleMidiOutputDevice;
class UBleMidiInputDevice;

namespace BleMidiMethodCallUtils
{
	bool CallBoolMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	void CallVoidMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	jobject CallObjectMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	TArray<UBleMidiInputDevice*> ConvertToInputArray(jobjectArray javaObjectArray);
	TArray<UBleMidiOutputDevice*> ConvertToOutputArray(jobjectArray javaObjectArray);
	jintArray ConvertToJIntArray(const TArray<int>& intArray);
	void CallStaticVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);
	jobjectArray ConvertToJStringArray(const TArray<FString>& stringArray);
	TArray<int> ConvertToIntArray(jintArray javaArray);
	TArray<FString> ConvertToStringArray(jobjectArray javaStringArray);
	TArray<bool> ConvertToBoolArray(jbooleanArray javaBooleanArray);
	FString CallStringMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...);

};
