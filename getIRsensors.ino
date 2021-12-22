void getIRsensors()
{
  // Read the sensors
  R_sensor = digitalRead(A0);
  L_sensor = digitalRead(A1);
  M_sensor = digitalRead(A2);
}
