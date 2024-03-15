package blog.jamiexu.cn.carulrtajoystick;

public class TouchMove {
    public enum MoveStatus {
        lEFT_UP,
        RIGHT_UP,
        lEFT_DOWN,
        RIGHT_DOWN,
        UP,
        DOWN,
        LEFT,
        RIGHT
    }

    public static MoveStatus calc(int angle) {
        if (angle <= 22.5 || angle >= 337.5)
            return MoveStatus.RIGHT;
        else if (angle >= 22.5 && angle <= 67.5)
            return MoveStatus.RIGHT_UP;
        else if (angle >= 67.5 && angle <= 112.5)
            return MoveStatus.UP;
        else if (angle >= 112.5 && angle <= 157.5)
            return MoveStatus.lEFT_UP;
        else if (angle >= 157.5 && angle <= 202.5)
            return MoveStatus.LEFT;
        else if (angle >= 202.5 && angle <= 247.5)
            return MoveStatus.lEFT_DOWN;
        else if (angle >= 247.5 && angle <= 292.5)
            return MoveStatus.DOWN;
        else if (angle >= 292.5 && angle <= 337.5)
            return MoveStatus.RIGHT_DOWN;
        return null;
    }
}
