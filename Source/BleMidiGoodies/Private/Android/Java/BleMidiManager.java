package com.ninevastudios.blemidilib;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.pm.PackageManager;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;

import java.util.ArrayList;
import java.util.List;

import jp.kshoji.blemidi.central.BleMidiCentralProvider;
import jp.kshoji.blemidi.device.MidiInputDevice;
import jp.kshoji.blemidi.device.MidiOutputDevice;
import jp.kshoji.blemidi.listener.OnMidiDeviceAttachedListener;
import jp.kshoji.blemidi.listener.OnMidiDeviceDetachedListener;
import jp.kshoji.blemidi.listener.OnMidiScanStatusListener;

@Keep
public class BleMidiManager {

	public static native void OnInputDeviceEvent(InputDevice device);
	public static native void OnOutputDeviceEvent(OutputDevice device);
	public static native void OnMidiScanStatusChanged(boolean status);
	private BleMidiCentralProvider bleMidiCentralProvider;
	private final BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
	private OnMidiScanStatusListener scanStatusListener;
	private OnMidiDeviceAttachedListener deviceAttachedListener;
	private OnMidiDeviceDetachedListener deviceDetachedListener;
	private boolean isInitialized = false;
	public BleMidiManager() {
	}

	@Keep
	public boolean initialize(Activity context) {
		if (!isBleSupported(context) || !isBluetoothEnabled())
			return false;

		bleMidiCentralProvider = new BleMidiCentralProvider(context);
		isInitialized = true;

		scanStatusListener = new OnMidiScanStatusListener() {
			@Override
			public void onMidiScanStatusChanged(boolean status) {
				OnMidiScanStatusChanged(status);
			}
		};

		bleMidiCentralProvider.setOnMidiScanStatusListener(scanStatusListener);

		deviceAttachedListener = new OnMidiDeviceAttachedListener() {
			@Override
			public void onMidiInputDeviceAttached(@NonNull MidiInputDevice midiInputDevice) {
				OnInputDeviceEvent(new InputDevice(midiInputDevice));
			}

			@Override
			public void onMidiOutputDeviceAttached(@NonNull MidiOutputDevice midiOutputDevice) {
				OnOutputDeviceEvent(new OutputDevice(midiOutputDevice));
			}
		};

		bleMidiCentralProvider.setOnMidiDeviceAttachedListener(deviceAttachedListener);

		deviceDetachedListener = new OnMidiDeviceDetachedListener() {
			@Override
			public void onMidiInputDeviceDetached(@NonNull MidiInputDevice midiInputDevice) {
				OnInputDeviceEvent(new InputDevice(midiInputDevice));
			}

			@Override
			public void onMidiOutputDeviceDetached(@NonNull MidiOutputDevice midiOutputDevice) {
				OnOutputDeviceEvent(new OutputDevice(midiOutputDevice));
			}
		};

		bleMidiCentralProvider.setOnMidiDeviceDetachedListener(deviceDetachedListener);

		return true;
	}

	@Keep
	public boolean isBleSupported(Activity activity) {
		return activity.getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE);
	}

	@Keep
	public boolean isBluetoothEnabled() {
		return mBluetoothAdapter != null && mBluetoothAdapter.isEnabled();
	}

	@Keep
	@SuppressLint("MissingPermission")
	public void setBluetoothState(boolean isEnabled) {
		if (mBluetoothAdapter == null)
			return;

		if (isEnabled) {
			mBluetoothAdapter.enable();
		} else {
			mBluetoothAdapter.disable();
		}
	}

	@Keep
	public void setRequestPairing(boolean needsPairing) {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.setRequestPairing(needsPairing);
	}

	@Keep
	public void startScan(int timeoutInMilliSeconds) {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.startScanDevice(timeoutInMilliSeconds);
	}

	@Keep
	public void stopScan() {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.stopScanDevice();
	}

	@Keep
	public void disconnectInputDevice(InputDevice midiInputDevice) {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.disconnectDevice(midiInputDevice.getDevice());
	}

	@Keep
	public void disconnectOutputDevice(OutputDevice midiOutputDevice) {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.disconnectDevice(midiOutputDevice.getDevice());
	}

	@Keep
	public InputDevice[] getMidiInputDevices() {
		ArrayList<InputDevice> result = new ArrayList<>();

		if (!isInitialized)
			return result.toArray(new InputDevice[0]);

		for (MidiInputDevice device : bleMidiCentralProvider.getMidiInputDevices()) {
			result.add(new InputDevice(device));
		}

		return result.toArray(new InputDevice[0]);
	}

	@Keep
	public OutputDevice[] getMidiOutputDevices() {
		ArrayList<OutputDevice> result = new ArrayList<>();

		if (!isInitialized)
			return result.toArray(new OutputDevice[0]);

		for (MidiOutputDevice device : bleMidiCentralProvider.getMidiOutputDevices()) {
			result.add(new OutputDevice(device));
		}

		return result.toArray(new OutputDevice[0]);
	}

	protected void finalize() {
		if (!isInitialized)
			return;

		bleMidiCentralProvider.terminate();
	}
}
