 #include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::Build() const
{
	PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
	SetUserAction(generator);

    RunAction *runAction = new RunAction();
    SetUserAction (runAction);

    EventAction *eventAction = new EventAction(runAction);
    SetUserAction (eventAction);

    SteppingAction *steppingAction = new SteppingAction(eventAction);
    SetUserAction (steppingAction);
}