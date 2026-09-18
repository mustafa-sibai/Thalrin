#include <Thalrin/Engine.h>
#include "Scenes/TestScene.h"
//#include <iostream>
//#include <string>
//#include "Generated/sample.pb.h"

using namespace Thalrin;

int main()
{
	Engine::GetInstance()->GetSceneManager().AddScene(new TestScene());
	Engine::GetInstance()->Run();
	return 0;

	/*GOOGLE_PROTOBUF_VERIFY_VERSION;

	thalrin::test::Entity entity;
	entity.set_id(42);
	entity.set_name("Mustafa");
	entity.set_type(thalrin::test::ENTITY_TYPE_PLAYER);

	auto* pos = entity.mutable_position();
	pos->set_x(1.0f);
	pos->set_y(2.0f);
	pos->set_z(3.0f);

	entity.add_tags("hero");
	entity.add_tags("admin");

	std::string bytes;
	if (!entity.SerializeToString(&bytes))
	{
		std::cerr << "Serialize failed\n";
		return 1;
	}
	std::cout << "Serialized size: " << bytes.size() << " bytes\n";

	thalrin::test::Entity parsed;
	if (!parsed.ParseFromString(bytes))
	{
		std::cerr << "Parse failed\n";
		return 1;
	}

	std::cout << parsed.DebugString();

	if (parsed.id() != entity.id())
	{
		std::cerr << "id mismatch\n";
		return 1;
	}
	if (parsed.name() != entity.name())
	{
		std::cerr << "name mismatch\n";
		return 1;
	}
	if (parsed.tags_size() != 2)
	{
		std::cerr << "tags mismatch\n";
		return 1;
	}

	std::cout << "Round-trip OK\n";

	google::protobuf::ShutdownProtobufLibrary();*/
}