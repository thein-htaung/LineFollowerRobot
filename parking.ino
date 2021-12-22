void parking()
{
  if (goForSomeDistance)
  {
    // If the car turned to the right, turn left more
    Serial.println(prev_line_state);
    if (prev_line_state == 1)
    {
      Serial.println("Go left for some distance");
      motorCtrlAlloc(1, 1, left_speed, right_speed + 15);
      delay(550);
      motorCtrlAlloc(1, 1, 0, 0);
    }
    else if (prev_line_state == 2)
    {
      Serial.println("Go Right for some distance");
      motorCtrlAlloc(1, 1, left_speed + 10, right_speed);
      delay(550);
      motorCtrlAlloc(1, 1, 0, 0);
    }
    else
    {
      Serial.println("Go Straight for some distance");
      motorCtrlAlloc(1, 1, left_speed, right_speed);
      delay(550);
      motorCtrlAlloc(1, 1, 0, 0);
    }
    // Set it to false so that this block of code will only run once
    goForSomeDistance = 0;
  }
  

  myservo.write(180);
  delay(250);
  ValueL = sonar_mm();

  // Turn back to the middle
  myservo.write(75);
  delay(250);
  ValueM = sonar_mm();

  Serial.print("Front : ");
  Serial.print(ValueM);
  Serial.print(" Left : ");
  Serial.println(ValueL);

  if (ValueM > parking_dist)
  {
    if (ValueL < 75)
    {
      // Go Right
      Serial.println("Go Right");
      motorCtrlAlloc(1, 0, turn_speed + 10, turn_speed + 10);
      delay(150);
      motorCtrlAlloc(1, 0, 0, 0);
      delay(150);
    }
    else if (ValueL > 100)
    {
      // Go Left
      Serial.println("Go Left");
      motorCtrlAlloc(0, 1, turn_speed + 10, turn_speed + 10);
      delay(150);
      motorCtrlAlloc(0, 1, 0, 0);
      delay(150);
    }
    else
    {
      Serial.println("Go Straight");
      motorCtrlAlloc(1, 1, left_speed + 10, right_speed + 10);
      delay(150);
      motorCtrlAlloc(1, 1, 0, 0);
      delay(150);
    }
  }
  else
  {
    while (true)
      motorCtrlAlloc(1, 1, 0, 0);
  }
}
