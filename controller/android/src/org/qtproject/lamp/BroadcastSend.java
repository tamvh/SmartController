package org.qtproject.lamp;

import android.util.Log;

/**
 * Created by tamvh on 08/10/2016.
 */

public class BroadcastSend {
    public static byte slave = 0x23;
    public static int onStartAdvertising(int action) {
        Log.d("BroadcastSend", "Action: " + action);
        MainActivity.s_activity.startAdvertising();
        return 0;
    }
    public static int onStopAdvertising(int action) {
        Log.d("BroadcastSend", "Stop: " + action);
        MainActivity.s_activity.stopAdvertising();
        return 0;
    }
}