#include "main.h"

#include "autolib/api.hpp"
#include "okapi/api.hpp"
#include "robot/api.hpp"

#include <memory>

using namespace autolib;
using namespace lib7842;
using namespace okapi;
using namespace pros;
using namespace Robot;
using namespace Screen;

void initialize() {
	//wait for adi ports
	delay(500);
	printf("Initialize\n");

	Robot::init();
	Screen::init();

}

void disabled() {
	printf("Disabled\n");
}

void competition_initialize() {
	printf("Competition Initialize\n");
}

void autonomous() {
	printf("Autonomous\n");
}

void opcontrol() {
	printf("opControl\n");

	while(true){
		Drive::runIntake(1);
		Drive::runTray(1);
		Drive::runChassis(1, true);
		Drive::trayMacro();
		delay(20);
	}
}
