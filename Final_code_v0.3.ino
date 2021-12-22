// Libraries
#include <ENGG1500Lib.h>
#include <Servo.h>

// Preprocessor Directives
// Ultrasonic constants
#define ECHO 12
#define TRIG 7

// IR constants
#define BLACK 1
#define WHITE 0

// Motor constants
#define ENA 5
#define ENB 6
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Necessasities
#define parking_dist 45
#define parallel_dist 700

Servo myservo;

// Line following
int M_sensor = 0;
int R_sensor = 0;
int L_sensor = 0;
int straight_speed = 100;
int prev_line_state = 0;

// Set speed
int pot = 0;
float init_speed = 0;
float left_speed = 0;
float right_speed = 0;
int turn_speed = 85;


// Timer
unsigned int prevMillis = 0;
unsigned int currMillis = 0;


// Ultrasonic sensing
int pos = 75;
unsigned int mm = 0;
bool isDeadEnd = false;
bool isDeadEndOver = false;

// Encoder algorithm
int prevState = 0;
int correctionFactor = 0;
int multiple = 5.2;
float l_count = 0;
float r_count = 0;
bool start = true;

// Parallel Hallway and the sensor values for the left check and the right
unsigned int ValueL = 100;
unsigned int ValueR = 100;
unsigned int ValueM = 0;
bool first_time = true;
bool parallel_check = true;
bool is_parking = true;
bool parallelHallDone = false;

// Parking
bool is_parallel;
int goForSomeDistance;
int firstRun = 1;
int left_distance = 0;
int front_distance = 0;

void setup() {
  setup_init();
}

void loop() {
  setSpeedByPot();
  getIRsensors();

  if (M_sensor == WHITE)
  {
    if (R_sensor == WHITE && L_sensor == WHITE)
    {
      if (parallel_check)
      {
        // Check for parallel/parking
        parkingParallelChk();
      }
      if (is_parallel)
      {
        parallelHall();
      }
      else if (is_parking)
      {
        if (firstRun)
        {
          goForSomeDistance = 1;
          firstRun = 0;
        }
        parking();
      }
    }
  }
  else
  {
    //printData();
    // Reset the parallel_check so that it will check again for the next parking/parallel hallway
    if (parallel_check == false)
    {
      parallel_check = true;
      myservo.write(75);
    }

    // Reset the isParallel status so that it will be able to detect parking
    if (is_parallel)
    {
      is_parallel = false;
    }

    if (!isDeadEndOver)
    {
      if (!isDeadEnd)
      {
        mm = sonar_mm();
      }
      Serial.println(mm); // Puttig this in fixed the uncontrollable turning of the car
      Serial.println(left_speed);
      if (mm < 300)
      {
        isDeadEnd = true;
        lineFollow();
        Serial.println("Dead End");
      }
      else
      {
        Serial.println("Normal Line Follow");
        lineFollow();
      }
    }
    else
    {
      Serial.println("Line follow without ultrasonic");
      lineFollow();
    }
  }
}

// Setup Function for pins and initialization
void setup_init()
{
  pinMode(5, OUTPUT); //set ENA as an output (left Wheel)
  pinMode(6, OUTPUT); //set ENB as an output (right Wheel)
  pinMode(8, OUTPUT); //set IN1 as an output
  pinMode(9, OUTPUT); //set IN2 as an output
  pinMode(10, OUTPUT); //set IN3 as an output
  pinMode(11, OUTPUT); //set IN4 as an output

  pinMode(A5, INPUT); // A5 is used for pot
  pinMode(A0, INPUT); //Initialising pin A0 for IR right
  pinMode(A1, INPUT); //Initialising pin A1 for IR left
  pinMode(A2, INPUT); //Initialising pin A2 for IR middle

  pinMode(ECHO, INPUT); //Initialise pin 12 as an input
  pinMode(TRIG, OUTPUT); //Initialise pin 7 as an output
  myservo.attach(13);  // attaches the servo on pin 13 to the servo object
  myservo.write(75);
  Serial.begin(9600);
  delay(1000);
  enc_init();
  enc_clear();
}

void setSpeedByPot(void)
{
  pot = analogRead(A5);
  init_speed = map(pot, 0, 1023, 0, 255);
  right_speed = init_speed;
  left_speed = init_speed;
}

void printData()
{
  Serial.print("Right Sensor : ");
  Serial.print(R_sensor);
  Serial.print(" Left Sensor : ");
  Serial.print(L_sensor);
  Serial.print(" Middle Sensor : ");
  Serial.println(M_sensor);
  Serial.print("Pot speed : ");
  Serial.println(init_speed);
  Serial.print("Ultrasonic distance : ");
  Serial.println(mm);
}
