#pragma once
#include <Core/Math/Vector2.h>
#include <Core/Math/Vector3.h>

namespace Core::Graphics
{
	using namespace Core::Math;

	struct Vertex
	{
		Vector2f position;
		Vector3f color;
	};
}