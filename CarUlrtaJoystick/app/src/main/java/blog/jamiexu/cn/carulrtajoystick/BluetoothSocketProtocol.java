package blog.jamiexu.cn.carulrtajoystick;

import android.bluetooth.BluetoothSocket;

import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Timer;
import java.util.TimerTask;

public class BluetoothSocketProtocol {

    private MainActivity context;
    private BluetoothSocket mSocket;
    private DataOutputStream mDataOutputStream;
    private ReceiveDataThread receiveDataThread;

    public BluetoothSocketProtocol(MainActivity context, BluetoothSocket mSocket) {
        this.context = context;
        this.mSocket = mSocket;
    }

    public void sendSingal(ConnectionStatus.InfoType infoType, String cmd, int strength) {
        try {
            mDataOutputStream.flush();
            mDataOutputStream.write(ConnectionStatus.BLUETOOTH_HEADER);
            mDataOutputStream.writeShort(ConnectionStatus.getInfoType(infoType));
            mDataOutputStream.writeShort(cmd.length() + 4);
            mDataOutputStream.writeShort(cmd.length());
            mDataOutputStream.write(cmd.getBytes(StandardCharsets.UTF_8));
            mDataOutputStream.writeShort(strength);
            mDataOutputStream.write(ConnectionStatus.BLUETOOTH_ENDING);
            mDataOutputStream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void connect() {
        try {
            mDataOutputStream = new DataOutputStream((this.mSocket.getOutputStream()));
            sendSingal(ConnectionStatus.InfoType.CONNECT, "CONNECT", 0);
            this.receiveDataThread = new ReceiveDataThread(this.context, this);
            this.receiveDataThread.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void close() {
        this.receiveDataThread.close();
        if (mDataOutputStream != null) {
            try {
                mDataOutputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


}
