#pragma once

#define PASSIVE_COOLING_LOW_LIMIT		0
#define PASSIVE_COOLING_HIGH_LIMIT		35
#define HI_ACTIVE_COOLING_LOW_LIMIT		0
#define HI_ACTIVE_COOLING_HIGH_LIMIT	45
#define MED_ACTIVE_COOLING_LOW_LIMIT	0
#define MED_ACTIVE_COOLING_HIGH_LIMIT	40

#define SUCCESS							1
#define FAIL							0

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
  double lowerLimit;
  double upperLimit;
} TemperatureLimit;

TemperatureLimit determineTempLimits(CoolingType coolingType);
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
int sendToController(BreachType breachType);
int sendToEmail(BreachType breachType);
