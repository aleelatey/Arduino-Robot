// IR program for Arduino robot

#include <IRremote.h>

/*
   Left Motor
*/
// IN 1
#define LM_IN1    2
// IN 2
#define LM_IN2    4
/*
   Right Motor
*/
// IN 3
#define RM_IN3    5
// IN 4
#define RM_IN4    7


// IR receiver
# define RECV_PIN 10

IRrecv irrecv(RECV_PIN);

decode_results results;

//HEX codes for buttons
#define FWD       0xFD8877 // go forward
#define LFT       0xFD28D7 // go left
#define RGT       0xFD6897 // go right
#define BWD       0xFD9867 // go backward
#define STOP      0xFD30CF // stop
#define RESET     0xFD00FF // Resets the Arduino Board(RED)

unsigned long int value=0;

/*
 ************Arduino Reset Pin**************
 */
#define RESET_PIN A0

void setup() {
  
  // set mode of the pins as output
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }


  // start serial communication
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

}

void loop() {
  if (irrecv.decode(&results)) {
    value = results.value;
    Serial.println(value, HEX);
    irrecv.resume(); // Receive the next value
    delay(200);
  }

  delay(100);
  check_Inst(value);
  value=0;
}

void check_Inst(long int value) {

  switch (value) {
    case FWD:
      go_Forward();
      break;
    case LFT:
      go_Left();
      break;
    case RGT:
      go_Right();
      break;
    case BWD:
      go_Backward();
      break;
    case STOP:
      go_Stop();
      break;
    case RESET:
      pinMode(RESET_PIN,OUTPUT);
      digitalWrite(RESET_PIN,HIGH);   
      break;  

    default:
      value = 0;
  }
}

void go_Forward() {
 
  movement_Inst_Fwd();
  delay(10);
}

void go_Left() {
   
  movement_Inst_Lft();
  delay(10);
}

void go_Right() {
  
  movement_Inst_Rgt();
  delay(10);
}

void go_Backward(){

  movement_Inst_Bwd();
  delay(10);
}  

void go_Stop(){
  
  movement_Inst_Stp();
  delay(10);
}  

/*
 * These movement instruction are repeated several times in the code
 */
void movement_Inst_Fwd(void){
  Serial.println("Going_Forward");
  
  // forward movement instructions
  digitalWrite(LM_IN1,HIGH);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,HIGH);
  digitalWrite(RM_IN4,LOW);   
  } 
  
void movement_Inst_Lft(void){
  Serial.println("Going_Left");
  
  // Left movement instructions
  digitalWrite(LM_IN1,LOW);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,HIGH);
  digitalWrite(RM_IN4,LOW);  
  delay(500);
  digitalWrite(LM_IN1,LOW);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,LOW);
  digitalWrite(RM_IN4,LOW);    
  delay(500);
  }
  
void movement_Inst_Rgt(void){
  Serial.println("Going_Right");  
  
  // Rgt movement instructions
  digitalWrite(LM_IN1,HIGH);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,LOW);
  digitalWrite(RM_IN4,LOW); 
  delay(500);
  digitalWrite(LM_IN1,LOW);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,LOW);
  digitalWrite(RM_IN4,LOW); 
  delay(500);
    
  }
  
void movement_Inst_Bwd(void){
  Serial.println("Going_Backward"); 
    
  // Bwd movement instructions
  digitalWrite(LM_IN1,LOW);
  digitalWrite(LM_IN2,HIGH);
  digitalWrite(RM_IN3,LOW);
  digitalWrite(RM_IN4,HIGH);   
  }
  
void movement_Inst_Stp(void){  
  Serial.println("Stopping");    
  
  // Stp movement instructions
  digitalWrite(LM_IN1,LOW);
  digitalWrite(LM_IN2,LOW);
  digitalWrite(RM_IN3,LOW);
  digitalWrite(RM_IN4,LOW);  
  }