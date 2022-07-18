#include "typewise-alert.h"
#include <stdio.h>

TemperatureLimit determineTempLimits(CoolingType coolingType){
  TemperatureLimit tempLimit;
  if(coolingType == PASSIVE_COOLING){
	  tempLimit.lowerLimit = PASSIVE_COOLING_LOW_LIMIT;
	  tempLimit.upperLimit = PASSIVE_COOLING_HIGH_LIMIT;
  }
  else if(coolingType == HI_ACTIVE_COOLING){
	  tempLimit.lowerLimit = HI_ACTIVE_COOLING_LOW_LIMIT;
	  tempLimit.upperLimit = HI_ACTIVE_COOLING_HIGH_LIMIT;
  }
  else{
	 tempLimit.lowerLimit = MED_ACTIVE_COOLING_LOW_LIMIT;
	 tempLimit.upperLimit = MED_ACTIVE_COOLING_HIGH_LIMIT;
  }
  return tempLimit;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  BreachType retSts_en = NORMAL;
  if(value < lowerLimit) {
	  retSts_en = TOO_LOW;
  }
  else if(value > upperLimit) {
	  retSts_en = TOO_HIGH;
  }
  return retSts_en;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  TemperatureLimit tempLimit;
  tempLimit = determineTempLimits(coolingType);
  return inferBreach(temperatureInC, tempLimit.lowerLimit, tempLimit.upperLimit);
}

int checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  int retSts = FAIL;
  if(alertTarget == TO_CONTROLLER){
	  retSts = sendToController(breachType);
  }
  else{
	  retSts = sendToEmail(breachType);
  }
  return retSts;
}
