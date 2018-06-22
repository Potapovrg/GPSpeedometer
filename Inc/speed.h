#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "GPS_parser.h"

void speedo(void);
void rallycomp(float odo1, uint32_t odo2, GPS_data *GPS);
extern u8g2_t u8g2;