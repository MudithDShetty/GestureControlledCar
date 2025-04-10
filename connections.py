import serial
import time


def main(mpu_port='COM4', car_port='COM5', baudrate_mpu=115200, baudrate_car=9600):
    try:
        mpu_ser = serial.Serial(mpu_port, baudrate_mpu, timeout=1)
        car_ser = serial.Serial(car_port, baudrate_car, timeout=1)

        print(f"[INFO] Connected to MPU ({mpu_port}) and Car ({car_port})")
        time.sleep(2)  # Allow devices to initialize

        last_command = None

        while True:
            if mpu_ser.in_waiting > 0:
                command = mpu_ser.readline().decode('utf-8').strip().lower()

                if command in ['w', 'a', 's', 'd', 'x'] and command != last_command:
                    car_ser.write(command.encode())
                    print(f"[FORWARDED] {command.upper()} to car")
                    last_command = command

                    # Optional: print car's response
                    while car_ser.in_waiting:
                        print(f"[CAR] {car_ser.readline().decode().strip()}")

    except KeyboardInterrupt:
        print("\n[EXIT] User interrupted.")
    except serial.SerialException as e:
        print(f"[ERROR] Serial exception: {e}")
    finally:
        if 'mpu_ser' in locals() and mpu_ser.is_open:
            mpu_ser.close()
            print("[CLOSED] MPU serial closed.")
        if 'car_ser' in locals() and car_ser.is_open:
            car_ser.close()
            print("[CLOSED] Car serial closed.")


if __name__ == "__main__":
    main()
