#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "alertConfigParameters.h"
#include "typewise-alert.h"


TEST_CASE("ValidateEnumValue - Passing enum value satisfying the range - Positive use case ") {
  bool validateStatus = validateEnumValue (2,3);
  REQUIRE(validateStatus  == true);
}

TEST_CASE("ValidateEnumValue - Passing enum value greater than the maximum accepted value - Negative use case ") {
  bool validateStatus = validateEnumValue (4,3);
  REQUIRE(validateStatus  == false);
}


TEST_CASE("ValidateEnumValue - Passing enum value lesser than zero - Negative use case ") {
  bool validateStatus = validateEnumValue (-4,3);
  REQUIRE(validateStatus  == false);
}

TEST_CASE("ValidateEnumValue - Passing enum value lesser than zero but greater than maximum accepted value - Negative use case  ") {
  bool validateStatus = validateEnumValue (-5,-7);
  REQUIRE(validateStatus  == false);
}

TEST_CASE("InferBreach -Temperature value is less than operating lower limit") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics.lowerLimitOfTemp  = 25;
  batteryCharacteristics.upperLimitOfTemp  = 60;
  float tempValue = 10;
  REQUIRE(inferBreach(batteryCharacteristics, tempValue) == TOO_LOW);
}

TEST_CASE("InferBreach - Temperature value is more than operating higher limit") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics.lowerLimitOfTemp  = 25;
  batteryCharacteristics.upperLimitOfTemp  = 60;
  float tempValue = 65;
  REQUIRE(inferBreach(batteryCharacteristics, tempValue) == TOO_HIGH);
}


TEST_CASE("InferBreach - Temperature value is in the normal operating range") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics.lowerLimitOfTemp  = 25;
  batteryCharacteristics.upperLimitOfTemp  = 60;
  float tempValue = 43;
  REQUIRE(inferBreach(batteryCharacteristics, tempValue) == NORMAL);
}

TEST_CASE("populateOperatingTemperatureValues - Populate the lower and upper temperature limits based on cooling type - PASSIVE_COOLING ") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics = populateOperatingTemperatureValues(PASSIVE_COOLING);
  REQUIRE(batteryCharacteristics.coolingType  == PASSIVE_COOLING);
  REQUIRE(batteryCharacteristics.lowerLimitOfTemp  == 0);
  REQUIRE(batteryCharacteristics.upperLimitOfTemp  == 35);
}

TEST_CASE("populateOperatingTemperatureValues - Populate the lower and upper temperature limits based on cooling type - HI_ACTIVE_COOLING ") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics = populateOperatingTemperatureValues(HI_ACTIVE_COOLING);
  REQUIRE(batteryCharacteristics.coolingType  == HI_ACTIVE_COOLING);
  REQUIRE(batteryCharacteristics.lowerLimitOfTemp  == 0);
  REQUIRE(batteryCharacteristics.upperLimitOfTemp  == 45);
}

TEST_CASE("populateOperatingTemperatureValues - Populate the lower and upper temperature limits based on cooling type - MED_ACTIVE_COOLING ") {
  BatteryCharacter batteryCharacteristics;
  batteryCharacteristics = populateOperatingTemperatureValues(MED_ACTIVE_COOLING);
  REQUIRE(batteryCharacteristics.coolingType  == MED_ACTIVE_COOLING);
  REQUIRE(batteryCharacteristics.lowerLimitOfTemp  == 0);
  REQUIRE(batteryCharacteristics.upperLimitOfTemp  == 40);
}

TEST_CASE("AlertBreach - Alert message to controller with breach level NORMAL ") {
  bool alertStatus = alertBreach(TO_CONTROLLER, NORMAL);
  REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Alert message to controller with breach level TOO_LOW ") {
  bool alertStatus = alertBreach(TO_CONTROLLER, TOO_LOW);
  REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Alert message to controller with breach level TOO_HIGH ") {
  bool alertStatus = alertBreach(TO_CONTROLLER, TOO_HIGH);
  REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Alert message to email with breach level NORMAL ") {
   bool alertStatus = alertBreach(TO_EMAIL, NORMAL);
    REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Alert message to email with breach level TOO_LOW ") {
  bool alertStatus = alertBreach(TO_EMAIL, TOO_LOW);
  REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Alert message to email with breach level TOO_HIGH ") {
  bool alertStatus = alertBreach(TO_EMAIL, TOO_HIGH);
  REQUIRE(alertStatus  == true);
}

TEST_CASE("AlertBreach - Negative use case - Alert with invalid configuration ") {
  bool alertStatus = alertBreach(INVALID_ALERT_VALUE, TOO_HIGH);
  REQUIRE(alertStatus  == false);
}

TEST_CASE("CheckAndAlert - TO_CONTROLLER , PASSIVE_COOLING with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,20);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,38);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,-5);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - TO_CONTROLLER , HI_ACTIVE_COOLING  with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,30);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,49);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,-2);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - TO_CONTROLLER , MED_ACTIVE_COOLING with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING, 32);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,43);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,-3);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - TO_EMAIL , PASSIVE_COOLING with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_EMAIL,PASSIVE_COOLING,20);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,PASSIVE_COOLING,38);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,PASSIVE_COOLING,-5);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - TO_EMAIL , HI_ACTIVE_COOLING  with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,30);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,49);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,-2);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - TO_EMAIL , MED_ACTIVE_COOLING with all range of temp values ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING, 32);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING,43);
   REQUIRE(alertStatus  == true);
   alertStatus = checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING,-3);
   REQUIRE(alertStatus  == true);
}

TEST_CASE("CheckAndAlert - Check negative scenario ") {
   bool alertStatus;
   alertStatus= checkAndAlert(TO_EMAIL,INVALID_COOLING_VALUE, 32);
   REQUIRE(alertStatus  == false);
   alertStatus = checkAndAlert(TO_CONTROLLER,INVALID_COOLING_VALUE,43);
   REQUIRE(alertStatus  == false);
   alertStatus = checkAndAlert(INVALID_ALERT_VALUE,PASSIVE_COOLING,43);
   REQUIRE(alertStatus  == false);
   alertStatus = checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,30);
   REQUIRE(alertStatus  == true);
}
