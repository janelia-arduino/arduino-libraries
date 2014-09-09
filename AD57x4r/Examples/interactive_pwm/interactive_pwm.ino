#include "Arduino.h"
#include "Streaming.h"
#include "SPI.h"
#include "TimeTriggeredScheduler.h"
#include "AD57X4R.h"

#define DAC_CS 49


AD57X4R dac = AD57X4R(DAC_CS);

char input_buffer[128];
uint8_t idx = 0;
boolean input_complete = false;
char *argv[8];
int arg1, arg2, arg3;
unsigned int dac_value_max;
unsigned int millivolt_max = 10000;
int pwmPin = 48;


void parse(char *line, char **argv, uint8_t maxArgs)
{
  uint8_t argCount = 0;
  while (*line != '\0')
    {       /* if not the end of line ....... */
      while (*line == ',' || *line == ' ' || *line == '\t' || *line == '\n')
        {
          *line++ = '\0';     /* replace commas and white spaces with 0    */
        }
      *argv++ = line;          /* save the argument position     */
      argCount++;
      if (argCount == maxArgs-1)
        {
          break;
        }
      while (*line != '\0' && *line != ',' && *line != ' ' &&
             *line != '\t' && *line != '\n')
        {
          line++;             /* skip the argument until ...    */
        }
    }
  *argv = '\0';                 /* mark the end of argument list  */
}

void setup() {
  // PC communications
  Serial.begin(115200);
  Serial.println("* System ready *");

  // Initialize DAC
  dac.init(AD57X4R::AD5724R, AD57X4R::UNIPOLAR_10V, AD57X4R::ALL);
  dac_value_max = dac.getMaxDacValue();

  // Initialize time triggered scheduler
  tts.init();

  // Initialize PWM pin
  pinMode(pwmPin, OUTPUT);
  digitalWrite(pwmPin, LOW);
}


void loop() {
  if (input_complete)
    {
      parse((char*)input_buffer, argv, sizeof(argv));
      if (strcmp(argv[0], "analogWrite") == 0)
        {
          if (0 < strlen(argv[1]))
            {
              unsigned int millivolt_value = atoi(argv[1]);
              unsigned int dac_value = map(millivolt_value,0,millivolt_max,0,dac_value_max);
              dac.analogWrite(AD57X4R::ALL,dac_value);
            }
          else
            {
              Serial << "analogWrite <MILLIVOLT_VALUE>, VALUE = {0.." << millivolt_max << "}" << endl;
            }
        }
      else if (strcmp(argv[0], "pwm") == 0)
        {
          if ((0 < strlen(argv[1])) && (0 < strlen(argv[2])) && (0 < strlen(argv[3])))
            {
              unsigned int duration = atoi(argv[1]);
              unsigned int frequency = atoi(argv[2]);
              unsigned int duty_cycle = atoi(argv[3]);
              int dummy = 0;
              tts.removeAllTasks();
              Serial << "pwm: duration = " << duration << ", frequency = " << frequency << ", duty_cycle = " << duty_cycle << endl;
              if (duty_cycle == 0)
                {
                  inlinePwmPinLow(dummy);
                }
              else if (duty_cycle >= 100)
                {
                  inlinePwmPinHigh(dummy);
                }
              else
                {
                  long period = 1000/frequency;
                  long count = (duration*1000)/period;
                  uint32_t offset = (period*duty_cycle)/100;
                  int onTaskId = (int)tts.addTaskUsingDelay(100,inlinePwmPinHigh,dummy,period,count,false);
                  tts.addTaskUsingOffset((uint8_t)onTaskId,offset,inlinePwmPinLow,dummy,period,count,false);
                  Serial << "pwm: count = " << count << ", period = " << period << ", offset = " << offset << endl;
                }
            }
          else
            {
              Serial << "pwm <DURATION_SECS> <FREQUENCY_HZ> <DUTY_CYCLE_%>" << endl;
            }
        }
      else if (strcmp(argv[0], "readPowerControlRegister") == 0)
        {
          int powerControlRegister = dac.readPowerControlRegister();
          Serial << "powerControlRegister = " << _BIN(powerControlRegister) << endl;
        }
      else
        {
          Serial.println("analogWrite <MILLIVOLT_VALUE>, pwm <DURATION_SECS> <FREQUENCY_HZ> <DUTY_CYCLE_%>, readPowerControlRegister");
        }

      input_complete = false;
    }
}

void serialEvent()
{
  while (Serial.available())
    {
      uint8_t inByte;
      inByte = Serial.read();
      if ((inByte == '\n') || (inByte == '\r'))
        {
          Serial.println();
          input_buffer[idx] = 0;
          idx = 0;
          input_complete = true;
        }
      else if (((inByte == '\b') || (inByte == 0x7f)) && (idx > 0))
        {
          idx--;
          Serial.write(inByte);
          Serial.print(" ");
          Serial.write(inByte);
        }
      else if ((inByte >= ' ') && (idx < sizeof(input_buffer) - 1))
        {
          input_buffer[idx++] = inByte;
          Serial.write(inByte);
        }
    }
}

inline void inlinePwmPinHigh(int dummy) {digitalWrite(pwmPin,HIGH);};
inline void inlinePwmPinLow(int dummy) {digitalWrite(pwmPin,LOW);};
