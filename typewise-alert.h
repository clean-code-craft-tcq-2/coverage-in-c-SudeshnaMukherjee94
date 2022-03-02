#pragma once

BreachType inferBreach(BatteryCharacter batteryCharacteristics, float tempValue);
BatteryCharacter populateOperatingTemperatureValues(CoolingType coolingType);
bool checkAndAlert(AlertOptions alertOption, CoolingType coolingType, float tempValue);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
bool alertBreach(AlertOptions alertOption, BreachType breachType);
bool validateEnumValue(int enumValue, int maxPossibleValue);
