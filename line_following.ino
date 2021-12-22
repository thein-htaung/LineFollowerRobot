void lineFollow()
{
  int twitch_delay = 30;
  if (R_sensor == BLACK && L_sensor == WHITE)
  {
    // Turn Right
    // After the paralle hallway, the car will slow down by having multiple steps
    if ((parallelHallDone == true) || (isDeadEnd == true))
    {
      Serial.println("Turn Right");
      // Must increase the speed to offset the static friction
      motorCtrlAlloc(1, 0, turn_speed + 20, turn_speed + 20);
      delay(twitch_delay);
      motorCtrlAlloc(1, 1, 0, 0);
      delay(twitch_delay);
    }
    else
    {
      motorCtrlAlloc(1, 0, turn_speed, turn_speed);
      delay(20);
    }
    prev_line_state = 1;
  }
  else if (L_sensor == BLACK && R_sensor == WHITE)
  {
    // Turn Left
    if ((parallelHallDone == true) || (isDeadEnd == true))
    {
      Serial.println("Turn Left");
      motorCtrlAlloc(0, 1, turn_speed + 15, turn_speed + 15);
      delay(twitch_delay);
      motorCtrlAlloc(1, 1, 0, 0);
      delay(twitch_delay);
    }
    else
    {
      motorCtrlAlloc(0, 1, turn_speed, turn_speed);
      delay(20);
    }
    prev_line_state = 2;
  }
  else if (L_sensor == WHITE && R_sensor == WHITE)
  {
    // Go straight if the sensors do not detect black
    if ((parallelHallDone == true) || (isDeadEnd == true))
    {
      Serial.println("Straight");
      motorCtrlAlloc(1, 1, left_speed + 20, right_speed + 20);
      delay(twitch_delay);
      motorCtrlAlloc(1, 1, 0, 0);
      delay(twitch_delay);
    }
    else
    {
      motorCtrlAlloc(1, 1, left_speed, right_speed);
      delay(20);
    }
    prev_line_state = 0;
  }
  // Take care of 90 angle & both sensors becoming black
  else if (L_sensor == BLACK && R_sensor == BLACK)
  {
    if (prev_line_state == 2)
    {
      // Turn Left
      while (true)
      {
        motorCtrlAlloc(1, 1, 0, turn_speed + 15);
        delay(twitch_delay);
        L_sensor = digitalRead(A1);
        if (L_sensor == WHITE)
        {
          break;
        }
        motorCtrlAlloc(1, 1, 0, 0);
        delay(twitch_delay);
      }
    }
    else if (prev_line_state == 1)
    {
      // Turn Right
      if (isDeadEnd)
      {
        while (true)
        {
          motorCtrlAlloc(1, 1, turn_speed + 15, 0);
          delay(twitch_delay);
          R_sensor = digitalRead(A0);
          M_sensor = digitalRead(A2);
          if (R_sensor == WHITE && M_sensor == BLACK)
          {
            isDeadEnd = false;
            isDeadEndOver = true;
            mm = 301;
            break;
          }
          motorCtrlAlloc(1, 1, 0, 0);
          delay(twitch_delay - 10);
        }
      }
      else
      {
        while (true)
        {
          motorCtrlAlloc(1, 1, turn_speed + 15, 0);
          delay(twitch_delay);
          R_sensor = digitalRead(A0);
          if (R_sensor == WHITE)
          {
            break;
          }
          motorCtrlAlloc(1, 1, 0, 0);
          delay(twitch_delay);
        }
      }
    }
    else
    {
      motorCtrlAlloc(0, 0, left_speed + 10, right_speed + 10);
      delay(twitch_delay);
      motorCtrlAlloc(0, 0, 0, 0);
      delay(twitch_delay + 20);
    }
  }
}
