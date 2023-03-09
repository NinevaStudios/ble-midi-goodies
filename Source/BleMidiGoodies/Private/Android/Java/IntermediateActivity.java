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

		for (int result : grantResults) {
			if (result == PackageManager.PERMISSION_DENIED) {
				Utils.OnPermissionGrantResult(false);
				finish();
				return;
			}
		}

		Utils.OnPermissionGrantResult(true);
		finish();
	}
}
