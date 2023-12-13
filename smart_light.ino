//창의공학설계_시각장애인용 스마트 지팡이
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip=Adafruit_NeoPixel(28, 7, NEO_GRB+NEO_KHZ800);

void setup() {
  //조도센서, 네오픽셀 스트립 설정
  Serial.begin(9600);
  strip.setBrightness(100);
  strip.begin();
  strip.show();
  //부저, 초음파, 수위감지 센서와 연결
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  //조도센서, 네오픽셀 스트립
  int light = analogRead(A2);

  //조도센서의 밝기에 따라 네오픽셀의 색상 조절(노랑 ~ 빨강)
  Serial.print("밝기: ");
  Serial.println(light);
  if(light > 600){
    for(int i = 0; i < 28; i++){
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
  }
  else if(light < 500 && light > 300)
  {
    for(int i = 0; i < 28; i++){
      strip.setPixelColor(i, 255, 255, 0);
    }
    strip.show();
  }
  else if(light < 300 && light > 100)
  {
    for(int i = 0; i < 28; i++){
      strip.setPixelColor(i, 255, 100, 0);
    }
    strip.show();
  }
  else if(light < 100 && light > 0)
  {
    for(int i = 0; i < 28; i++){
      strip.setPixelColor(i, 255, 0, 0);
    }
    strip.show();
  }
  delay(100);

  //초음파, 부저
  digitalWrite(6,1);
  delay(100);
  digitalWrite(6,0);
  
  int duration = pulseIn(5, 1); //초음파 가져오기
  int distance = duration/58.2; //미터 -> 센치(cm)로 단위변환
  
  //거리에 따라 자동차 후방경고음과 같은 기능을 구현
  if(distance > 60) {
    noTone(4);
    delay(100);
  }
  else if(distance < 60 && distance > 40) {
      tone(4, 400);
      delay(200);
      noTone(4);
      delay(200);
  }
   else if(distance < 40 && distance > 25) {
      tone(4, 400);
      delay(100);
      noTone(4);
      delay(100);
  }
  else if(distance < 25 && distance > 10) {
      tone(4, 400);
      delay(30);
      noTone(4);
      delay(30);
  }
  else if(distance < 10 && distance > 0) {
      tone(4, 500);
  }

  //초음파센서와 물체와의 거리를 출력(0.1초 갱신)
  Serial.print("현재 거리(cm): ");
  Serial.println(distance);

    //시리얼모니터에 수위감지 센서 값 출력
  Serial.print("수위 위험수치: ");
  int x = analogRead (A0);
  Serial.println (x);

   //출력값(수위 위험수치)이 750 이상으로 올라가면 경고음 출력
  if(x > 750){
    tone(4, 700);
  }
  else{
    digitalWrite(4, LOW);
  }
  delay(100);
}