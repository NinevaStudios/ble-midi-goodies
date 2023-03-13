package com.ninevastudios.blemidilib;


import android.util.Log;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import jp.kshoji.blemidi.device.MidiInputDevice;
import jp.kshoji.blemidi.listener.OnMidiInputEventListener;

@Keep
public class InputDevice implements OnMidiInputEventListener {
	public static native void OnMessageReceived(long callbackAdr, int type, int[] data);

	private final MidiInputDevice _device;
	private long _callbackAdr;

	public InputDevice(MidiInputDevice device) {
		_device = device;
	}

	public void bindCallback(long callbackAdr) {
		_callbackAdr = callbackAdr;
		_device.setOnMidiInputEventListener(this);
	}

	@Keep
	public String getName() {
		return _device.getDeviceName();
	}

	@Keep
	public String getAddress() {
		return _device.getDeviceAddress();
	}

	public MidiInputDevice getDevice() {
		return _device;
	}

	@Override
	public void onMidiSystemExclusive(@NonNull MidiInputDevice midiInputDevice, @NonNull byte[] bytes) {
		Log.d("InputDevice", "onMidiSystemExclusive: ");

		int[] result = new int[bytes.length];
		for (int i = 0; i < bytes.length; i++) {
			result[i] = bytes[i];
		}

		OnMessageReceived(_callbackAdr, MessageType.SystemExclusive, result);
	}

	@Override
	public void onMidiNoteOff(@NonNull MidiInputDevice midiInputDevice, int channel, int note, int velocity) {
		Log.d("InputDevice", "onMidiNoteOff: ");

		int[] result = new int[]{channel, note, velocity};
		OnMessageReceived(_callbackAdr, MessageType.NoteOff, result);
	}

	@Override
	public void onMidiNoteOn(@NonNull MidiInputDevice midiInputDevice, int channel, int note, int velocity) {
		Log.d("InputDevice", "onMidiNoteOn: ");

		int[] result = new int[]{channel, note, velocity};
		OnMessageReceived(_callbackAdr, MessageType.NoteOn, result);
	}

	@Override
	public void onMidiPolyphonicAftertouch(@NonNull MidiInputDevice midiInputDevice, int channel, int note, int pressure) {
		Log.d("InputDevice", "onMidiPolyphonicAftertouch: ");

		int[] result = new int[]{channel, note, pressure};
		OnMessageReceived(_callbackAdr, MessageType.PolyphonicAftertouch, result);
	}

	@Override
	public void onMidiControlChange(@NonNull MidiInputDevice midiInputDevice, int channel, int function, int value) {
		Log.d("InputDevice", "onMidiControlChange: ");

		int[] result = new int[]{channel, function, value};
		OnMessageReceived(_callbackAdr, MessageType.ControlChange, result);
	}

	@Override
	public void onMidiProgramChange(@NonNull MidiInputDevice midiInputDevice, int channel, int program) {
		Log.d("InputDevice", "onMidiProgramChange: ");

		int[] result = new int[]{channel, program};
		OnMessageReceived(_callbackAdr, MessageType.ProgramChange, result);
	}

	@Override
	public void onMidiChannelAftertouch(@NonNull MidiInputDevice midiInputDevice, int channel, int pressure) {
		Log.d("InputDevice", "onMidiChannelAftertouch: ");

		int[] result = new int[]{channel, pressure};
		OnMessageReceived(_callbackAdr, MessageType.ChannelAftertouch, result);
	}

	@Override
	public void onMidiPitchWheel(@NonNull MidiInputDevice midiInputDevice, int channel, int amount) {
		Log.d("InputDevice", "onMidiPitchWheel: ");

		int[] result = new int[]{channel, amount};
		OnMessageReceived(_callbackAdr, MessageType.PitchWheel, result);
	}

	@Override
	public void onMidiTimeCodeQuarterFrame(@NonNull MidiInputDevice midiInputDevice, int timing) {
		Log.d("InputDevice", "onMidiTimeCodeQuarterFrame: ");

		int[] result = new int[]{timing};
		OnMessageReceived(_callbackAdr, MessageType.TimeCodeQuarterFrame, result);
	}

	@Override
	public void onMidiSongSelect(@NonNull MidiInputDevice midiInputDevice, int song) {
		Log.d("InputDevice", "onMidiSongSelect: ");

		int[] result = new int[]{song};
		OnMessageReceived(_callbackAdr, MessageType.SongSelect, result);
	}

	@Override
	public void onMidiSongPositionPointer(@NonNull MidiInputDevice midiInputDevice, int position) {
		Log.d("InputDevice", "onMidiSongPositionPointer: ");

		int[] result = new int[]{position};
		OnMessageReceived(_callbackAdr, MessageType.SongPositionPointer, result);
	}

	@Override
	public void onMidiTuneRequest(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiTuneRequest: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.TuneRequest, result);
	}

	@Override
	public void onMidiTimingClock(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiTimingClock: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.TimingClock, result);
	}

	@Override
	public void onMidiStart(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiStart: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.Start, result);
	}

	@Override
	public void onMidiContinue(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiContinue: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.Continue, result);
	}

	@Override
	public void onMidiStop(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiStop: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.Stop, result);
	}

	@Override
	public void onMidiActiveSensing(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiActiveSensing: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.ActiveSensing, result);
	}

	@Override
	public void onMidiReset(@NonNull MidiInputDevice midiInputDevice) {
		Log.d("InputDevice", "onMidiReset: ");

		int[] result = new int[0];
		OnMessageReceived(_callbackAdr, MessageType.Reset, result);
	}

	@Override
	public void onRPNMessage(@NonNull MidiInputDevice midiInputDevice, int channel, int function, int value) {
		Log.d("InputDevice", "onRPNMessage: ");

		int[] result = new int[]{channel, function, value};
		OnMessageReceived(_callbackAdr, MessageType.RPN, result);
	}

	@Override
	public void onNRPNMessage(@NonNull MidiInputDevice midiInputDevice, int channel, int function, int value) {
		Log.d("InputDevice", "onNRPNMessage: ");

		int[] result = new int[]{channel, function, value};
		OnMessageReceived(_callbackAdr, MessageType.NRPN, result);
	}
}
