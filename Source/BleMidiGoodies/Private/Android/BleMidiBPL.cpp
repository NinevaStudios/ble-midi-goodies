// Copyright (c) 2023 Nineva Studios

#include "BleMidiBPL.h"

#include "BleMidiManager.h"

UBleMidiManager* UBleMidiBPL::CreateMidiManager()
{
	return NewObject<UBleMidiManager>();	
}
