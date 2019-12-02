#include "dispatchController.h"
#include <fstream>
#include <iostream>

using namespace std;

DispatchController::DispatchController(PipelineController& pc, UfController& uc, RegResController& rrc):
	pipe(pc),
	ufCon(uc),
	regCon(rrc){
	this->loadInstructions();
}
	
void DispatchController::loadInstructions(){

	string value1, value2, value3, value4;
	ifstream inputFile("instructions.sbd");
	
	vector< unordered_map<string, string> > instructionsMaps;
	instructionsMaps = createInstructionsMaps();
	int instructionCounter = 0;
	//reading instruction line
	while(inputFile >> value1 >> value2 >> value3 >> value4){
		
		instruction newInstruction;
		newInstruction.id = instructionCounter++;
		
		//will see if intruction name is mapped
		//r-type integer operation
		if( instructionsMaps[0].find(value1) != instructionsMaps[0].end()){
			newInstruction.opName = instructionsMaps[0].find(value1)->second;
			newInstruction.isRtype = true;
			newInstruction.useFp = false;
		}
		//r-type floating point operation
		else if( instructionsMaps[1].find(value1) != instructionsMaps[1].end()){
			newInstruction.opName = instructionsMaps[1].find(value1)->second;
			newInstruction.isRtype = true;
			newInstruction.useFp = true;
		}
		//i-type integer operation
		else if( instructionsMaps[2].find(value1) != instructionsMaps[2].end()){
			newInstruction.opName = instructionsMaps[2].find(value1)->second;
			newInstruction.isRtype = false;
			newInstruction.useFp = false;
		}//else invalid instruction.. TODO
		
		//rs rt rd or imm
		newInstruction.rs = value2;
		newInstruction.rt = value3;
		if(newInstruction.isRtype)
			newInstruction.rd = value4;
		else
			newInstruction.immed = stoi(value4);
		
		//add to queue
		instructionQueue.push(newInstruction);
	}
}

int DispatchController::tryToDispatchNext(UfController ufCon, PipelineController pipe, RegResController regCon, int clockCycle){
	
	instruction nextInstruction = instructionQueue.front();
	instructionQueue.pop();
	
	//check if destiny register is free
	if( regCon.isRegAvailable(nextInstruction.rd) ){
		//checking if a compatible fu is available
		//
		
		ufLine ufReturned = ufCon.hasUfAvailable(nextInstruction.useFp);
		if( ufReturned != NULL) {//uf was found
			//then will populate uf and register status
			ufCon.populateUf(ufReturned, nextInstruction, regCon);
			regCon.populateReg(nextInstruction.rd, fuName);

			//finally, send dispatched instruction to the pipeline
			pipe.dispatchInstruction(nextInstruction.id, nextInstruction.opName, clockCycle);
			
			return nextInstruction.id;
		}
	}
	return -1;
}

vector<unordered_map<string, string>> DispatchController::createInstructionsMaps(){
	
	vector< unordered_map<string, string> > instructionsMaps;
	unordered_map<string, string> rTypeInt, rTypeFp, iType;
	
	rTypeInt["ADD"] = "Add";
	rTypeInt["SUB"] = "Sub";
	rTypeInt["MUL"] = "Mult";
	rTypeInt["DIV"] = "Div";

	rTypeFp["ADD.D"] = "Add";
	rTypeFp["SUB.D"] = "Sub";
	rTypeFp["MUL.D"] = "Mult";
	rTypeFp["DIV.D"] = "Div";
	
	iType["LW"] = "Load";
	iType["SW"] = "Store";
	iType["ADDI"] = "Add";
	iType["SUBI"] = "Sub";

	instructionsMaps.push_back(rTypeInt);
	instructionsMaps.push_back(rTypeFp);
	instructionsMaps.push_back(iType);

	return instructionsMaps;
}




