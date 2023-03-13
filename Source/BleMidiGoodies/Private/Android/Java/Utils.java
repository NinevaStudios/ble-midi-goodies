package com.ninevastudios.blemidilib;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;

import androidx.annotation.Keep;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;
import java.util.Collections;

public class Utils {
	public static native void OnPermissionGrantResult(String[] permissions, boolean[] granted);

	@Keep
	public static void requestBluetoothPermissions(Activity context) {
		String[] permissions;

		if (Build.VERSION.SDK_INT < Build.VERSION_CODES.S) {
			permissions = new String[]{Manifest.permission.ACCESS_FINE_LOCATION};
		} else {
			permissions = new String[]{
					Manifest.permission.BLUETOOTH_SCAN,
					Manifest.permission.BLUETOOTH_CONNECT};
		}

		requestPermissions(context, permissions);
	}

	@Keep
	public static void requestPermissions(Activity context, String[] permissions) {
		ArrayList<String> permissionsList = new ArrayList<>();
		Collections.addAll(permissionsList, permissions);

		Intent intent = new Intent(context, IntermediateActivity.class)
				.putExtra(IntermediateActivity.EXTRA_PERMISSIONS, permissionsList);
		try {
			context.startActivity(intent);
		} catch (Exception e) {
			e.printStackTrace();
			OnPermissionGrantResult(permissions, new boolean[permissions.length]);
		}
	}

	@Keep
	public static void openApplicationSettings(Activity context) {
		Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
		Uri uri = Uri.fromParts("package", context.getPackageName(), null);
		intent.setData(uri);
		context.startActivity(intent);
	}
}
