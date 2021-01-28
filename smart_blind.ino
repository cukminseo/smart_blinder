/*
 * 겨울 계절학기 스마트 블라인드제어기 제작 프로젝트
 * 핀배치는 아래와 같습니다.
 * A1,A2,A3는 CDS
 * D18,D19,D20,D21은 STEPMOTOR
 * 제작전에 핀 레이아웃을 참고해주세요
 * https://content.arduino.cc/assets/Pinout-NANO33IoT_latest.png
 * 
 */
// 스텝모터 설정----------------------------------------
int IN1 = 18;               // IN1핀을 8번에 배선합니다.
int IN2 = 19;               // IN2핀을 9번에 배선합니다.
int IN3 = 20;               // IN3핀을 10번에 배선합니다.
int IN4 = 21;               // IN4핀을 11번에 배선합니다.
int motorSpeed = 1800;      // 스텝모터의 속도를 정할 수 있습니다.
int count = 0;              // 스텝을 카운트하여 얼마나 회전했는지 확인할 수 있습니다.
int countsperrev = 512;     // 최대 카운트를 512로 설정합니다.
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};// 스텝모터를 제어할 방향의 코드를 미리 설정합니다.
//int motor_locate=0;         //모터의 현재 위치입니다.
// 조도센서 설정-----------------------------------------
int CDS_A1=A0;    
int CDS_A2=A1;
int CDS_A3=A2;
int CDS_A4=A3;

//개발자모드 진입-----------------------------------------
#define isDeveloperMode (0)
//1로 설정된 경우 개발자 모드로 들어가 컴퓨터와 시리얼 통신을 하며, 아두이노 기초값을 세팅합니다.
//0으로 설정된 경우 기본모드로 블라인드가 작동하게 됩니다.

//기본설정-----------------------------------------------
void setup(){
  pinMode(IN1, OUTPUT);    // IN1을 스텝모터 출력핀으로 설정합니다.
  pinMode(IN2, OUTPUT);    // IN2을 스텝모터 출력핀으로 설정합니다.
  pinMode(IN3, OUTPUT);    // IN3을 스텝모터 출력핀으로 설정합니다.
  pinMode(IN4, OUTPUT);    // IN4을 스텝모터 출력핀으로 설정합니다.
  if (isDeveloperMode)     //개발자 모드로 진입합니다.
    Serial.begin(9600);    // CDS 초기값 세팅을 위해 컴퓨터와 통신합니다.
}

//반복작동 설정-------------------------------------------
void loop(){
  int CA1=analogRead(CDS_A1);
  int CA2=analogRead(CDS_A2);
  int CA3=analogRead(CDS_A3);
  int CA4=analogRead(CDS_A4);
  if (!isDeveloperMode){
    blind_start(CA1,CA2,CA3,CA4);
  }
  else              //개발자 모드를 실행합니다.
    blind_developermode(CA1,CA2,CA3,CA4);
  
}
//추가함수들---------------------------------------------
void blind_start(int CA1,int CA2,int CA3, int CA4){
  if (CA1>CA4+50){
    clockwise();
  }
  else if (CA4>CA1+50){
    anticlockwise();
  }
  else{
    
  }
}
void blind_developermode(int CA1,int CA2,int CA3, int CA4){
  CDS_setting(CA1,CA2,CA3,CA4);          //CDS세팅 함수
}

void CDS_setting(int CA1,int CA2,int CA3, int CA4){       //CDS측정값을 시리얼모니터로 출력합니다.
  Serial.print("CA1로 입력된 값:");
  Serial.print(CA1);
  Serial.print(" CA2로 입력된 값:");
  Serial.print(CA2);
  Serial.print(" CA3로 입력된 값:");
  Serial.print(CA3);
  Serial.print(" CA4로 입력된 값:");
  Serial.println(CA4);
  delay(700);
}

void clockwise()
{
  for (int i = 7; i >= 0; i--)                          // 8번 반복합니다.
  {
    motorSet(i);                                        // setOutput() 함수에 i 값을 넣습니다 (7~0)
    delayMicroseconds(motorSpeed);                      // 모터 스피트만큼 지연합니다.
  }
}
void anticlockwise()
{
  for (int i = 0; i < 8; i++)                           // 8번 반복합니다.
  {
    motorSet(i);                                        //  setOutput() 함수에 i 값을 넣습니다 (0~7)
    delayMicroseconds(motorSpeed);                      // 모터 스피드만큼 지연합니다.
  }
}
void motorSet(int out)
{
  digitalWrite(IN1, bitRead(lookup[out], 0));             // IN1에 함수로부터 입력받은 out값을 넣어 모터를 제어합니다.
  digitalWrite(IN2, bitRead(lookup[out], 1));             // IN2에 함수로부터 입력받은 out값을 넣어 모터를 제어합니다.
  digitalWrite(IN3, bitRead(lookup[out], 2));             // IN3에 함수로부터 입력받은 out값을 넣어 모터를 제어합니다.
  digitalWrite(IN4, bitRead(lookup[out], 3));             // IN4에 함수로부터 입력받은 out값을 넣어 모터를 제어합니다.
}
