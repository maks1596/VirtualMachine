#pragma once

#include "../Processor/Processor.h"

class Loader {
public:
	static void load(Processor &processor, const string &name_file);

private:
	static Address m_loadAddress;
};

