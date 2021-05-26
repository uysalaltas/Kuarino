#include "motor_control.h"
#include "gcode.h"
#include "end_stop.h"
#include "pins.h"
#include "TimerOne.h"
#include <Arduino_FreeRTOS.h>

String serial_data;
FILE *fileI;
gcode gcode_read;
pins pin_init;

#define MSG_MAX_LEN 22

volatile uint8_t m_newMessage;
volatile uint8_t m_packetBuffer[MSG_MAX_LEN];
volatile uint8_t m_packetBufferInd;

volatile uint32_t m_msgTimeoutCnt_ms;

void timer_tick()
{
  // Packet timeout handler
  if(m_msgTimeoutCnt_ms > 0)
  {
    m_msgTimeoutCnt_ms -= 1;
    if(m_msgTimeoutCnt_ms == 0)
    {
      Serial.println("TimeOut");
      comHandler_init();
    }
  }
}

void timer_init()
{
  Timer1.initialize(1 * 1000);
  Timer1.attachInterrupt(timer_tick);
}

void comHandler_init()
{
  uint8_t i = 0;
  for(i=0;i<MSG_MAX_LEN;i++)
  {
    m_packetBuffer[i] = 0;
  }
  comHandler_reset();
}

void comHandler_reset()
{
  m_packetBufferInd = 0;
  m_newMessage = true;
}

void setup() {
  Serial.begin(115200);
  timer_init();
  comHandler_init();
  
  fileI = fopen("1.gcode", "r");
}

void serialEvent()
{
  while(Serial.available())
  {
    volatile char ch = Serial.read();

    if (m_newMessage == true)
    {
      m_packetBuffer[m_packetBufferInd] = ch;
      m_packetBufferInd = m_packetBufferInd + 1;

      if (m_packetBuffer[0] > MSG_MAX_LEN)
      {
        Serial.println("Package is higher than expected!");
        m_packetBufferInd = 0;
        m_newMessage = false;
      }
      else if (ch == 10 && m_packetBufferInd != 1)
      {
        gcode_read.g_control(m_packetBuffer);
      }
      m_msgTimeoutCnt_ms = 200;
    }
  }
}

void loop() {

}
