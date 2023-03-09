package com.ninevastudios.blemidilib;

public class MessageType
{
	final static int SystemExclusive = 0;
	final static int NoteOff = 1;
	final static int NoteOn = 2;
	final static int PolyphonicAftertouch = 3;
	final static int ControlChange = 4;
	final static int ProgramChange = 5;
	final static int ChannelAftertouch = 6;
	final static int PitchWheel = 7;
	final static int TimeCodeQuarterFrame = 8;
	final static int SongSelect = 9;
	final static int SongPositionPointer = 10;
	final static int TuneRequest = 11;
	final static int TimingClock = 12;
	final static int Start = 13;
	final static int Continue = 14;
	final static int Stop = 15;
	final static int ActiveSensing = 16;
	final static int Reset = 17;
	final static int RPN = 18;
	final static int NRPN = 19;
}
