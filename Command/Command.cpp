#include "command.h"

#include <iostream>
#include "../Processor/Processor.h"


// Завершение работы процессора
void StopCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->m_psw.Stop = 1;
}

// Сложение целых чисел 
void AddICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].i += processor->RON[cmd.fcmd16.r1].i;
}

// Вычитание целых чисел
void SubICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].i -= processor->RON[cmd.fcmd16.r1].i;
}

// Умножение целых знаковых чисел
void MulICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].i *= processor->RON[cmd.fcmd16.r1].i;
}

// Деление целых знаковых чисел
void DivICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].i /= processor->RON[cmd.fcmd16.r1].i;
}

// Остаток от деления знаковых целых
void ModICmd::execute(const MemCmd &cmd, Processor *processor) {
	processor->RON[cmd.fcmd16.r2].i %= processor->RON[cmd.fcmd16.r1].i;
}


// Умножение целых беззнаковых чисел
void MulUICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].u *= processor->RON[cmd.fcmd16.r1].u;
}

// Деление целых беззнаковых чисел
void DivUICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].u /= processor->RON[cmd.fcmd16.r1].u;
}

// Остаток от деления беззнаковых целых
void ModUICmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].u %= processor->RON[cmd.fcmd16.r1].u;
}


// Сложение вещественных чисел
void AddFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].f += processor->RON[cmd.fcmd16.r1].f;
}

// Вычитание вещественных чисел
void SubFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].f -= processor->RON[cmd.fcmd16.r1].f;
}

// Умножение вещественных чисел
void MulFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].f *= processor->RON[cmd.fcmd16.r1].f;
}

// Деление вещественных чисел
void DivFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2].f = processor->RON[cmd.fcmd16.r1].f / processor->RON[cmd.fcmd16.r2].f;
}

// Пересылка значения регистр-регистр
void MovCmdRR::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.fcmd16.r2] = processor->RON[cmd.fcmd16.r1];
}
// Пересылка значений регистр-память
void MovCmdRM::execute(const MemCmd &cmd, Processor *processor)
{	
	processor->m_memory[cmd.cmd32.a] = processor->RON[cmd.cmd32.r2];
}
// Пересылка значения память-регистр
void MovCmdMR::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.cmd32.r2] = processor->m_memory[cmd.cmd32.a];
}

// Сравнение целых чисел
void CmpICmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->RON[cmd.fcmd16.r2].i == processor->RON[cmd.fcmd16.r1].i)
		processor->m_psw.RF = EQUAL;
	else if (processor->RON[cmd.fcmd16.r2].i > processor->RON[cmd.fcmd16.r1].i)
		processor->m_psw.RF = GREATER;
	else if (processor->RON[cmd.fcmd16.r2].i < processor->RON[cmd.fcmd16.r1].i)
		processor->m_psw.RF = LOWER;
}

// Сравнение беззнаковых целых чисел
void CmpUICmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->RON[cmd.fcmd16.r2].u == processor->RON[cmd.fcmd16.r1].u)
		processor->m_psw.RF = EQUAL;
	else if (processor->RON[cmd.fcmd16.r2].u > processor->RON[cmd.fcmd16.r1].u)
		processor->m_psw.RF = GREATER;
	else if (processor->RON[cmd.fcmd16.r2].u < processor->RON[cmd.fcmd16.r1].u)
		processor->m_psw.RF = LOWER;
}

// Сравнение вещественных чисел
void CmpFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->RON[cmd.fcmd16.r2].f == processor->RON[cmd.fcmd16.r1].f)
		processor->m_psw.RF = EQUAL;
	else if (processor->RON[cmd.fcmd16.r2].f > processor->RON[cmd.fcmd16.r1].f)
		processor->m_psw.RF = GREATER;
	else if (processor->RON[cmd.fcmd16.r2].f < processor->RON[cmd.fcmd16.r1].f)
		processor->m_psw.RF = LOWER;
}

// Ввод целого числа в память
void InICmd::execute(const MemCmd &cmd, Processor *processor)
{
	std::cin.clear();
	std::wcout << L"Ввод целого число: ";
	std::cin >> processor->RON[cmd.fcmd16.r1].i;
}

// Вывод целого числа из памяти
void OutICmd::execute(const MemCmd &cmd, Processor *processor)
{
	std::wcout << L"Вывод целого числа: ";
	std::cout << processor->RON[cmd.fcmd16.r1].i << std::endl;
}

// Ввод вещественного числа в память
void InFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	std::cin.clear();
	std::wcout << L"Ввод дробного числа: ";
	std::cin >> processor->RON[cmd.fcmd16.r1].f;
}

// Вывод вещественного числа из памяти
void OutFCmd::execute(const MemCmd &cmd, Processor *processor)
{
	std::wcout << L"Вывод дробного числа: ";
	std::cout << processor->RON[cmd.fcmd16.r1].f << std::endl;
}

// Переход к адресу
void JmpCmd::execute(const MemCmd &cmd, Processor *processor)
{
	switch (cmd.cmd32.r1) {
		case 1: {
			processor->setIP(cmd.cmd32.a);
			processor->m_psw.JF = 1;
		} break;
		case 2: {
			Address ip = processor->getIP();
			processor->setIP(ip + cmd.cmd32.r2 + cmd.cmd32.a);
			processor->m_psw.JF = 1;
		} break;
		case 3: {
			processor->setIP(cmd.cmd32.r2 + cmd.cmd32.a);
			processor->m_psw.JF = 1;
		} break;
	}
}

// Условный переход, если равно
void JeCmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->m_psw.RF == EQUAL)
		JmpCmd::execute(cmd, processor);
}

// Условный переход, если меньше
void JlCmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->m_psw.RF == LOWER)
		JmpCmd::execute(cmd, processor);
}

// Условный переход, если больше
void JgCmd::execute(const MemCmd &cmd, Processor *processor)
{
	if (processor->m_psw.RF == GREATER)
		JmpCmd::execute(cmd, processor);
}

// Вызов подпрограммы
void CallCmd::execute(const MemCmd &cmd, Processor *processor)
{
	processor->RON[cmd.cmd32.r1].u = processor->getIP() + 1;
	processor->m_returnAddress = cmd.cmd32.r1;
	JmpCmd::execute(cmd, processor);
}

// Возврат из подпрограммы
void RetCmd::execute(const MemCmd &cmd, Processor *processor)
{
	MemCmd jmpCmd = MemCmd();
	jmpCmd.cmd32.code = CommandCode::Jmp;	// ������ ������
	jmpCmd.cmd32.r1 = 1;					// ������
	jmpCmd.cmd32.a = (Address)processor->RON[processor->m_returnAddress].u; // �� ������

	JmpCmd::execute(jmpCmd, processor);
}
