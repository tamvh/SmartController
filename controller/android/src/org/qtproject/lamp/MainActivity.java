package org.qtproject.lamp;

/**
 * Created by tamvh on 08/10/2016.
 */

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import java.nio.ByteBuffer;

public class MainActivity extends org.qtproject.qt5.android.bindings.QtActivity {
    private static final String TAG = MainActivity.class.getSimpleName();
    public static MainActivity s_activity = null;
    public static int cmd = -1;
    public static int control = 0;
    public static int pwm = 0;

    public static String[] arr_password = new String[2];
    public static String[] arr_slave = new String[4];
    public static byte[] arr_cmd = new byte[4];
    public static String s_value;
    public static String s_number;

    public MainActivity() {
        s_activity = this;
    }

    public static int onStartAdvertising(
            String securityNumber,
            String password,
            String command,
            String value,
            String direction,
            String slave) {
        Log.d(TAG, "Security Number: " + securityNumber);
        Log.d(TAG, "Password: " + password);
        Log.d(TAG, "Common: " + command);
        Log.d(TAG, "Value: " + value);
        Log.d(TAG, "Direction: " + direction);
        Log.d(TAG, "Slave: " + slave);
        if (!password.isEmpty())
        {
            arr_password = password.split("-");
        }

        if(!slave.isEmpty()) {
            arr_slave = slave.split(":");
        }
        s_value = value;
        arr_cmd = Common.intToByteArray(Integer.parseInt(command));
        s_number = securityNumber;
        if (s_activity != null) {
            cmd = 0;
            s_activity.startAdvertising();
        } else {
            Log.d(TAG, "Activity is NULL");
        }
        return 0;
    }
    public static int onStopAdvertising(int action) {
        Log.d(TAG, "Stop: " + action);
        s_activity.stopAdvertising();
        return 0;
    }
    public void startAdvertising() {
        Intent intent = new Intent(s_activity, AdvertiserService.class);
        startService(intent);
    }
    public void stopAdvertising() {
        Intent intent = new Intent(s_activity, AdvertiserService.class);
        stopService(intent);
    }
}