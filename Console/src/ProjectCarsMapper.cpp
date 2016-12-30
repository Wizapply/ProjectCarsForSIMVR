#include "ProjectCarsMapper.h"

#include <Windows.h>
#include <memory>

#include "SharedMemory.h"

namespace ProjectCars
{
	Mapper::Mapper()
	{
		const char* key = "$pcars$";
		using Handle = std::remove_pointer<HANDLE>::type;
		std::unique_ptr<Handle, decltype(&CloseHandle)> mapping(
			OpenFileMappingA(PAGE_READONLY, FALSE, key),
			CloseHandle);
		if(!mapping)
		{
			return;
		}

		std::unique_ptr<SharedMemory, decltype(&UnmapViewOfFile)> sharedMemory(
			reinterpret_cast<SharedMemory*>(MapViewOfFile(mapping.get(), PAGE_READONLY, 0, 0, sizeof(SharedMemory))),
			UnmapViewOfFile);
		if(!sharedMemory)
		{
			return;
		}

		property.roll = sharedMemory->mAngularVelocity[VEC_Z];
		property.pitch = sharedMemory->mAngularVelocity[VEC_X];
		property.yaw = sharedMemory->mAngularVelocity[VEC_Y];
		property.heave = sharedMemory->mLocalAcceleration[VEC_Y];
		property.sway = sharedMemory->mLocalAcceleration[VEC_X];
		property.surge = sharedMemory->mLocalAcceleration[VEC_Z];
	}

	Property Mapper::Get() const
	{
		return property;
	}
}