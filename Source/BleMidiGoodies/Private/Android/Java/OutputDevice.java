package com.ninevastudios.blemidilib;

import androidx.annotation.Keep;

import jp.kshoji.blemidi.device.MidiOutputDevice;

public class OutputDevice {
	private final MidiOutputDevice _device;

	public OutputDevice(MidiOutputDevice device) {
		_device = device;
	}

	@Keep
	public String getName() {
		return _device.getDeviceName();
	}

	@Keep
	public String getAddress() {
		return _device.getDeviceAddress();
	}

	@Keep
	public void sendMessage(int type, int[] data) {
		switch (type) {
			case MessageType.SystemExclusive:
				byte[] result = new byte[data.length];
				for (int i = 0; i < data.length; i++) {
					result[i] = (byte) data[i];
				}

				_device.sendMidiSystemExclusive(result);
				break;
			case MessageType.NoteOff:
				_device.sendMidiNoteOff(data[0], data[1], data[2]);
			case MessageType.NoteOn:
				_device.sendMidiNoteOn(data[0], data[1], data[2]);
			case MessageType.PolyphonicAftertouch:
				_device.sendMidiPolyphonicAftertouch(data[0], data[1], data[2]);
			case MessageType.ControlChange:
				_device.sendMidiControlChange(data[0], data[1], data[2]);
			case MessageType.ProgramChange:
				_device.sendMidiProgramChange(data[0], data[1]);
			case MessageType.ChannelAftertouch:
				_device.sendMidiChannelAftertouch(data[0], data[1]);
			case MessageType.PitchWheel:
				_device.sendMidiPitchWheel(data[0], data[1]);
			case MessageType.TimeCodeQuarterFrame:
				_device.sendMidiTimeCodeQuarterFrame(data[0]);
			case MessageType.SongSelect:
				_device.sendMidiSongSelect(data[0]);
			case MessageType.SongPositionPointer:
				_device.sendMidiSongPositionPointer(data[0]);
			case MessageType.TuneRequest:
				_device.sendMidiTuneRequest();
			case MessageType.TimingClock:
				_device.sendMidiTimingClock();
			case MessageType.Start:
				_device.sendMidiStart();
			case MessageType.Continue:
				_device.sendMidiContinue();
			case MessageType.Stop:
				_device.sendMidiStop();
			case MessageType.ActiveSensing:
				_device.sendMidiActiveSensing();
			case MessageType.Reset:
				_device.sendMidiReset();
			case MessageType.RPN:
				_device.sendRPNMessage(data[0], data[1], data[2]);
			case MessageType.NRPN:
				_device.sendNRPNMessage(data[0], data[1], data[2]);
		}
	}

	public MidiOutputDevice getDevice() {
		return _device;
	}
}
