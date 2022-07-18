#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW); 		//value < lowerlimit
  REQUIRE(inferBreach(35.1, 20, 35) == TOO_HIGH); 	//value > upper limit
  REQUIRE(inferBreach(21.1, 21, 35) == NORMAL); 	//value in range
}

TEST_CASE("determines the temperature limits based on the coolingType") {
  TemperatureLimit tempLimit;
  
  //Test Lower & Upper Limits of Passive Cooling Type
  tempLimit = determineTempLimits(PASSIVE_COOLING);
  REQUIRE((tempLimit.lowerLimit == PASSIVE_COOLING_LOW_LIMIT) && (tempLimit.upperLimit == PASSIVE_COOLING_HIGH_LIMIT));
  //Test Lower & Upper Limits of Hi_Active Cooling Type
  tempLimit = determineTempLimits(HI_ACTIVE_COOLING);
  REQUIRE((tempLimit.lowerLimit == HI_ACTIVE_COOLING_LOW_LIMIT) && (tempLimit.upperLimit == HI_ACTIVE_COOLING_HIGH_LIMIT));
  //Test Lower & Upper Limits of Med_Active Cooling Type
  tempLimit = determineTempLimits(MED_ACTIVE_COOLING);
  REQUIRE((tempLimit.lowerLimit == MED_ACTIVE_COOLING_LOW_LIMIT) && (tempLimit.upperLimit == MED_ACTIVE_COOLING_HIGH_LIMIT));
}

TEST_CASE("Alert for Too low & Too High temp via Email") {
  REQUIRE(sendToEmail(TOO_LOW)== SUCCESS);	//Alert for Too-Low Temp via Email
  REQUIRE(sendToEmail(TOO_HIGH)== SUCCESS); //Alert for Too-High Temp via Email
}

TEST_CASE("Checks and Alerts the Temperature Breach based on coolingType ") {
  BatteryCharacter batteryChar;
  
  batteryChar.coolingType = PASSIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0)==SUCCESS);	//Alert via Controller for temp in range
  assert(checkAndAlert(TO_EMAIL,batteryChar,35)==SUCCESS);		//Alert via Email for temp in range
}
