#include <iostream>
#include <cstring>
#include <functional>

#include "Processor/Processor.h"
#include "Debugger/Debugger.h"
#include "Debugger/CommandDebugger/CommandDebugger.h"
#include "Loader/Loader.h"
#include "Exception.h"

bool debug = false;

void setDebugMod(Processor &);

const unordered_map<string, void(*)(Processor &)> HANDLERS {
		{"-d", &setDebugMod}
};

void setDebugMod(Processor &processor) {
	debug = true;
}

void handleCommandLineArguments(int argc, char **argv, Processor &processor) {
	if(argc < 2) {
		throw NotEnoughArguments();
	}

	Loader::load(processor, argv[1]);
	for(int i = 2; i < argc; i++) {
		auto handlerIter = HANDLERS.find(argv[i]);
		if(handlerIter != HANDLERS.end()) {
			HANDLERS.at(argv[i])(processor);
		} else {
			throw UnknownCommandLineParameters();
		}
	}
}

inline 
void runDebugger(Processor &processor) {
	CommandDebugger view;
	Debugger debugger(&view, &processor);
	view.setDebugger(&debugger);
	debugger.debug();
}

int main(int argc, char* argv[]) {
	setlocale(0, "rus");
		
	try {
		Word memory[MEMORY_SIZE];
		Processor processor(memory);
		handleCommandLineArguments(argc, argv, processor);
		
		if(!debug) {
			processor.interpreter();
		} else {
			runDebugger(processor);			
		}
		
	}
	catch (const exception & ex) {
		cerr << ex.what() << endl;
	}
	system("pause");
}
