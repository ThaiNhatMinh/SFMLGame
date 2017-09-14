#include "pch.h"
#include "CommandQueue.h"

void CommandQueue::Push(const Command & cmd)
{
	m_Queue.push(cmd);
}

Command CommandQueue::Pop()
{
	Command cmd = m_Queue.front();
	m_Queue.pop();
	return cmd;
}

bool CommandQueue::IsEmpty() const
{
	return m_Queue.empty();
}
