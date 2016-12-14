package org.qtproject.lamp;

/**
 * Created by tamvh on 08/10/2016.
 */

import android.annotation.TargetApi;
import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothManager;
import android.bluetooth.le.AdvertiseCallback;
import android.bluetooth.le.AdvertiseData;
import android.bluetooth.le.AdvertiseSettings;
import android.bluetooth.le.BluetoothLeAdvertiser;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;
import android.app.Notification;
import android.app.NotificationManager;

import java.io.Console;
import java.lang.reflect.Array;
import java.util.concurrent.TimeUnit;

/**
 * Manages BLE Advertising independent of the main app.
 * If the app goes off screen (or gets killed completely) advertising can continue because this
 * Service is maintaining the necessary Callback in memory.
 */
public class AdvertiserService extends Service {
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static AdvertiserService m_instance;

    private static final String TAG = AdvertiserService.class.getSimpleName();

    /**
     * A global variable to let AdvertiserFragment check if the Service is running without needing
     * to start or bind to it.
     * This is the best practice method as defined here:
     * https://groups.google.com/forum/#!topic/android-developers/jEvXMWgbgzE
     */
    public static boolean running = false;

    public static final String ADVERTISING_FAILED =
            "com.example.android.bluetoothadvertisements.advertising_failed";

    public static final String ADVERTISING_FAILED_EXTRA_CODE = "failureCode";

    public static final int ADVERTISING_TIMED_OUT = 6;

    private BluetoothLeAdvertiser mBluetoothLeAdvertiser;

    private AdvertiseCallback mAdvertiseCallback;

    private Handler mHandler;

    private Runnable timeoutRunnable;

    /**
     * Length of time to allow advertising before automatically shutting off. (10 minutes)
     */
    private long TIMEOUT = TimeUnit.MILLISECONDS.convert(3, TimeUnit.SECONDS);

    @Override
    public void onCreate() {
        Log.d(TAG, "onCreate Advertiser Service");
        running = true;
        initialize();
        startAdvertising();
        setTimeout();
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        /**
         * Note that onDestroy is not guaranteed to be called quickly or at all. Services exist at
         * the whim of the system, and onDestroy can be delayed or skipped entirely if memory need
         * is critical.
         */
        Log.d(TAG, "onDestroy Advertiser Service");
        running = false;
        stopAdvertising();
        mHandler.removeCallbacks(timeoutRunnable);
        super.onDestroy();
    }

    /**
     * Required for extending service, but this will be a Started Service only, so no need for
     * binding.
     */
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    /**
     * Get references to system Bluetooth objects if we don't have them already.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private void initialize() {
        try {
            if (mBluetoothLeAdvertiser == null) {
                BluetoothManager mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
                if (mBluetoothManager != null) {
                    BluetoothAdapter mBluetoothAdapter = mBluetoothManager.getAdapter();
                    if (mBluetoothAdapter != null) {
                        mBluetoothLeAdvertiser = mBluetoothAdapter.getBluetoothLeAdvertiser();
                    } else {
                        Toast.makeText(this, "BLE NULL", Toast.LENGTH_LONG).show();
                    }
                } else {
                    Toast.makeText(this, "BLE NULL", Toast.LENGTH_LONG).show();
                }
            }
        } catch (Exception ex) {
            Log.d(TAG, "ex initialize: " + ex.getMessage());
        }
    }

    /**
     * Starts a delayed Runnable that will cause the BLE Advertising to timeout and stop after a
     * set amount of time.
     */
    private void setTimeout() {
        mHandler = new Handler();
        try {
            timeoutRunnable = new Runnable() {
                @Override
                public void run() {
                    Log.d(TAG, "AdvertiserService has reached timeout of " + TIMEOUT + " milliseconds, stopping advertising.");
                    sendFailureIntent(ADVERTISING_TIMED_OUT);
                    stopSelf();
                }
            };
            mHandler.postDelayed(timeoutRunnable, TIMEOUT);
        } catch (Exception ex) {
            Log.d(TAG, "ex setTimeout: " + ex.getMessage());
        }
    }

    /**
     * Starts BLE Advertising.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private void startAdvertising() {
        Log.d(TAG, "Service: Starting Advertising");
        try {
            if (mAdvertiseCallback == null) {
                AdvertiseSettings settings = buildAdvertiseSettings();
                AdvertiseData data = buildAdvertiseData();
                mAdvertiseCallback = new SampleAdvertiseCallback();

                if (mBluetoothLeAdvertiser != null) {
                    mBluetoothLeAdvertiser.startAdvertising(settings, data,
                            mAdvertiseCallback);
                    Log.d(TAG, "Send data finish");
                }
            }
        } catch (Exception ex) {
            Log.d(TAG, "ex startAdvertising: " + ex.getMessage());
        }
    }

    /**
     * Stops BLE Advertising.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private void stopAdvertising() {
        Log.d(TAG, "Service: Stopping Advertising");
        try {
            if (mBluetoothLeAdvertiser != null) {
                mBluetoothLeAdvertiser.stopAdvertising(mAdvertiseCallback);
                mAdvertiseCallback = null;
            }
        } catch (Exception ex) {
            Log.d(TAG, "ex stopAdvertising: " + ex.getMessage());
        }
    }

    /**
     * Returns an AdvertiseData object which includes the Service UUID and Device Name.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private AdvertiseData buildAdvertiseData() {

        /**
         * Note: There is a strict limit of 31 Bytes on packets sent over BLE Advertisements.
         *  This includes everything put into AdvertiseData including UUIDs, device info, &
         *  arbitrary service or manufacturer data.
         *  Attempting to send packets over this limit will result in a failure with error code
         *  AdvertiseCallback.ADVERTISE_FAILED_DATA_TOO_LARGE. Catch this error in the
         *  onStartFailure() method of an AdvertiseCallback implementation.
         */
        Log.e(TAG, "pass: " + String.valueOf(Common.hex2decimal(MainActivity.arr_password[0])));
        Log.e(TAG, "pass: " + String.valueOf(Common.hex2decimal(MainActivity.arr_password[1])));
        Log.e(TAG, "slave: " + String.valueOf(Common.hex2decimal(MainActivity.arr_slave[0])));
        Log.e(TAG, "slave: " + String.valueOf(Common.hex2decimal(MainActivity.arr_slave[1])));
        Log.e(TAG, "slave: " + String.valueOf(Common.hex2decimal(MainActivity.arr_slave[2])));
        Log.e(TAG, "slave: " + String.valueOf(Common.hex2decimal(MainActivity.arr_slave[3])));

        byte[] arvalue = new byte[24];

        arvalue[0] = (byte) Common.hex2decimal(MainActivity.arr_password[0]); //Password.
        arvalue[1] = (byte) Common.hex2decimal(MainActivity.arr_password[1]);

        arvalue[2] = (byte) 0x31; //Direction and Protocol Version (0x31: Phone)

        arvalue[3] = (byte) 0x11; //ID Master
        arvalue[4] = (byte) 0x22;
        arvalue[5] = (byte) 0x33;
        arvalue[6] = (byte) 0x44;

        arvalue[7] = (byte) Common.hex2decimal(MainActivity.arr_slave[0]); //ID Slave
        arvalue[8] = (byte) Common.hex2decimal(MainActivity.arr_slave[1]);
        arvalue[9] = (byte) Common.hex2decimal(MainActivity.arr_slave[2]);
        arvalue[10] = (byte) Common.hex2decimal(MainActivity.arr_slave[3]);

        arvalue[11] = MainActivity.arr_cmd[0]; //Command
        arvalue[12] = MainActivity.arr_cmd[1];

        arvalue[13] = (byte) Common.hex2decimal(MainActivity.s_value); //Value
        arvalue[14] = (byte) 0x00;
        arvalue[15] = (byte) 0x00;
        arvalue[16] = (byte) 0x00;
        arvalue[17] = (byte) 0x00;
        arvalue[18] = (byte) 0x00;
        arvalue[19] = (byte) 0x00;
        arvalue[20] = (byte) 0x00;
        arvalue[21] = (byte) 0x00;
        arvalue[22] = (byte) 0x00;
        arvalue[23] = (byte) 0x00;

//        arvalue[0] = (byte) 0x02;
//        arvalue[1] = (byte) 0x15;
//
//        arvalue[2] = (byte) Common.hex2decimal(MainActivity.arr_password[0]); //Password
//        arvalue[3] = (byte) Common.hex2decimal(MainActivity.arr_password[1]);
//
//        arvalue[4] = (byte) 0x31; //Direction and Protocol Version (0x31: Phone)
//
//        arvalue[5] = (byte) 0x11; //ID Master
//        arvalue[6] = (byte) 0x22;
//        arvalue[7] = (byte) 0x33;
//        arvalue[8] = (byte) 0x44;
//
//        arvalue[9] = (byte) Common.hex2decimal(MainActivity.arr_slave[0]); //ID Slave
//        arvalue[10] = (byte) Common.hex2decimal(MainActivity.arr_slave[1]);
//        arvalue[11] = (byte) Common.hex2decimal(MainActivity.arr_slave[2]);
//        arvalue[12] = (byte) Common.hex2decimal(MainActivity.arr_slave[3]);
//
//        arvalue[13] = MainActivity.arr_cmd[0]; //Command
//        arvalue[14] = MainActivity.arr_cmd[1];
//
//        arvalue[15] = (byte) Common.hex2decimal(MainActivity.s_value); //Value
//        arvalue[16] = MainActivity.arr_cmd[2];
//        arvalue[17] = MainActivity.arr_cmd[3];
//        arvalue[18] = (byte) 0x00;
//        arvalue[19] = (byte) 0x00;
//        arvalue[20] = (byte) 0x00;
//        arvalue[21] = (byte) 0x00;
//        arvalue[22] = (byte) 0x00;
//        arvalue[23] = (byte) 0x00;

        AdvertiseData.Builder dataBuilder = new AdvertiseData.Builder();
        dataBuilder.addManufacturerData(Integer.parseInt(MainActivity.s_number), arvalue);

        return dataBuilder.build();
    }

    /**
     * Returns an AdvertiseSettings object set to use low power (to help preserve battery life)
     * and disable the built-in timeout since this code uses its own timeout runnable.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private AdvertiseSettings buildAdvertiseSettings() {
        AdvertiseSettings.Builder settingsBuilder = new AdvertiseSettings.Builder();
        try {
            settingsBuilder.setAdvertiseMode(AdvertiseSettings.ADVERTISE_MODE_LOW_POWER);
//            settingsBuilder.setConnectable(false);
//            settingsBuilder.wait(100);
        } catch (Exception ex) {
            Log.d(TAG, "ex buildAdvertiseSettings: " + ex.getMessage());
        }
        return settingsBuilder.build();
    }

    /**
     * Custom callback after Advertising succeeds or fails to start. Broadcasts the error code
     * in an Intent to be picked up by AdvertiserFragment and stops this Service.
     */
    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private class SampleAdvertiseCallback extends AdvertiseCallback {

        @Override
        public void onStartFailure(int errorCode) {
            super.onStartFailure(errorCode);

            Log.d(TAG, "Advertising failed");
            sendFailureIntent(errorCode);
            stopSelf();

        }

        @Override
        public void onStartSuccess(AdvertiseSettings settingsInEffect) {
            super.onStartSuccess(settingsInEffect);
            Log.d(TAG, "Advertising successfully started");
        }
    }

    /**
     * Builds and sends a broadcast intent indicating Advertising has failed. Includes the error
     * code as an extra. This is intended to be picked up by the {@code AdvertiserFragment}.
     */
    private void sendFailureIntent(int errorCode) {
        Intent failureIntent = new Intent();
        failureIntent.setAction(ADVERTISING_FAILED);
        failureIntent.putExtra(ADVERTISING_FAILED_EXTRA_CODE, errorCode);
        sendBroadcast(failureIntent);
    }
}
