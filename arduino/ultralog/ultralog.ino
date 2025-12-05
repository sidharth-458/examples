/**
  @brief Ultrasonic detects entry and exit; logs it to flash; On touch print logs
  */
#include <Arduino.h>
#include <SPI.h>
#include <SPIFlash.h>
#include<string>
// Ultrasound Defaults
const int TRIG_PIN = 27;                   // Ultrasonic TRIG
const int ECHO_PIN = 34;                   // Ultrasonic ECHO (input-only OK)
const unsigned long POLL_MS = 200;         // ultrasonic poll interval (ms)
const float PRESENCE_THRESHOLD_CM = 30.0;  // distance threshold to detect object

// Flash defaults
const int FLASH_CS = 5;                                   // SPI CS for W25Q flash
const uint32_t FLASH_START_ADDR = 0x000000;               // start writing at beginning of flash
const uint32_t FLASH_SIZE_BYTES = 8UL * 1024UL * 1024UL;  // adjust if not 8 MiB
const uint32_t SECTOR_SIZE = 4096UL;                      // 4KB sector

// Touch defaults
const int TOUCH_PIN = T0;  // Touch pin (T0 maps to GPIO4 on many boards)
const touch_value_t TOUCH_THRESH = 400;
// SPIClass spi =  SPIClass(HSPI);
// Adafruit_FlashTransport_SPI flashTransport(FLASH_CS,SPI);
SPIFlash flash(FLASH_CS);
QueueHandle_t msgq;

bool newlock;
bool oldlock;
void initSonic() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}
  // }
  enum e_activity{ENTRY, EXIT, PRINT};
  struct st_work{
    enum e_activity activity;
    unsigned long mills;
  };

  void touchTopHalf(){
    struct st_work work;
    touchDetachInterrupt(TOUCH_PIN);
    newlock = true;
    work.activity = PRINT;
    work.mills = millis();
    xQueueSendFromISR(msgq,(void*)&work,NULL);
     Serial.println("touch");
  }
uint32_t appendLog(struct st_work *work, uint32_t last){
    last = last +1;
    String a;
    if(work->activity == ENTRY)
      a = "entry ";
    else
      a = "exit ";
    a = a + String(work->mills);
    a = a + "\n";
    flash.writeBytes(last, (const uint8_t *)a.c_str(), a.length());
    last +=a.length();
    return last;
  }
  void printLogs(uint32_t last){
    uint8_t buff[100];
    buff[99] = 0;
    int times = last/99;
    int remain = last%99;
    uint32_t id = 0;
    while(times--){
      flash.readBytes(id, buff, 99);
      id+=99;
      Serial.printf("%s",buff);
    }
    flash.readBytes(id,buff,remain);
    buff[remain] = 0;
    Serial.printf("%s\n",buff);
  }
  void touchBotHalf(uint32_t last){
    printLogs(last);
    touchAttachInterrupt(TOUCH_PIN, touchTopHalf, TOUCH_THRESH);
  }


  void loopFlash(void *pv){
    uint32_t curridx = 0;
    struct st_work work;
    for(;;){
      if(xQueueReceive(msgq,(void*)&work,portMAX_DELAY)){
        switch(work.activity){
          case ENTRY:
          case EXIT:
            curridx = appendLog(&work,curridx);
          break;
          case PRINT:
            touchBotHalf(curridx);
          break;
        }
      }
    }
  }
  void loopSonic(void *pv) {
    float duration, distance;
    bool olddet = false;
    bool currdet = false;
    struct st_work work = {};
    
    while (1) {
      distance = 0;
      for(int i =0; i<10;i++){
        delayMicroseconds(2);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        duration = pulseIn(ECHO_PIN, HIGH);
        distance += (duration*.0343)/2;
        // Serial.print("Distance: ");
        // Serial.println(distance);
        if(distance > 1200.0)
          break;
        delay(100);

      }
      distance = distance/10;
      if(distance < 60.0){
        // Serial.print(distance);
        // Serial.println("detected");
        currdet = true;
      }
      else
        currdet = false;
      if(currdet != olddet){
        if(currdet){
          Serial.println("detected");
          work.activity = ENTRY;
        }
        else{
          Serial.println("gone");
          work.activity = EXIT;
        }
        work.mills = millis();
        xQueueSend(msgq,(void*)&work,portMAX_DELAY);
        olddet  = currdet;
      }
    }
  }
  void flashTest(){
    flash.writeByte(0, 12);

    if(flash.readByte(0) == 12)
      Serial.println("flash works");
    else
      Serial.println("flash issue");
  }
  void setup() {
    // put your setup code here, to run once:
    SPI.begin();
    flash.initialize();
    flashtest();
    initSonic();
    
    msgq = xQueueCreate(sizeof(struct st_work ),10);
    
    xTaskCreate(loopSonic,"loopSonic",2000,NULL,1,NULL);
    xTaskCreate(loopFlash,"loopFlash",2000,NULL,1,NULL);
    
    touchAttachInterrupt(TOUCH_PIN, touchTopHalf, TOUCH_THRESH);
  }

  void loop() {
    // put your main code here, to run repeatedly:
    delay(1000);
    //Serial.println(touchRead(T0));
  }
