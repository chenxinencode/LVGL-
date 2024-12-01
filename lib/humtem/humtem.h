#ifndef _humtem_H
#define _humtem_H

#include<Arduino.h>
#include <Wire.h>
#include <AHT20.h>
const int SCLPin = 18;
const int SDAPin = 19;


void humtem_setup();
void humtem_loop();

#endif
