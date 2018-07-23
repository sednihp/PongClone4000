#include "StateMachine.h"
#include "Engine.h"

StateMachine::StateMachine(Engine* owner) :	mOwner(owner),
											mCurrentState(nullptr)
{
}

StateMachine::~StateMachine()
{
	
}

//if we try to change to the same state, return immediately
//otherwise exit out of the current state, assign newState to currentState and enter the new state
void StateMachine::changeState(std::shared_ptr<State> newState)
{
	if(typeid(*mCurrentState) == typeid(*newState))
	{
		return;
	}

	mCurrentState->exit(mOwner);

	mCurrentState = newState;

	mCurrentState->enter(mOwner);
}