// Copyright (c) 2023 Nineva Studios

#include "Android/BleMidiInputDevice.h"
#include "Android/BleMidiOutputDevice.h"

namespace BleMidiMethodCallUtils
{
	bool CallStaticBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = FAndroidApplication::FindJavaClass(ClassName);

		jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		bool Result = Env->CallStaticBooleanMethodV(Class, Method, Args);
		va_end(Args);

		Env->DeleteLocalRef(Class);

		return Result;
	}
	bool CallBoolMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = Env->GetObjectClass(object);

		jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		bool Result = Env->CallBooleanMethodV(object, Method, Args);
		va_end(Args);

		Env->DeleteLocalRef(Class);

		return Result;
	}
	void CallVoidMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = Env->GetObjectClass(object);

		jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		Env->CallVoidMethodV(object, Method, Args);
		va_end(Args);

		Env->DeleteLocalRef(Class);
	}
	
	jobject CallObjectMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = Env->GetObjectClass(object);

		jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		jobject Result = Env->CallObjectMethodV(object, Method, Args);
		va_end(Args);

		Env->DeleteLocalRef(Class);

		return Result;
	}
	TArray<UBleMidiInputDevice*> ConvertToInputArray(jobjectArray javaObjectArray)
	{
		TArray<UBleMidiInputDevice*> objectArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		int length = Env->GetArrayLength(javaObjectArray);

		for (int i = 0; i < length; i++)
		{
			UBleMidiInputDevice* Device = NewObject<UBleMidiInputDevice>();
			Device->Init(Env->GetObjectArrayElement(javaObjectArray, i));
			objectArray.Add(Device);
		}
		return objectArray;
	}

	TArray<UBleMidiOutputDevice*> ConvertToOutputArray(jobjectArray javaObjectArray)
	{
		TArray<UBleMidiOutputDevice*> objectArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		int length = Env->GetArrayLength(javaObjectArray);

		for (int i = 0; i < length; i++)
		{
			UBleMidiOutputDevice* Device = NewObject<UBleMidiOutputDevice>();
			Device->Init(Env->GetObjectArrayElement(javaObjectArray, i));
			objectArray.Add(Device);
		}
		return objectArray;
	}
	jintArray ConvertToJIntArray(const TArray<int>& intArray)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jintArray javaIntArray = (jintArray)Env->NewIntArray(intArray.Num());

		jint* javaIntArrayPtr = (jint*)malloc(intArray.Num() * sizeof(jint));

		for (int i = 0; i < intArray.Num(); i++)
		{
			javaIntArrayPtr[i] = (jint)intArray[i];
		}

		Env->SetIntArrayRegion(javaIntArray, 0, intArray.Num(), javaIntArrayPtr);

		free(javaIntArrayPtr);

		return javaIntArray;
	}
}

