#include <Servo.h>
// 创建对象
Servo servo_8;
Servo servo_9;
Servo servo_10;

void setup() {

  Serial.begin(9600);
  pinMode(A0, INPUT);

  servo_8.attach(8);
  servo_9.attach(9);
  servo_10.attach(10);
}

void loop() {
  int sensorValue;
  long sum = 0;
  for (int i = 0; i < 256; i++) {
    sensorValue = analogRead(A0);
    sum += sensorValue;
    delay(2);
  }
  sum = sum >> 10;
  Serial.print(sum);
  Serial.print(", ");

  // Serial.print("The voltage value:");
  Serial.print(sum * 4980.0 / 1023.0);
  Serial.println("mV");
  delay(20);

  if(sum > 0) {
    testPump();
  }
}


void testPump() {
    for (int index = 0; index < 1; index++) {   //注释：工作循环次数0-？次循环，此代表循环3次。3可以根据自己需求修改
    servo_8.write(180);
    servo_9.write(0);
    servo_10.write(0);


    delay(8000);
//-----------------------------------------此组代码表示充气泵工作8秒（180代表开，0代表关。 delay(8000);代表运行时间为8000毫秒。需要充气时间可以按需求自定义修改。

    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(180);

    delay(500);
    //------------------------------------此组代码表示电磁阀启动，主要是电磁优先启动0.5秒为下一步抽气准备。此组时间基本不需要修改。

    servo_8.write(0);
    servo_9.write(180);
    servo_10.write(180);
 
    delay(8000);


  //---------------------------------------此组代码表示抽气泵电池阀工作8秒，也就是抽气8秒（时间可以根据自己需求修改）。


    servo_8.write(0);
    servo_9.write(0);
    servo_10.write(0);


    //------------------------------------全部结束。
  
  }
}