package org.qtproject.lamp;

/**
 * Created by tamvh on 08/10/2016.
 */

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.GraphRequest;
import com.facebook.GraphResponse;
import com.facebook.login.LoginResult;

import org.json.JSONObject;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {
    private static final String TAG = MainActivity.class.getSimpleName();
    public static MainActivity s_activity = null;
    public static int control = 0;
    public static int pwm = 0;

    User user;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        s_activity = this;
        super.onCreate(savedInstanceState);
    }
    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        s_activity = null;
    }
    public void startAdvertising() {
        Intent intent = new Intent(this, AdvertiserService.class);
        startService(intent);
    }
    public void stopAdvertising() {
        Intent intent = new Intent(this, AdvertiserService.class);
        stopService(intent);
    }
}