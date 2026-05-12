#include <stdio.h>
#include <stdbool.h>
#include "output.h"
#include "lcd.h"
#include "toString.h"

char currentAngleStr[12];
char speedStr[12];

char currentAngleStrOld[12];
char speedStrOld[12];

int zaehler = 0;
bool topLine = true;

void outputUpdate()
{
    if(topLine)
    {
        if(currentAngleStr[zaehler] != currentAngleStrOld[zaehler])
        {
            currentAngleStrOld[zaehler] = currentAngleStr[zaehler];

            lcdGotoXY(20 + zaehler, 2);
            lcdPrintC(currentAngleStr[zaehler]);
        }

        topLine = false;
    }
    else
    {
        if(speedStr[zaehler] != speedStrOld[zaehler])
        {
            speedStrOld[zaehler] = speedStr[zaehler];

            lcdGotoXY(20 + zaehler, 4);
            lcdPrintC(speedStr[zaehler]);
        }

        topLine = true;

        zaehler++;
        if(zaehler >= sizeof(currentAngleStr) - 1)
        {
            zaehler = 0;
        }
    }
}

#define USE_DOUBLE_TO_STRING false

void outputChange(double currentAngle, double angleSpeed)
{
#if USE_DOUBLE_TO_STRING
    doubleToString(currentAngle, currentAngleStr);
    doubleToString(angleSpeed, speedStr);
#else
    snprintf(currentAngleStr, sizeof(currentAngleStr),
        "%11.1f", currentAngle);

    snprintf(speedStr, sizeof(speedStr),
        "%11.1f", angleSpeed);
#endif
}
