#include <simvr.h>
#include <simvr_log.h>

#include "ProjectCarsMapper.h"

#include <iostream>
#include <thread>

/* -- Main -------------------------------------------------------------- */
SIMVRSDK::SIMVRDataPacket DefaultPacket()
{
	SIMVRSDK::SIMVRDataPacket packet = {};
	packet.axis1 = 0.5f;
	packet.axis2 = 0.5f;
	packet.axis3 = 0.5f;
	packet.axis4 = 0.5f;
	packet.axis5 = 0.5f;
	packet.axis6 = 0.5f;

	//Axis speed/accel controls
	packet.speedAxis123 = 1.0f;
	packet.accelAxis123 = 0.5f;
	packet.speedAxis4 = 1.0f;
	packet.accelAxis4 = 0.5f;

	//Axis Processing
	packet.roll = 0.0f;
	packet.pitch = 0.0f;
	packet.yaw = 0.0f;
	packet.heave = 0.0f;
	packet.sway = 0.0f;
	packet.surge = 0.0f;

	packet.rotationMotionRatio = 0.3f;
	packet.gravityMotionRatio = 0.7f;

	packet.commandCount = 0;
	return packet;
}

float Scale(float value, float limit)
{
	if(value < -limit)
	{
		value = -limit;
	}
	if(value > limit)
	{
		value = limit;
	}
	value /= limit;
	return value;
}

void PrintLog()
{
	auto size = SIMVRSDK::Debug::GetBackLogSize();
	if(size > 0)
	{
		auto buffer = SIMVRSDK::Debug::GetBackLog();
		std::string message(buffer, buffer + size);
		SIMVRSDK::Debug::ClearBackLog();

		std::cout << message;
	}
}

int main()
{
	SIMVRSDK::SIMVR simvr{};

	std::cout << "SIMVR SDK version" << simvr.GetVersion() << std::endl;

	simvr.Open("");

	simvr.SetOriginMode(false);
	simvr.SetAxisProcessingMode(true);

	auto packet = DefaultPacket();

	while(simvr.IsRunning())
	{
		PrintLog();

		ProjectCars::Mapper mapper;
		auto property = mapper.Get();
		packet.roll = 0;
		packet.pitch = 0;
		packet.yaw = Scale(-property.yaw, 1.3f);
		packet.heave = Scale(property.heave, 20.f);
		packet.sway = Scale(property.sway, 20.f);
		packet.surge = Scale(-property.surge, 20.f);
		simvr.Write(&packet);
	}

	PrintLog();
}