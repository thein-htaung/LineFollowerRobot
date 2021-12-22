// Motor Directions
void leftForwards(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void leftBackwards(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void rightForwards(void)
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void leftStop(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void rightStop(void)
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void rightBackwards(void)
{
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// This function sets the direction of the motors as well as the speed.
int motorCtrlAlloc(int dirL, int dirR, int pwmL, int pwmR)
{
  // This checks for invalid inputs for both the direction and PWM values
  if (((dirL != 1 || dirL != 0) && (dirR != 1 || dirR != 0)) && ((pwmL < 0 || pwmL > 255) && (pwmR < 0 || pwmR > 255)))
  {
    Serial.println("Bad Input");
    return -1;
  }
  else
  {
    // Set the motors direction
    if (dirL == 1)
    {
      leftForwards();
    }
    else
    {
      leftBackwards();
    }
    if (dirR == 1)
    {
      rightForwards();
    }
    else
    {
      rightBackwards();
    }

    // Set the motors speed
    analogWrite(ENA, pwmL);
    analogWrite(ENB, pwmR);
    return 0;
  }
}
