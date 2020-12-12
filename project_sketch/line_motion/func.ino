
void getAngle()
{
  float K =0.90;
  angle_x = K*(angle_x + 57.2957f * (IMU.getGyroX_rads() - gyro_x_zero) * time_period/1000000.0) + (1 - K) * (5.3 + 57.2957f *  atan2(-(IMU.getAccelY_mss() - accel_y_zero), -(IMU.getAccelZ_mss() - accel_z_zero))); 
  angle_y = K*(angle_y + 57.2957f * (IMU.getGyroY_rads() - gyro_y_zero) * time_period/1000000.0) + (1 - K) * (1.4 + 57.2957f *  atan2(-(IMU.getAccelX_mss() - accel_x_zero), -(IMU.getAccelZ_mss() - accel_z_zero)));
  //angle_z = K*(angle_z + 57.2957f * (IMU.getGyroZ_rads() - gyro_z_zero) * time_period/1000000.0) + (1 - K) * (135 + 57.2957f  *  atan2(-IMU.getAccelY_mss()+ accel_y_zero, -IMU.getAccelX_mss() + accel_x_zero));
  angle_z += 57.2957f * (IMU.getGyroZ_rads() - gyro_z_zero) * time_period/1000000.0;
}

void calibrate()
{ 
  int i = 0;
  int calibrate_num = 10000;
  while (i < calibrate_num)
  {
    if (timer < micros())
    {
      timer = micros + time_period;
      IMU.readSensor();
      gyro_x_zero += IMU.getGyroX_rads();
      gyro_y_zero += IMU.getGyroY_rads();
      gyro_z_zero += IMU.getGyroZ_rads();
      accel_x_zero += IMU.getGyroX_rads();
      accel_y_zero += IMU.getGyroY_rads();
      accel_z_zero += IMU.getGyroZ_rads();
      ++i;
    }
  }
  gyro_x_zero /= calibrate_num;
  gyro_y_zero /= calibrate_num;
  gyro_z_zero /= calibrate_num;
  accel_x_zero /= calibrate_num;
  accel_y_zero /= calibrate_num;
  accel_z_zero /= calibrate_num;
}
