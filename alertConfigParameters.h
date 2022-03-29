#include <stddef.h>

#define ACCEPTABLE_ALERT_VALUE 2
#define ACCEPTABLE_COOLING_STATES 3

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  INVALID_COOLING_VALUE
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef struct {
  CoolingType coolingType;
  float lowerLimitOfTemp;
  float upperLimitOfTemp;
  char brand[48];
} BatteryCharacter;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL, 
  INVALID_ALERT_VALUE
} AlertOptions;

//define a function pointer which consumes breachType and alerts via mail / controller
typedef void (*func_ptrAlertBreach)(BreachType);

typedef struct 
{
  func_ptrAlertBreach alertFunction;
} AlertTargetFunction;

extern BatteryCharacter BatteryTemperatureValues[3];
extern char AlertMessageForMail[3][100];
extern AlertTargetFunction AlertTargetFuncConfiguration[2];
