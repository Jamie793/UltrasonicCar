package blog.jamiexu.cn.carulrtajoystick;


import android.Manifest;
import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.os.Process;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Set;
import java.util.UUID;

import io.github.controlwear.virtual.joystick.android.JoystickView;

//import
@SuppressWarnings("all")
@SuppressLint("all")
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private JoystickView JoystickViewLeft;
    private JoystickView JoystickViewRight;
    private Button btn_connect;
    private BluetoothAdapter bluetoothAdapter;
    private ProgressDialog progressDialog;
    public BluetoothSocket mSocket;
    public BluetoothSocketProtocol bluetoothSocketProtocol;
    private final String TAG = "MainActivity";
    private final String BLUETOOTH_UUID = "00001101-0000-1000-8000-00805f9b34fb";
    private final String BLUETOOTH_PIN = "Jamiexu123";

    private final String[] PERMISSIONS = new String[]{
            Manifest.permission.BLUETOOTH,
            Manifest.permission.BLUETOOTH_ADMIN,
            Manifest.permission.ACCESS_COARSE_LOCATION
    };

    private Set<BluetoothDevice> bluetoothDevices;


    public Handler handler = new Handler(Looper.getMainLooper(), new Handler.Callback() {
        @Override
        public boolean handleMessage(@NonNull Message message) {
            switch (message.what) {
                case 0:
                    switch ((ConnectionStatus.ConnectStatus) message.obj) {
                        case CONNECT_FAILUR:
                            if (bluetoothSocketProtocol != null)
                                bluetoothSocketProtocol.close();
                            if (mSocket != null) {
                                try {
                                    mSocket.close();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                            Toast.makeText(MainActivity.this, "连接Car车失败v~v", Toast.LENGTH_SHORT).show();
                            progressDialog.dismiss();
                            break;
                        case CONNECT_SUCCESSFUL:
                            MainActivity.this.btn_connect.setText("取消连接");
                            Toast.makeText(MainActivity.this, "连接Car车成功^-^", Toast.LENGTH_SHORT).show();
                            progressDialog.dismiss();
                            break;
                        case CONNECT_INTERRUPT:
                            Toast.makeText(MainActivity.this, "连接中断》。。", Toast.LENGTH_SHORT).show();
                            MainActivity.this.btn_connect.setText("点击连接");
                            break;
                    }
                    break;
            }
            return false;
        }
    });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        JoystickViewLeft = findViewById(R.id.joystick_left);
        JoystickViewRight = findViewById(R.id.joystick_right);
        btn_connect = findViewById(R.id.btn_connect);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        // 保持屏幕常亮
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        init();

        initUI();

    }


    public void init() {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            this.requestPermissions(PERMISSIONS, 0);
        }

        bluetoothAdapter = ((BluetoothManager) this.getSystemService(Context.BLUETOOTH_SERVICE)).getAdapter();
        if (bluetoothAdapter == null || !bluetoothAdapter.isEnabled()) {
            Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(intent);
        }


        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        registerReceiver(mReceiver, intentFilter);

        new Thread(new Runnable() {
            @Override
            public void run() {
                MainActivity.this.bluetoothDevices = bluetoothAdapter.getBondedDevices();
            }
        }).start();
    }


    public void initUI() {

        btn_connect.setOnClickListener(this);
        JoystickViewLeft.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                Logger.i("Joystick1", "angle: " + angle + ", strength: " + strength + ", direction: " + TouchMove.calc(angle));
                TouchMove.MoveStatus moveStatus = TouchMove.calc(angle);
                if (angle == 0 || moveStatus == TouchMove.MoveStatus.LEFT || moveStatus == TouchMove.MoveStatus.UP
                        || moveStatus == TouchMove.MoveStatus.RIGHT || moveStatus == TouchMove.MoveStatus.DOWN) {
                    if (ConnectionStatus.connectionStatus)
                        bluetoothSocketProtocol.sendSingal(ConnectionStatus.InfoType.OPERATION, moveStatus.toString(), strength);
                }
            }
        });
        JoystickViewRight.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                Logger.i("Joystick2", "angle: " + angle + ", strength: " + strength + ", direction: " + TouchMove.calc(angle));
                TouchMove.MoveStatus moveStatus = TouchMove.calc(angle);
                if (angle == 0 || moveStatus == TouchMove.MoveStatus.lEFT_UP || moveStatus == TouchMove.MoveStatus.lEFT_DOWN
                        || moveStatus == TouchMove.MoveStatus.RIGHT_UP || moveStatus == TouchMove.MoveStatus.RIGHT_DOWN) {
                    if (ConnectionStatus.connectionStatus)
                        bluetoothSocketProtocol.sendSingal(ConnectionStatus.InfoType.OPERATION, moveStatus.toString(), strength);
                }
            }
        });

    }


    public void createConnection(BluetoothDevice device) {
        try {
            device.setPin(MainActivity.this.BLUETOOTH_PIN.getBytes(StandardCharsets.UTF_8));
            device.createBond();
            mSocket = device.createRfcommSocketToServiceRecord(UUID.fromString(BLUETOOTH_UUID));
            mSocket.connect();
            progressDialog.setMessage("连接成功，等待小车连接应答<-_->...");
            bluetoothSocketProtocol = new BluetoothSocketProtocol(this, mSocket);
            bluetoothSocketProtocol.connect();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    if (!ConnectionStatus.connectionStatus)
                        handler.obtainMessage(0, ConnectionStatus.ConnectStatus.CONNECT_FAILUR).sendToTarget();
                }
            }, 1000 * 30);
        } catch (IOException e) {
            e.printStackTrace();
            handler.obtainMessage(0, ConnectionStatus.ConnectStatus.CONNECT_FAILUR).obtain();
        }
    }


    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_connect:
                if (this.btn_connect.getText().toString().equals("取消连接")) {
                    this.bluetoothSocketProtocol.sendSingal(ConnectionStatus.InfoType.CONNECT, "DECONNECT", 0);
                    if (this.bluetoothSocketProtocol != null)
                        this.bluetoothSocketProtocol.close();


                    if (this.mSocket != null) {
                        try {
                            this.mSocket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                    this.btn_connect.setText("连接小车");
                    Toast.makeText(MainActivity.this, "已取消连接", Toast.LENGTH_SHORT).show();
                    return;
                }
                progressDialog = new ProgressDialog(MainActivity.this);
                progressDialog.setTitle("提示：");
                progressDialog.setMessage("正在扫描并连接小车中，请稍后...");
                progressDialog.setCancelable(false);
                progressDialog.setButton(progressDialog.BUTTON_POSITIVE, "取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        bluetoothAdapter.cancelDiscovery();
                        progressDialog.dismiss();
                    }
                });
                progressDialog.show();

                for (BluetoothDevice device :
                        bluetoothDevices) {
                    if (device.getUuids() != null && device.getUuids()[0].toString().equals(BLUETOOTH_UUID)) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                createConnection(device);
                            }
                        }).start();
                        return;
                    }
                }

                if (!bluetoothAdapter.isDiscovering()) {
                    if (!bluetoothAdapter.startDiscovery()) {
                        Toast.makeText(MainActivity.this, "扫描失败...", Toast.LENGTH_SHORT).show();
                        progressDialog.dismiss();
                        return;
                    }

                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            bluetoothAdapter.cancelDiscovery();
                        }
                    }, 1000 * 60);
                }
                break;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == 0) {
            for (int i = 0; i < grantResults.length; i++) {
                if (grantResults[i] != PackageManager.PERMISSION_GRANTED)
                    showDialog();
            }
        } else {
            showDialog();
        }
    }

    public void showDialog() {
        AlertDialog alertDialog = new android.app.AlertDialog.Builder(this)
                .setTitle("温馨提示：")
                .setMessage("为了确保本程序的功能能正常的使用， 请给予本程序位置与蓝牙权限")
                .setPositiveButton("确定", (dialogInterface, i) -> {
                    killMyself();
                })
                .setCancelable(false).create();
        alertDialog.show();

    }

    public void killMyself() {
        Process.killProcess(Process.myPid());
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mReceiver);
        if (mSocket != null) {
            try {
                mSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        if (bluetoothSocketProtocol != null)
            bluetoothSocketProtocol.close();
    }


    private BroadcastReceiver mReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

                Logger.i(TAG, "[Device] --> " + device.getName() + "------" + device.getAddress()
                        + "-----" + Arrays.toString(device.getUuids()));

                if (device.getUuids() != null && device.getUuids()[0].toString().equals(BLUETOOTH_UUID)) {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            createConnection(device);
                        }
                    }).start();

                }
            }
        }
    };

}