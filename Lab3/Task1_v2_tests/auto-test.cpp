// Task1_v2_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Task1_v2/auto.h"

TEST_CASE("test setting engine on and off and setting nothing except 0 gear while engine is off")
{
	CCar car;

	CHECK(car.EngineIsOn() == false);
	CHECK(car.TurnOffEngine() == false);
	CHECK(car.TurnOnEngine() == true);

	CHECK(car.EngineIsOn() == true);
	CHECK(car.GetDirection() == movingDirection::INPLACE);
	CHECK(car.GetSpeed() == 0);
	CHECK(car.GetGear() == 0);
	
	CHECK(car.TurnOnEngine() == false);
	CHECK(car.TurnOffEngine() == true);
	CHECK(car.TurnOffEngine() == false);

	CHECK(car.SetGear(1) == false);
	CHECK(car.SetSpeed(0) == false);
	CHECK(car.SetSpeed(10) == false);
	CHECK(car.SetGear(-1) == false);
	CHECK(car.SetGear(0) == true);
}

TEST_CASE("test setting speed and positive gear")
{
	CCar car;
	CHECK(car.SetSpeed(10) == false);
	CHECK(car.SetSpeed(0) == false);
	CHECK(car.TurnOnEngine() == true);
	//can't enc speed in 0 gear
	CHECK(car.SetSpeed(10) == false);
	//can't set 2, 3, 4, 5 gear
	CHECK(car.SetGear(2) == false);
	CHECK(car.SetGear(3) == false);
	CHECK(car.SetGear(4) == false);	
	CHECK(car.SetGear(5) == false);
	//set 1 gear and correct speed
	CHECK(car.SetGear(1) == true);
	CHECK(car.SetSpeed(50) == false);
	CHECK(car.SetSpeed(20) == true);
	//can't set -1, 3, 4, 5 gear
	CHECK(car.SetGear(-1) == false);
	CHECK(car.SetGear(3) == false);
	CHECK(car.SetGear(4) == false);
	CHECK(car.SetGear(5) == false);
	// set 2 gear and more speed
	CHECK(car.SetGear(2) == true);
	CHECK(car.SetSpeed(50) == true);
	// set 4 gear and more speed
	CHECK(car.SetGear(4) == true);
	// set 0 gear, but can't -1 because of big speed
	CHECK(car.SetGear(0) == true);
	CHECK(car.SetGear(-1) == false);
	// set 3 gear, not 1
	CHECK(car.SetGear(1) == false);
	CHECK(car.SetGear(3) == true);
	// set 0 gear, but can't enc speed, only dec
	CHECK(car.SetGear(0) == true);
	CHECK(car.SetSpeed(60) == false);
	CHECK(car.SetSpeed(20) == true);
	//stop
	CHECK(car.SetSpeed(0) == true);
	//turn off
	CHECK(car.TurnOffEngine() == true);
}

TEST_CASE("test setting speed and negative gear")
{
	CCar car;
	CHECK(car.TurnOnEngine() == true);
	CHECK(car.SetGear(1) == true);
	CHECK(car.SetSpeed(10) == true);
	//can't set -1 gear from 1
	CHECK(car.SetGear(-1) == false);
	//set 0 gear
	CHECK(car.SetGear(0) == true);
	//can't set -1 gear from 0 while speed > 0
	CHECK(car.SetGear(-1) == false);
	//stopping and set -1 gear
	CHECK(car.SetSpeed(0) == true);
	CHECK(car.SetGear(-1) == true);
	//can't set -1 gear from 0 gear while speed >0 and direction is backward
	CHECK(car.SetSpeed(10) == true);
	CHECK(car.SetGear(0) == true);
	CHECK(car.SetGear(-1) == false);
}
