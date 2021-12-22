void goForwardEnc(void)
{
  leftForwards();//set motor directions to forwards
  rightForwards();
  analogWrite(5, left_speed);

  if (start)
  {
    analogWrite(6, right_speed + 2);
    start = false;
  }

  // Get step counts
  l_count = enc_getLeft();
  r_count = enc_getRight();
  correctionFactor = abs(l_count - r_count);

  // Set left wheel as master
  if (l_count > r_count)
  {
    //Serial.println("Faster");
    analogWrite(6, right_speed + 4 + correctionFactor * multiple);
    prevState = 1;
  }
  else if (l_count < r_count)
  {
    prevState = 2;
    //Serial.println("Slower");
    analogWrite(6, right_speed - 4 - correctionFactor * multiple - 35);
  }
  else
  {
    // If the wheels start to get in sync, keep doing whatever the previous action did
    //Serial.println("The wheels are equal");
    if (prevState == 1)
    {
      analogWrite(6, right_speed + 4 + correctionFactor * multiple);
    }
    else
    {
      analogWrite(6, right_speed - 4 - correctionFactor * multiple - 35);
    }
  }
  // Debugging
    Serial.print(l_count);
    Serial.print(" ");
    Serial.println(r_count);
  
}
