package blog.jamiexu.cn.carulrtajoystick;

import java.io.DataInputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Timer;
import java.util.TimerTask;

public class ReceiveDataThread extends Thread {
    private MainActivity context;
    private BluetoothSocketProtocol bluetoothSocketProtocol;
    private DataInputStream dataInputStream;
    private Timer timer;
    private Timer timer2;


    public ReceiveDataThread(MainActivity context, BluetoothSocketProtocol bluetoothSocketProtocol) {
        this.context = context;
        this.bluetoothSocketProtocol = bluetoothSocketProtocol;
        this.timer = new Timer();
        this.timer2 = new Timer();
    }

    @Override
    public void run() {
        super.run();
        try {
            dataInputStream = new DataInputStream(context.mSocket.getInputStream());
            while (context.mSocket.isConnected()) {
                if (dataInputStream.readByte() != ConnectionStatus.BLUETOOTH_HEADER[0] ||
                        dataInputStream.readByte() != ConnectionStatus.BLUETOOTH_HEADER[1])
                    continue;
                ConnectionStatus.InfoType type = ConnectionStatus.getInfoType(dataInputStream.readShort());
                short dataPackageSize = dataInputStream.readShort();
                short cmdLen = dataInputStream.readShort();
                switch (type) {
                    case CONNECT:
                        processConnect(dataPackageSize, cmdLen);
                        break;
                    case OPERATION:
                        processOperation(dataPackageSize, cmdLen);
                        break;
                    case HEART:
                        processHeart(dataPackageSize, cmdLen);
                        break;
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void processConnect(short dataPackageSize, short cmdLen) {
        byte[] data = new byte[1024];
        try {
            dataInputStream.read(data, 0, cmdLen);
            if (new String(data, 0, cmdLen, StandardCharsets.UTF_8).equals("OK")) {
                ConnectionStatus.connectionStatus = true;
                ConnectionStatus.connectionHeart = true;
                context.handler.obtainMessage(0, ConnectionStatus.ConnectStatus.CONNECT_SUCCESSFUL).sendToTarget();

//                this.timer.schedule(new TimerTask() {
//                    @Override
//                    public void run() {
//
//                    }
//                }, 0, 30 * 1000);


//                this.timer2.schedule(new TimerTask() {
//                    @Override
//                    public void run() {
//                        ConnectionStatus.connectionHeart = false;
//                        try {
//                            Thread.sleep(30000);
//                        } catch (InterruptedException e) {
//                            e.printStackTrace();
//                        }
//
//                        if (!ConnectionStatus.connectionHeart) {
//                            close();
//                            try {
//                                context.mSocket.close();
//                                timer.cancel();
//                                timer2.cancel();
//                                context.handler.obtainMessage(0, ConnectionStatus.ConnectStatus.CONNECT_INTERRUPT).sendToTarget();
//                            } catch (IOException e) {
//                                e.printStackTrace();
//                            }
//                        }
//                        bluetoothSocketProtocol.sendSingal(ConnectionStatus.InfoType.HEART, "HEART", 0);
//                    }
//                },0 , 3000);


            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void processHeart(short dataPackageSize, short cmdLen) {
        byte[] data = new byte[1024];
        try {
            dataInputStream.read(data, 0, cmdLen);
            if (new String(data, 0, cmdLen, StandardCharsets.UTF_8).equals("OK")) {
                ConnectionStatus.connectionHeart = true;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void processOperation(short dataPackageSize, short cmdLen) {
        byte[] data = new byte[1024];
        try {
            dataInputStream.read(data, 0, cmdLen);
            if (new String(data, 0, cmdLen, StandardCharsets.UTF_8).equals("OK")) {
                ConnectionStatus.connectionStatus = true;
                context.handler.obtainMessage(0, ConnectionStatus.ConnectStatus.CONNECT_SUCCESSFUL).sendToTarget();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void close() {
        if (this.dataInputStream != null) {
            try {
                this.dataInputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
