// Task1_v2_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Task1_v2/ccar.h"
#include <functional>

void ExpectOperationSuccess(CCar& car, const std::function<bool(CCar& car)>& op, bool engineIsOn, int gear, int speed, MovingDirection direction)
{
	REQUIRE(op(car)); // ожидаем, что операция вернет true (успех)
	// Сравниваем состояние свойства объект с ожидаемым
	CHECK(car.EngineIsOn() == engineIsOn);
	CHECK(car.GetGear() == gear);
	CHECK(car.GetSpeed() == speed);
	CHECK(car.GetDirection() == direction);
	return;
}

void ExpectOperationFailure(CCar const& car, const std::function<bool(CCar& car)>& op)
{
	auto clone(car); // сделали клон объекта
	REQUIRE(!op(clone)); // ожидаем, что операция завершится неуспешно (передаем клон)
					     // проверяем, что после выполнения операции состояние клона не отличается от оригинала 
					     // (операция в случае неудачи оставляет объект в состоянии, в котором он пребывал до операции)
	CHECK(clone.EngineIsOn() == car.EngineIsOn());
	CHECK(clone.GetGear() == car.GetGear());
	CHECK(clone.GetSpeed() == car.GetSpeed());
	CHECK(clone.GetDirection() == car.GetDirection());
	return;
}

TEST_CASE("Can set engine on only when it is off")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	ExpectOperationSuccess(car, [](auto&& car) {return car.TurnOnEngine(); }, true /*on*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOnEngine(); });
}

TEST_CASE("Can set engine off only when it is on")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	car.TurnOnEngine();
	ExpectOperationSuccess(car, [](auto&& car) {return car.TurnOffEngine(); }, false /*off*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOffEngine(); });
}

TEST_CASE("Can set only 0 gear while engine is off")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, false /*off*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
}

TEST_CASE("Can't set speed while engine is off")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, false /*off*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(10); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(0); });
}

TEST_CASE("Can set gear exept 1 and -1 at gear 0 and speed 0")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	car.TurnOnEngine();
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(3); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(4); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(5); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(6); }); //out of range
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(-1); }, true /*on*/, -1 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(1); }, true /*on*/, 1 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(-1); }, true /*on*/, -1 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
}
TEST_CASE("Can set appropriate speed and gear for moving FORFARD")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	car.TurnOnEngine();
	//can't set speed out of bounds
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(1); }, true /*on*/, 1 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(20); }, true /*on*/, 1 /*gear*/, 20 /*speed*/, MovingDirection::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(50); });
	//can't set -1, 3, 4, 5 gear
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(3); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(4); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(5); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	// set 2 gear and more speed
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(2); }, true /*on*/, 2 /*gear*/, 20 /*speed*/, MovingDirection::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(50); }, true /*on*/, 2 /*gear*/, 50 /*speed*/, MovingDirection::FORWARD);
	// set 4 gear
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(4); }, true /*on*/, 4 /*gear*/, 50 /*speed*/, MovingDirection::FORWARD);
	// set 0 gear, but can't -1 because of big speed
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, 0 /*gear*/, 50 /*speed*/, MovingDirection::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	// can't encrease speed at gear 0
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(40); }, true /*on*/, 0 /*gear*/, 40 /*speed*/, MovingDirection::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(50); });
	// set 3 gear, not 1
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(3); }, true /*on*/, 3 /*gear*/, 40 /*speed*/, MovingDirection::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });	
}

TEST_CASE("Can set speed at gear -1, can't set gear -1 from 0 at speed > 0")
{
	CCar car;// engine is off, gear = 0, speed = 0, INPLACE
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	//can't set -1 gear from 0 while moving FORWARD
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(0); }, true /*on*/, 0 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(-1); }, true /*on*/, -1 /*gear*/, 0 /*speed*/, MovingDirection::INPLACE);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(10); }, true /*on*/, -1 /*gear*/, 10 /*speed*/, MovingDirection::BACKWARD);
	//can't set speed out of bounds
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(40); });
	//can't set gear -1 after 0 at >0 speed
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, 0 /*gear*/, 10 /*speed*/, MovingDirection::BACKWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
}
