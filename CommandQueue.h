#pragma once
#include "pch.h"
#include <queue>
class CommandQueue
{
public:
	void		Push(const Command& cmd);
	Command		Pop();
	bool		IsEmpty()const;

private:
	std::queue<Command> m_Queue;
};