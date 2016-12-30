#pragma once

namespace ProjectCars
{
	struct Property
	{
		float roll;
		float pitch;
		float yaw;
		float heave;
		float sway;
		float surge;
	};

	class Mapper
	{
	public:
		Mapper();
		Property Get() const;

	private:
		Property property = {};
	};
}
