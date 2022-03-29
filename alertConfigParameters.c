#include <stdio.h>
#include "alertConfigParameters.h"
#include "typewise-alert.h"

BatteryCharacter BatteryTemperatureValues[ACCEPTABLE_COOLING_STATES] =
{
  {
  .lowerLimitOfTemp = 0,
  .upperLimitOfTemp = 35,
  },
  {
  .lowerLimitOfTemp = 0,
  .upperLimitOfTemp = 45,
  },
  {
  .lowerLimitOfTemp = 0,
  .upperLimitOfTemp = 40,
  }
};

AlertTargetFunction AlertTargetFuncConfiguration[ACCEPTABLE_ALERT_VALUE] =
{
  {
    .alertFunction = &sendToEmail
  },
  {
    .alertFunction = &sendToController
  }
};

char AlertMessageForMail[ACCEPTABLE_COOLING_STATES][100] =
{"Hi, the temperature is normal\n",
 "Hi, the temperature is too low\n",
 "Hi, the temperature is too high\n"};
