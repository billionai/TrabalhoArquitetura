#include "regResultController.h"

std::vector<std::string> regs = {"F0", "F1", "F2", "F3", "F4", "F5", "F6"};

using namespace std;
RegResController::RegResController(tableManager<string>& tm):
	gui(tm){
    for(size_t i = 0; i < regs.size(); i++){
        registers[regs[i]] = "NULL"; // registers available have a NULL string
        registers_next[regs[i]] = "NULL"; // used to prevent early write
    }
    return;
}

bool RegResController::isRegAvailable(string regName) {
    string r = registers[regName];
    if(r.compare("NULL") == 0) return 1;
    else return 0;    
}

string RegResController::getRegister(string regName){
    return registers[regName];
}

void RegResController::populateReg(string regName, string fuName){
	registers_next[regName] = fuName;
	return;
}

void RegResController::clearReg(string regName){
	registers_next[regName] = "NULL";
	return;
}

void RegResController::update_table(){
	vector<string> data;
	for(auto it = registers.begin(); it != registers.end(); it++){
		if(it->second != "NULL")
			data.push_back(it->second);
		else
			data.push_back(" ");
	}
	gui.update_line(0,"FU",data);
}

void RegResController::performClockTick(){
	
	for(auto& reg : registers){
		reg.second = registers_next[reg.first];
	}
	update_table();
}
