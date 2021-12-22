void parkingParallelChk()
{
  // Stop the car
  motorCtrlAlloc(1, 1, 0, 0);
  Serial.println("Checking in progress");
  for (pos = 75; pos <= 130; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(5); // waits 7ms for the servo to reach the position
    ValueM = sonar_mm();
    Serial.println(ValueM);
    if (ValueM > parallel_dist)
      is_parallel = true;

  }
  for (pos = 130; pos >= 74; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    ValueM = sonar_mm();
    Serial.println(ValueM);
    if (ValueM > parallel_dist)
      is_parallel = true;
  }

  for (pos = 74; pos >= 30; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5); // waits 15ms for the servo to reach the position
    ValueM = sonar_mm();
    Serial.println(ValueM);
    if (ValueM > parallel_dist)
      is_parallel = true;
  }
  for (pos = 30; pos < 75; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
    ValueM = sonar_mm();
    Serial.println(ValueM);
    if (ValueM > parallel_dist)
      is_parallel = true;
  }
  if (is_parallel)
  {
    Serial.println("Parallel hallway detected");
    parallel_check = false;
    is_parking = false;
  }
  else
  {
    Serial.println("Parking detected");
    is_parallel = false;
    parallel_check = false;
    is_parking = true;
  }
}
