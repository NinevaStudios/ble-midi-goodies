﻿// Copyright (c) 2023 Nineva Studios

#pragma once

#include "BleMidiInputDeviceCallback.generated.h"

UENUM()
enum class EMidiMessageType :uint8
{
	E_MMT_SystemExclusive = 0 UMETA(DisplayName = "SystemExclusive"),
	E_MMT_NoteOff = 1 UMETA(DisplayName = "NoteOff"),
	E_MMT_NoteOn = 2 UMETA(DisplayName = "NoteOn"),
	E_MMT_PolyphonicAftertouch = 3 UMETA(DisplayName = "PolyphonicAftertouch"),
	E_MMT_ControlChange = 4 UMETA(DisplayName = "ControlChange"),
	E_MMT_ProgramChange = 5 UMETA(DisplayName = "ProgramChange"),
	E_MMT_ChannelAftertouch = 6 UMETA(DisplayName = "ChannelAftertouch"),
	E_MMT_PitchWheel = 7 UMETA(DisplayName = "PitchWheel"),
	E_MMT_TimeCodeQuarterFrame = 8 UMETA(DisplayName = "TimeCodeQuarterFrame"),
	E_MMT_SongSelect = 9 UMETA(DisplayName = "SongSelect"),
	E_MMT_SongPositionPointer = 10 UMETA(DisplayName = "SongPositionPointer"),
	E_MMT_TuneRequest = 11 UMETA(DisplayName = "TuneRequest"),
	E_MMT_TimingClock = 12 UMETA(DisplayName = "TimingClock"),
	E_MMT_Start = 13 UMETA(DisplayName = "Start"),
	E_MMT_Continue = 14 UMETA(DisplayName = "Continue"),
	E_MMT_Stop = 15 UMETA(DisplayName = "Stop"),
	E_MMT_ActiveSensing = 16 UMETA(DisplayName = "ActiveSensing"),
	E_MMT_Reset = 17 UMETA(DisplayName = "Reset"),
	E_MMT_RPN = 18 UMETA(DisplayName = "RPN"),
	E_MMT_NRPN = 19 UMETA(DisplayName = "NRPN"),
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMessageReceivedDelegate, EMidiMessageType, Type, TArray<int>, Data);

UCLASS()
class UBleMidiInputDeviceCallback : public UObject
{
public:
	
	void BindOnMessageReceivedDelegate(const FOnMessageReceivedDelegate& Delegate);

	void ExecuteOnMessageReceivedDelegate(EMidiMessageType Type, TArray<int> Data);

private:

	UPROPERTY()
	FOnMessageReceivedDelegate OnMessageReceivedDelegate;
};