void parallelHall()
{
  mm = sonar_mm();

  myservo.write(180);
  Serial.println(mm);
  if (mm < 95)
  {
    // Turn Right
    motorCtrlAlloc(1, 0, 90, 90);
  }
  else if (mm > 105)
  {
    // Turn Left
    motorCtrlAlloc(0, 1, 90, 90);
  }
  else
  {
    motorCtrlAlloc(1, 1, 90, 90);
  }
  parallelHallDone = true;
}
