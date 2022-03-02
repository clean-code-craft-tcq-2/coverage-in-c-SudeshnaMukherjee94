#include "alertConfigParameters.h"
#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool validateEnumValue(int enumValue, int maxPossibleValue)
{
  if((enumValue >= 0) && (enumValue < maxPossibleValue))
  { 
      return true;
  } 
  return false;
}

void printWarningMessageForEmail(const char* recipient, char alertStatus[]){
    printf("To: %s\n%s", recipient, alertStatus);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printWarningMessageForEmail(recepient, AlertMessageForMail[breachType]);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}
                    
//Function to infer the nature of breach occured
BreachType inferBreach(BatteryCharacter batteryCharacteristics, float tempValue) 
{
  if(tempValue < batteryCharacteristics.lowerLimitOfTemp)
  {return TOO_LOW;
  }
  else if(tempValue > batteryCharacteristics.upperLimitOfTemp)
  { return TOO_HIGH;
  }
  return NORMAL;
}

BatteryCharacter populateOperatingTemperatureValues(CoolingType coolingType)
{
  BatteryCharacter batteryCharacteristics; 
  batteryCharacteristics.coolingType = coolingType;
  batteryCharacteristics.lowerLimitOfTemp = BatteryTemperatureValues[coolingType].lowerLimitOfTemp;
  batteryCharacteristics.upperLimitOfTemp = BatteryTemperatureValues[coolingType].upperLimitOfTemp;
  return batteryCharacteristics;
}

bool alertBreach(AlertOptions alertOption, BreachType breachType){
  if(validateEnumValue(alertOption, ACCEPTABLE_ALERT_VALUE)){
      AlertTargetFuncConfiguration[alertOption].alertFunction(breachType);
      return true;
  }
    return false;
}
                    
bool checkAndAlert(AlertOptions alertOption, CoolingType coolingType, float tempValue) {
  if(validateEnumValue(coolingType, ACCEPTABLE_COOLING_STATES)){
      BatteryCharacter batteryCharacteristics = populateOperatingTemperatureValues(coolingType);
      BreachType breachType = inferBreach(batteryCharacteristics, tempValue);
      return alertBreach(alertOption, breachType);
  }
    return false;
}
