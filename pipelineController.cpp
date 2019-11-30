#include "pipelineController.h"
#include <iostream>

using namespace std;

PipelineController::PipelineController(){


}

//adds new line of intruction
void PipelineController::dispatchInstruction(int instructionId, std::string opName, int clockCycle){

	cout << "dispatchInstruction"<< endl;
}

//calls ufController method to read operands. Updates pipeline and window?
void PipelineController::tryToReadOperands(UfController ufCon, pipeLine line, int clockCycle){
	cout << "tryToReadOperands" <<endl;
}

//calls ufController method to run execution. Updates pipeline and window
void PipelineController::runExecution(UfController ufCon, pipeLine line, int clockCycle){
	
	cout << "runExecution" << endl;
}

//calls ufController method to check if write is available and if it is
//will update pipeline and call register result method to update register 
void PipelineController::tryToWriteResult(RegResController regCon, pipeLine line, int clockCycle){
	cout << "tryToWriteResult" << endl;
}

//will try to perform next stage for every instruction in the pipeline
void PipelineController::performClockCicle(UfController ufCon, RegResController regCon){
	cout << "performClockCicle" << endl;
}
