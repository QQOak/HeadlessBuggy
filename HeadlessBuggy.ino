#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#include "Wheel.h"

MPU6050 mpu;

Wheel leftWheel(4, 5, 3);
Wheel rightWheel(8, 7, 6);




//String incomingByte;

// Yaw tolerance.
// when starting, the yaw value will 'drift' until some sort of internal calibration is complete.
// when the calibration is complete, get the value and use this as an offset for point 0.
// the yawOffset can also be used during runtime to 'trim' the axis to deal with yaw drift.

//bool yawCalibrating = true;
//double yawCalibrationAngleTolerance = 0.2;
//double yawOffset = 0.0;







#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector



volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}






// Drive related functions
// ==========================================================




void calculateWheelSpeeds()
{

}




// Range is from -255 for full reverse to 255 for full forwards. 
void SetWheelSpeed(Wheel wheel, int Speed) {
  digitalWrite(wheel.ForwardsPin, Speed > 0);
  digitalWrite(wheel.ReversePin, Speed < 0);
  analogWrite(wheel.SpeedPin, abs(Speed));  
}



int leftWheelSpeed = 0;
int rightWheelSpeed = 0;
int *ptrLeftWheelSpeed = NULL;
int *ptrRightWheelSpeed = NULL;

void CalculateRotationSpeed(int CurrentAngle, int TargetAngle, int *leftWheelSpeed, int *rightWheelSpeed)
{



}


// Returns a float with 2 decimal point precision indicating the amount of travel required clockwise (+) rotation or
// anti-clockwise (-) rotation, whichever is the shortest rotation.
// Accepts the current orientation as the current angle, and the orientation that is needed.
float CalculateRotationRequired(float CurrentAngle, float TargetAngle)
{

  // Degrees difference between the current and target angles.
  // Multiply by 10 and convert to integer so we maintain TWO decimal point precision.
  int neededRotation = (int)((TargetAngle - CurrentAngle)*100);

  // Add half a clockwise rotation to be removed after the modulus operation
  neededRotation += 18000;

  // Make sure the rotation angle does not angle exceed 359.99 degrees
  neededRotation = neededRotation % 36000;

  // Add a half anti-clockwise rotation to put output in range of -180 to +180 degrees.
  neededRotation -= 18000;

  // Divide by 10 again and return as a float to give us a single decimal point precision.
  return ((float)(neededRotation))/100;
   
}




void SetWheelSpeeds(int RotationSpeed, int Velocity)
{


  SetWheelSpeed(leftWheel, leftWheelSpeed);
  SetWheelSpeed(rightWheel, rightWheelSpeed);
}
















void setup() {

    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    //mpu.setXGyroOffset(220);
    //mpu.setYGyroOffset(76);
    //mpu.setZGyroOffset(-85);
    //mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    mpu.setXGyroOffset(-1);
    mpu.setYGyroOffset(0);
    mpu.setZGyroOffset(0);
    mpu.setZAccelOffset(0); // 1688 factory default for my test chip


    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
      
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
        
    } else {
      
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);


  
    
    Serial.println("Initialising Wheels...");
    SetWheelSpeeds(0, 0);
  
    Serial.println("Ready.");


    
}





// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        //
        // other program behavior stuff here
        //              







        
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;


        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        float Target = 0;
        Serial.print("Rotation Required to reach ");
        Serial.print(Target);
        Serial.print(" : ");
        Serial.println(CalculateRotationRequired((ypr[0] * 180/M_PI), 0));
        
        //Serial.print("ypr\t");
        //Serial.println(ypr[0] * 180/M_PI);
        //Serial.print("\t");
        //Serial.print(ypr[1] * 180/M_PI);
        //Serial.print("\t");
        //Serial.println(ypr[2] * 180/M_PI);

       //Serial.print("Current Yaw:");
       //Serial.println(ypr[0] * 180/M_PI);

        //SetWheelSpeed(leftWheel, leftWheelSpeed);
        //SetWheelSpeed(rightWheel, rightWheelSpeed);

        // blink LED to indicate activity
        //blinkState = !blinkState;
        //digitalWrite(LED_PIN, blinkState);
    }
}
