#include "processor.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Processor::Processor(Word *memory) : 
	m_memory(memory)
{
	initCommands();
	reset();
}

void Processor::initCommands()
{
	commands[Nop] = new NOPCmd();
	commands[Stop] = new StopCmd();

	commands[AddI] = new AddICmd();
	commands[SubI] = new SubICmd();
	commands[MulI] = new MulICmd();
	commands[MulUI] = new MulUICmd();
	commands[DivI] = new DivICmd();
	commands[DivUI] = new DivUICmd();
	commands[ModI] = new ModICmd();
	commands[ModUI] = new ModUICmd();

	commands[AddF] = new AddFCmd();
	commands[SubF] = new SubFCmd();
	commands[MulF] = new MulFCmd();
	commands[DivF] = new DivFCmd();

	commands[MovRR] = new MovCmdRR();
	commands[MovRM] = new MovCmdRM();
	commands[MovMR] = new MovCmdMR();

	commands[CmpI] = new CmpICmd();
	commands[CmpUI] = new CmpUICmd();
	commands[CmpF] = new CmpFCmd();

	commands[InI] = new InICmd();
	commands[OutI] = new OutICmd();

	commands[InF] = new InFCmd();
	commands[OutF] = new OutFCmd();

	commands[Jmp] = new JmpCmd();
	commands[Je] = new JeCmd();
	commands[Jl] = new JlCmd();
	commands[Jg] = new JgCmd();
	commands[Call] = new CallCmd();
	commands[Ret] = new RetCmd();
}

inline
void Processro::reset() {
	resetFlags();
	setIP(0);
}

void Processor::resetFlags() {
	m_psw.JF = 0;
	m_psw.RF = 0;
	m_psw.Stop = 0;
}

void Processor::interpreter() {
	while (m_psw.Stop != 1) {
		m_currentCommand = m_memory[m_IP].mc;
		commands[m_currentCommand.code]->execute(m_currentCommand, this);
		
		CommandSize size = CommandSizeRecognizer::getCommandSize(m_currentCommand);
		if (m_psw.Stop != 1 && size == SHORT) {	
			// Вторую команду не "замеряем". Будем считать, что она тоже короткая
			m_currentCommand.fcmd16 = m_currentCommand.scmd16;
			commands[m_currentCommand.code]->execute(m_currentCommand, this);
		}

		if (!m_psw.JF) {
			m_IP++;
		} else {
			m_psw.JF = 0;
		}
	}
}

void Processor::executeCommand() {
	static bool incIP = true;	// Необходимо ли инкрементировать IP
	
	// Текущая команда уже правильно выставлена при установке IP
	commands[m_currentCommand.code]->execute(m_currentCommand, this);
	
	// Определяем надо ли смещать IP
	// IP не надо смещать, если первая команда в слове была короткая
	CommandSize size = CommandSizeRecognizer::getCommandSize(m_currentCommand);
	incIP = (size == LONG || !incIP);
	
	// Текущую команду неопроходимо выставить заранее, так как
	// отладчик будет запрашивать команду до её исполнения
	if (!m_psw.JF) {
		if(incIP) {
			m_IP++;
			m_currentCommand = m_memory[m_IP].mc;
		} else {
			m_currentCommand.fcmd16 = m_currentCommand.scmd16;
		}
	} else {
		incIP = true;
		m_psw.JF = 0;
		m_currentCommand = m_memory[m_IP].mc;
	}
}

Address Processor::getIP() const {
	return m_IP;
}

void Processor::setIP(const Address &address) {
	m_IP = address;
	m_currentCommand = m_memory[m_IP].mc;
}

MemCmd Processor::getCurrentCommand() const {
	return m_currentCommand;
}


