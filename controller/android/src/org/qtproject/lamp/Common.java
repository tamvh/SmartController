package org.qtproject.lamp;

import android.annotation.TargetApi;
import android.bluetooth.le.AdvertiseSettings;
import android.os.Build;
import android.os.ParcelUuid;
import android.util.Log;

import java.util.HashMap;

/**
 * Created by tamvh on 09/10/2016.
 */

public class Common {
    private static final String TAG = Common.class.getSimpleName();
    public static String ServiceId = "6e400001-b5a3-f393-e0a9-e50e24dcca9e";
    public static String writeCharacteristicId02 = "6e400002-b5a3-f393-e0a9-e50e24dcca9e"; //control 1next, 2back, 3left, 4right, 0stop
    public static String writeCharacteristicId04 = "6e400004-b5a3-f393-e0a9-e50e24dcca9e"; //pwm 0- 255
    private static HashMap<String, String> attributes = new HashMap();
    public static String HEART_RATE_MEASUREMENT = "00002a37-0000-1000-8000-00805f9b34fb";
    public static String CLIENT_CHARACTERISTIC_CONFIG = "00002902-0000-1000-8000-00805f9b34fb";

    static {
        // Sample Services.
        attributes.put("0000180d-0000-1000-8000-00805f9b34fb", "Heart Rate Service");
        attributes.put("0000180a-0000-1000-8000-00805f9b34fb", "Device Information Service");
        // Sample Characteristics.
        attributes.put(HEART_RATE_MEASUREMENT, "Heart Rate Measurement");
        attributes.put("00002a29-0000-1000-8000-00805f9b34fb", "Manufacturer Name String");
    }

    public static String lookup(String uuid, String defaultName) {
        String name = attributes.get(uuid);
        return name == null ? defaultName : name;
    }

    public static final ParcelUuid Service_UUID = ParcelUuid.fromString("0000b81d-0000-1000-8000-00805f9b34fb");

    public static int hex2decimal(String s) {
        String digits = "0123456789ABCDEF";
        s = s.toUpperCase();
        int val = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int d = digits.indexOf(c);
            val = 16*val + d;
        }
        return val;
    }

    public static String convertStringToHex(String str) {
        char[] chars = str.toCharArray();
        StringBuffer hex = new StringBuffer();
        for (int i = 0; i < chars.length; i++) {
            hex.append(Integer.toHexString((int) chars[i]));
        }

        return hex.toString();
    }
    public static byte[] intToByteArray(int value) {
        byte[] ret = new byte[4];
        ret[0] = (byte) (value & 0xFF);
        ret[1] = (byte) ((value >> 8) & 0xFF);
        ret[2] = (byte) ((value >> 16) & 0xFF);
        ret[3] = (byte) ((value >> 24) & 0xFF);
        return ret;
    }
}
