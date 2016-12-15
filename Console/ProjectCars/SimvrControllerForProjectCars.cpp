#include "simvr.h"
#include "ProjectCarsMapper.h"

#include <iostream>

SIMVRSDK::SIMVRDataPacket DefaultPacket()
{
	SIMVRSDK::SIMVRDataPacket packet={};
	packet.axis1 = 0.5f;
	packet.axis2 = 0.5f;
	packet.axis3 = 0.5f;
	packet.axis4 = 0.5f;

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
	return packet;
}

float ToSimvrValue(float value)
{
	const float limit = 20.0f;
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

int main()
{
	SIMVRSDK::SIMVR simvr{};
	simvr.Open("");
	simvr.SetOriginMode(false);
	simvr.SetAxisProcessingMode(true);

	auto packet = DefaultPacket();

	while(true)
	{
		ProjectCars::Mapper mapper;
		auto property = mapper.Get();
		packet.roll = property.roll;
		packet.pitch = property.pitch;
		packet.yaw = property.yaw / 3.14f;
		packet.heave = ToSimvrValue(property.heave);
		packet.sway = ToSimvrValue(property.sway);
		packet.surge = ToSimvrValue(-property.surge);
		simvr.Write(&packet);
		std::cout << packet.yaw << std::endl;
	}
}