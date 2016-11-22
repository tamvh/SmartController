package org.qtproject.lamp;

/**
 * Created by tamvh on 08/10/2016.
 */

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {
    private static final String TAG = MainActivity.class.getSimpleName();
    public static MainActivity s_activity = null;
    public static int control = 0;
    public static int pwm = 0;

    public MainActivity() {
        s_activity = this;
    }

//    @Override
//    public void onCreate(Bundle savedInstanceState)
//    {
//        super.onCreate(savedInstanceState);
//        s_activity = this;
//    }
//    @Override
//    protected void onDestroy()
//    {
//        super.onDestroy();
//        s_activity = null;
//    }
    public static int onStartAdvertising(int action) {
        Log.d("BroadcastSend", "Start: " + action);
        if (s_activity != null)
            s_activity.startAdvertising();
        else
            Log.d(TAG, "Activity is NULL");
        return 0;
    }
    public static int onStopAdvertising(int action) {
        Log.d("BroadcastSend", "Stop: " + action);
        s_activity.stopAdvertising();
        return 0;
    }
    public void startAdvertising() {
        Log.d(TAG, "start Advertising: " + s_activity);
        Intent intent = new Intent(s_activity, AdvertiserService.class);
        startService(intent);
    }
    public void stopAdvertising() {
        Log.d(TAG, "stop Advertising");
        Intent intent = new Intent(s_activity, AdvertiserService.class);
        stopService(intent);
    }
}