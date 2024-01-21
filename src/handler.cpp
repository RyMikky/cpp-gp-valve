#include "handler.h"

namespace handler {

	Handler::Handler(int args, char** argv)
		: _settings(console::ParseCommandLine(args, argv)) 
	{};


} // namespace handler