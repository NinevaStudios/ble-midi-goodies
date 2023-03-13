package com.ninevastudios.blemidilib;

import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Bundle;

import androidx.core.app.ActivityCompat;

import java.util.ArrayList;

public class IntermediateActivity extends Activity {
	public static final String EXTRA_PERMISSIONS = "EXTRA_PERMISSIONS";
	public static final int PERMISSION_REQUEST_CODE = 0;

	@SuppressWarnings("unchecked")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		ArrayList<String> permissions = (ArrayList<String>) getIntent().getSerializableExtra(EXTRA_PERMISSIONS);
		if (permissions == null) {
			finish();
			return;
		}

		requestPermissions(permissions.toArray(new String[0]));
	}

	private void requestPermissions(String[] permissions) {
		ActivityCompat.requestPermissions(this, permissions, PERMISSION_REQUEST_CODE);
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		if (requestCode != PERMISSION_REQUEST_CODE) {
			finish();
			return;
		}

		boolean[] granted = new boolean[grantResults.length];
		for (int i = 0; i < grantResults.length; i++) {
			granted[i] = grantResults[i] == PackageManager.PERMISSION_GRANTED;
		}

		Utils.OnPermissionGrantResult(permissions, granted);
		finish();
	}
}
