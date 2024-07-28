/*
 * Test encoder by spinning wheel manually, 
 * and seeing if coder value changes as expect.
 */

volatile long pulseCount = 0; 
volatile long totPulses = 0; 
volatile long totRevs = 0;

unsigned long currentTime;

const byte m = 3; // pin connected to encoder signal

int lastEncoderVel = 0,
  ppr = 20,
  samplePeriod = 100;
  
static unsigned long lastTime = 0; // print manager timer

long timeDiff;

void setup() 
{
  Serial.begin(9600);
  
  while(!Serial);

  /* Initialize */

  attachInterrupt(digitalPinToInterrupt(m), wheelSpeed, CHANGE);
}

void loop() 
{
  currentTime = millis();
  
  timeDiff = currentTime - lastTime;
  
  if(timeDiff > samplePeriod)
  {
    displayStatus();

    lastEncoderVel = pulseCount * ( 1000 / samplePeriod ); // record latest speed value

    Serial.print("Last Encoder Velocity (pulses/s): ");
    Serial.println(lastEncoderVel);
    Serial.println();
    
    pulseCount = 0; // clear data buffer

    lastTime = millis();
  }
}

void displayStatus()
{
  Serial.print("Total Elapsed Time (ms): ");
  Serial.println(currentTime);

  Serial.print("Last Recorded Time (ms): ");
  Serial.println(lastTime);
  
  Serial.print("Time Diff (ms): ");
  Serial.println(timeDiff);
  
  Serial.print("Pulse Count: ");
  Serial.println(pulseCount);
  
  Serial.print("Total Pulses: ");
  Serial.print(totPulses);
  Serial.println();
  
  Serial.print("Total Wheel Revs: ");
  Serial.print(totRevs);
  Serial.println();

  Serial.println();
}


//======Interrupt Service Routines======
void wheelSpeed()
{
  pulseCount++; // count wheel encoder interrupts

  totPulses++;

  totRevs = floor(totPulses / ppr);
}

long encoderRotVel()
{
  return pulseCount * 10;
}

