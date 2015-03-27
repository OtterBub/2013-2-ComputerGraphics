#ifndef __STATE_H__
#define __STATE_H__

template<class entity_type>
class State{
public:
	virtual ~State() {}

	virtual void Enter(entity_type*) = 0;
	virtual void Execute(entity_type*) = 0;
	virtual void Exit(entity_type*) = 0;
};

#endif //__STATE_H__