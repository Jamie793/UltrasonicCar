package blog.jamiexu.cn.carulrtajoystick;

import static blog.jamiexu.cn.carulrtajoystick.ConnectionStatus.InfoType.CONNECT;
import static blog.jamiexu.cn.carulrtajoystick.ConnectionStatus.InfoType.DISCONNECT;
import static blog.jamiexu.cn.carulrtajoystick.ConnectionStatus.InfoType.HEART;
import static blog.jamiexu.cn.carulrtajoystick.ConnectionStatus.InfoType.OPERATION;

public class ConnectionStatus {
    public static boolean connectionStatus = false;
    public static boolean connectionHeart = false;
    public static final byte[] BLUETOOTH_HEADER = {0x05, 0x02};
    public static final byte[] BLUETOOTH_ENDING = {0x05, 0x04};

    public enum InfoType {
        CONNECT, //0
        DISCONNECT,//1
        OPERATION,//2
        HEART,//3
    }

    public enum ConnectStatus {
        CONNECT_SUCCESSFUL,
        CONNECT_FAILUR,
        CONNECT_INTERRUPT
    }


    public static InfoType getInfoType(short v) {
        InfoType type = null;
        switch (v) {
            case 0:
                type = CONNECT;
                break;
            case 1:
                type = DISCONNECT;
                break;
            case 2:
                type = OPERATION;
                break;
            case 3:
                type = HEART;
                break;
        }
        return type;
    }


    public static short getInfoType(InfoType v) {
        short n = -1;
        switch (v) {
            case CONNECT:
                n = 0;
                break;
            case DISCONNECT:
                n = 1;
                break;
            case OPERATION:
                n = 2;
                break;
            case HEART:
                n = 3;
                break;
        }
        return n;
    }

}
