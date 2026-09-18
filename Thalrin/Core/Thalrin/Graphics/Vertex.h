#pragma once
#include <Thalrin/Math/Vector2.h>
#include <Thalrin/Math/Vector3.h>

namespace Thalrin::Graphics
{
	using namespace Thalrin::Math;

	struct Vertex
	{
		Vector2f position;
		Vector3f color;
	};
}