﻿// Copyright (c) 2023 Nineva Studios

#include "BleMidiMethodCallUtils.h"

#include "BleMidiInputDevice.h"
#include "BleMidiOutputDevice.h"

namespace BleMidiMethodCallUtils
{
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

	void CallStaticVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature,
							  ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = FAndroidApplication::FindJavaClass(ClassName);

		jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		Env->CallStaticVoidMethodV(Class, Method, Args);
		va_end(Args);

		Env->DeleteLocalRef(Class);
	}

	jobjectArray ConvertToJStringArray(const TArray<FString>& stringArray)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jobjectArray javaStringArray = (jobjectArray)Env->NewObjectArray(
			stringArray.Num(), FJavaWrapper::JavaStringClass,
			nullptr);

		for (int i = 0; i < stringArray.Num(); i++)
		{
			Env->SetObjectArrayElement(javaStringArray, i, *FJavaClassObject::GetJString(stringArray[i]));
		}

		return javaStringArray;
	}

	TArray<int> ConvertToIntArray(jintArray javaArray)
	{
		TArray<int> intArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jint* javaInt = Env->GetIntArrayElements(javaArray, 0);

		int length = Env->GetArrayLength(javaArray);

		for (int i = 0; i < length; i++)
		{
			intArray.Add(javaInt[i]);
		}

		return intArray;
	}

	TArray<FString> ConvertToStringArray(jobjectArray javaStringArray)
	{
		TArray<FString> stringArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		int length = Env->GetArrayLength(javaStringArray);

		for (int i = 0; i < length; i++)
		{
			jstring javaString = static_cast<jstring>(Env->GetObjectArrayElement(javaStringArray, i));

			stringArray.Add(FJavaHelper::FStringFromParam(Env, javaString));
		}

		return stringArray;
	}

	TArray<bool> ConvertToBoolArray(jbooleanArray javaBooleanArray)
	{
		TArray<bool> boolArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		int length = Env->GetArrayLength(javaBooleanArray);

		jboolean* javaBooleans = Env->GetBooleanArrayElements(javaBooleanArray, 0);

		for (int i = 0; i < length; i++)
		{
			boolArray.Add((bool)javaBooleans[i]);
		}

		return boolArray;
	}

	FString CallStringMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
	{
		bool bIsOptional = false;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jclass Class = Env->GetObjectClass(object);

		jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

		va_list Args;
		va_start(Args, MethodSignature);
		jstring Return = static_cast<jstring>(Env->CallObjectMethodV(object, Method, Args));
		va_end(Args);

		if (Return == nullptr)
		{
			return FString();
		}

		const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
		FString Result(UTF8_TO_TCHAR(UTFString));
		Env->ReleaseStringUTFChars(Return, UTFString);

		Env->DeleteLocalRef(Class);

		return Result;
	}
}

