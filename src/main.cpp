#include "main.h"

#include "lib7842/api.hpp"
#include "okapi/api.hpp"

#include <memory>
#include <map>
#include <functional>

using namespace lib7842;
using namespace okapi;

std::shared_ptr<ChassisController> chassis;
std::shared_ptr<XDriveModel> model;
std::shared_ptr<CustomOdometry> odom;
std::shared_ptr<MotorGroup> intake;
std::shared_ptr<MotorGroup> tray;
std::shared_ptr<Potentiometer> trayPotent;
std::shared_ptr<AsyncPosPIDController> trayController7;
std::shared_ptr<AsyncPosPIDController> trayController10;
std::shared_ptr<Controller> master;

std::shared_ptr<GUI::Screen> scr;
GUI::Selector* selector;

std::map<std::string, std::function<void()>&> routines;

std::string routine;

void initialize() {
	pros::delay(500);//wait for ADIEncoders to catch up

	chassis = ChassisControllerBuilder()
<<<<<<< HEAD
		.withMotors(2,3,-9,-10)
//		.withSensors( ADIEncoder(7,8), ADIEncoder(1,2,true) )
		.withDimensions( AbstractMotor::gearset::green, ChassisScales({10.2101761242_in, 3.25_in}, imev5GreenTPR) )
=======
		.withMotors({2,3},{-9,-10})
		.withSensors( ADIEncoder(7,8), ADIEncoder(1,2,true) )
		.withDimensions( AbstractMotor::gearset::green, ChassisScales({12.5_in, 3.25_in, 0_in, 2.75_in}, imev5GreenTPR) )
>>>>>>> ca6660dbe6e8e647341a638067556c2accbe033c
		.build();

	model = std::dynamic_pointer_cast<XDriveModel>(chassis->getModel());

	odom = std::make_shared<CustomOdometry>(
		model, 
<<<<<<< HEAD
		ChassisScales(
			{10.2101761242_in, 3.25_in,10.2101761242_in, 3.25_in}, 
			imev5GreenTPR
		),
=======
		chassis->getChassisScales(),
>>>>>>> ca6660dbe6e8e647341a638067556c2accbe033c
		TimeUtilFactory::withSettledUtilParams()
	);

	intake = std::make_shared<MotorGroup>(MotorGroup({5,-6}));
	intake->setGearing(AbstractMotor::gearset::red);

	tray = std::make_shared<MotorGroup>(MotorGroup({1}));
	tray->setGearing(AbstractMotor::gearset::red);

	trayPotent = std::make_shared<Potentiometer>(3);

	trayController7 = std::make_shared<AsyncPosPIDController>(
		tray->getEncoder(),
		tray,
		TimeUtilFactory::withSettledUtilParams(),
		.0004,
		.0000,
		.00007,
		.0
	);
	trayController7->startThread();
	trayController7->flipDisable(true);

	trayController10 = std::make_shared<AsyncPosPIDController>(
		tray->getEncoder(),
		tray,
		TimeUtilFactory::withSettledUtilParams(),
		.0004,
		.0000,
		.00005,
		.0
	);
	trayController10->startThread();
	trayController10->flipDisable(true);

	master = std::make_shared<Controller>();

<<<<<<< HEAD
	routines["redBig"] = [&](){
=======
	routines.at("redBig") =[&](){
>>>>>>> ca6660dbe6e8e647341a638067556c2accbe033c
		printf("redBig");
	};
	routines.at("redSmall") = [&](){
		printf("redSmall");
	};
	routines.at("blueBig") = [&](){
		printf("blueBig");
	};
	routines.at("blueSmall") = [&](){
		printf("blueSmall");
	};
<<<<<<< HEAD
	scr = std::make_shared<GUI::Screen>( lv_scr_act(), LV_COLOR_MAKE(38,84,124) );
	scr->startTask("screenTask");

	GUI::Selector* iselector = dynamic_cast<GUI::Selector*>(
	    &scr->makePage<GUI::Selector>("Selector")
			.button("Red Big",   [&]() { routines.at("redBig")(); })
			.button("Red Small", [&]() { routines.at("redSmall")(); })
			.newRow()
			.button("Blue Big", [&]()   { routines.at("blueBig")(); })//*/
=======

	scr = std::make_shared<GUI::Screen>( lv_scr_act(), LV_COLOR_GREEN );
	scr->startTask("screenTask");

	GUI::Selector* iselector = dynamic_cast<GUI::Selector*>(
    	&scr->makePage<GUI::Selector>("Selector")
			.button("Red Big",   [&]() { routines.at("redBig")(); })
			.button("Red Small", [&]() { routines.at("redSmall")(); })
			.newRow()
			.button("Blue Big", [&]()   { routines.at("blueBig")(); })
>>>>>>> ca6660dbe6e8e647341a638067556c2accbe033c
			.button("Blue Small", [&]() { routines.at("blueSmall")(); })
			.build()
		);
	
	pros::delay(10);
	scr->makePage<GUI::Odom>().attachOdom(odom).attachResetter([&]() { model->resetSensors(); });

	scr->makePage<GUI::Graph>("Temp")
		.withRange(0,100)
		.withGrid(2,4)
		.withResolution(100)
		.withSeries("Intake", LV_COLOR_MAKE(6,214,160), []() { return intake->getTemperature(); })
		.withSeries("Tray", LV_COLOR_MAKE(239,71,111), []() { return tray->getTemperature(); })
<<<<<<< HEAD
		.withSeries("Drive", LV_COLOR_MAKE(255,209,102), []() { return model->getLeftSideMotor()->getTemperature(); }
	);//*/

=======
		.withSeries("Drive", LV_COLOR_MAKE(255,209,102), []() { return model->getLeftSideMotor()->getTemperature(); });
>>>>>>> ca6660dbe6e8e647341a638067556c2accbe033c
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	selector->run();
}

void taskFnc(void*){
	while(true){
		std::string out;
		//Tray Optimal || Tray Over Temp || Tray Over Crnt || Tray WARNING
		//Intk Optimal || Intk Over Temp || Intk Over Crnt || Intk WARNING
		//Drve Optimal || Drve Over Temp || Drve Over Crnt || Drve WARNING	

		const double maxTemp = 60;

		//TRAY
		if(tray->getTemperature()<maxTemp && !tray->isOverCurrent()){
			master->clearLine(0);
			out = "TrayTmp" + std::to_string(tray->getTemperature());
			master->setText(0,0,out.c_str());
		}else if(tray->getTemperature()>=maxTemp && !tray->isOverCurrent()){
			master->clearLine(0);
			master->setText(0,0,"Tray Over Temp");
			master->rumble("- -");
			pros::delay(500);
		}else if(!tray->getTemperature()>=maxTemp && tray->isOverTemp()){
			master->clearLine(0);
			master->setText(0,0,"Tray Over Crnt");
			master->rumble("- -");
			pros::delay(500);
		}
		//INTAKE
		if(intake->getTemperature()<maxTemp && !intake->isOverCurrent()){
			master->clearLine(1);
			out = "IntkTmp" + std::to_string(intake->getTemperature());
			master->setText(1,0,out.c_str());
		}else if(intake->getTemperature()>=maxTemp && !intake->isOverCurrent()){
			master->clearLine(1);
			master->setText(1,0,"Intk Over Temp");
			master->rumble("- -");
			pros::delay(500);
		}else if(!intake->getTemperature()>=maxTemp && intake->isOverTemp()){
			master->clearLine(1);
			master->setText(1,0,"Intk Over Crnt");
			master->rumble("- -");
			pros::delay(500);
		}
		//DRIVE
		if(model->getLeftSideMotor()->getTemperature()<maxTemp && !model->getLeftSideMotor()->isOverCurrent()){
			master->clearLine(1);
			out = "DrveTmp" + std::to_string(model->getLeftSideMotor()->getTemperature());
			master->setText(1,0,out.c_str());
		}else if(model->getLeftSideMotor()->getTemperature()>=maxTemp && !model->getLeftSideMotor()->isOverCurrent()){
			master->clearLine(1);
			master->setText(1,0,"Drve Over Temp");
			master->rumble("- -");
			pros::delay(500);
		}else if(model->getLeftSideMotor()->getTemperature()<maxTemp && !model->getLeftSideMotor()->isOverTemp()){
			master->clearLine(1);
			master->setText(1,0,"Drve Over Crnt");
			master->rumble("- -");
			pros::delay(500);
		}
	}
}

void opcontrol() {
	pros::Task task( taskFnc, NULL, "taskFnc" );
	bool intakeToggle = false;

	while (true) {
		double left;
		double right;
		if( std::abs(master->getAnalog(ControllerAnalog::rightY)) <= .1){
			left = master->getAnalog(ControllerAnalog::leftX);
			right = -master->getAnalog(ControllerAnalog::leftX);			
		}else{
			left = master->getAnalog(ControllerAnalog::rightY) + (.75 * master->getAnalog(ControllerAnalog::leftX));
			right = master->getAnalog(ControllerAnalog::rightY) + (-.75 * master->getAnalog(ControllerAnalog::leftX));
		}

		model->tank(left, right, .1);
		
		//INTAKE TOGGLE
		if(master->getDigital(ControllerDigital::Y)){
			intakeToggle=!intakeToggle;		
			while(master->getDigital(ControllerDigital::Y)){
				pros::delay(20);
			}	
		}

		//INTAKE
		if(master->getDigital(ControllerDigital::R1)){
			if(!intakeToggle){
				intake->moveVelocity(100);
			}
		}else if(master->getDigital(ControllerDigital::R2)){
			intake->moveVelocity(-100);
			intakeToggle = false;
		}else if(intakeToggle){
			intake->moveVelocity(100);
		}else{
			intake->moveVelocity(0);
		}

		//TRAY
		const double trayUp = 2000;
		const double trayDown = -50;
		if(master->getDigital(ControllerDigital::L1)){
			//trayController7
			trayController10->flipDisable(true);
			trayController7->flipDisable(false);
			trayController7->setTarget(trayUp);
		}else if(master->getDigital(ControllerDigital::L2)){
			//go back down
			trayController10->flipDisable(true);
			trayController7->flipDisable(true);
			tray->moveVelocity(-100);
		}else if(master->getDigital(ControllerDigital::right)){
			//trayController10
			trayController7->flipDisable(true);
			trayController10->flipDisable(false);
			trayController10->setTarget(trayUp);
		}else if(master->getDigital(ControllerDigital::down)){
			//nothing
		}else if(master->getDigital(ControllerDigital::Y)){
			trayController7->setTarget(trayDown);
			trayController10->setTarget(trayDown);
			while(master->getDigital(ControllerDigital::Y)){
				intake->moveVelocity(-100);
			}
			intake->moveVelocity(0);
		}

		pros::delay(20);
	}
}
