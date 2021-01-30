#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "../Define.h"
#include "../Processor/Processor.h"

using namespace std;

class DebuggerView;
typedef vector<Address> BreakPoints;

class Debugger {
public:
	Debugger(DebuggerView *view, Processor *processor) : 
		m_view(view),
		m_processor(processor) {}
	
	void debug();

	bool isBreakPoint(const Address &ip) const;
	const BreakPoints& getBreakPoints() const;
	void setBreakPointByCurrentAddress();
	void setBreakPoint(const Address &address);
	void deleteBreakPoint(const Address &address);
	void deleteAllBreakPoints();
	
	unsigned getRegisterValue(const unsigned &regNumber) const;
	unsigned getUnsignedRegisterValue(const unsigned &regNumber) const;
	int getIntegerRegisterValue(const unsigned &regNumber) const;
	float getFloatRegisterValue(const unsigned &regNumber) const;

	void setRegisterValue(const unsigned &regNumber, const unsigned &value);
	void setRegisterValue(const unsigned &regNumber, const int &value);
	void setRegisterValue(const unsigned &regNumber, const float &value);
	
	unsigned getMemory(const Address &address) const;
	unsigned getUnsignedMemory(const Address &address) const;
	int getIntegerMemory(const Address &address) const;
	float getFloatMemory(const Address &address) const;

	void setMemory(const Address &address, const unsigned &value);
	void setMemory(const Address &address, const int &value);
	void setMemory(const Address &address, const float &value);
	
	Address getCurrentAddress() const;
	MemCmd getCurrentCommand() const;
	MemCmd getCommand(const Address &address) const;
	
	void step();
	void stopProgram();
	
private:	
	DebuggerView *m_view;			// Указатель на представление отладчика
	Processor *m_processor;			// Указатель на процессор
	bool m_step = true;
	BreakPoints m_breakPoints;		// Точки остановы
};

