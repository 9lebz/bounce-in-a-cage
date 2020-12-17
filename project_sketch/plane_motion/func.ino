
void getAngle()
{
  float K =0.99;
  angle_x = K*(angle_x + (IMU.getGyroX_rads() - gyro_x_zero) * time_period/1000000.0) + (1 - K) * (5.3 / 57.2957f + atan2(-(IMU.getAccelY_mss() - accel_y_zero), -(IMU.getAccelZ_mss() - accel_z_zero))); 
  angle_y = K*(angle_y + (IMU.getGyroY_rads() - gyro_y_zero) * time_period/1000000.0) + (1 - K) * (1.4 / 57.2957f +  atan2(-(IMU.getAccelX_mss() - accel_x_zero), -(IMU.getAccelZ_mss() - accel_z_zero)));
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

void getPos()
{
  s_x +=(abs(angle_x)>0.02 ? 5 * 9.80665 * sin(angle_x) * (time_period/1000000.0) * (1 + time_period/2000000.0) : 0);
  s_y +=(abs(angle_y)>0.02 ? 5 * 9.80665 * sin(angle_y) * (time_period/1000000.0) * (1 + time_period/2000000.0) : 0);
  if (abs(s_x) + 3.5 < 7 && abs(s_y) + 3.5 < 7)
  {
    pos_x = round(s_x + 3.6);
    pos_y = round(s_y + 3.6);
  }
  else if (abs(s_y) + 3.5 < 7)
  {
    pos_y = s_y + 3.6;
    if (s_x > 1 && angle_x < 0)
      s_x = 3.5;
    if (s_x < -1 && angle_x > 0)
      s_x = -3.5;
  }
  else if (abs(s_x) + 3.5 < 7)
  {
    pos_x =s_x + 3.6;
    if (s_y > 1 && angle_y < 0)
      s_y = 3.5;
    if (s_y < -1 && angle_y > 0)
      s_y = -3.5;
  }
  else 
  {
    if (s_x > 1 && angle_x < 0)
      s_x = 3.5;
    if (s_x < -1 && angle_x > 0)
      s_x = -3.5;
    if (s_y > 1 && angle_y < 0)
      s_y = 3.5;
    if (s_y < -1 && angle_y > 0)
      s_y = -3.5;
  }
}
