
#include "sched_rr.h"


using namespace std;

// Ej4.
SchedRR::SchedRR(vector<int> argn) {
	// Recibe la cantidad de nucleos y  los valores de sus respectivos quantums
	for (int i = 0; i < argn[1]; i++) {
		quantums.push_back(argn[i+2]);
		nucleos.push_back(argn[i+2]);
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	procesos.push(pid);
}

void SchedRR::unblock(int pid) {
	procesos.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	/**
	 * Si el proceso ha finalizado, verifica si
	 * la cola de procesos restantes está vacía. Si lo está, retorna la tarea
	 * IDLE. Si no, retorna la próxima a ejecutar.
	 */
	if (m == EXIT) {
		if (procesos.empty()) {
			return IDLE_TASK;
		} 
		
		reset(cpu);
		return next(cpu);
	}

	/**
	 * Cuando se produce un TICK, puede ser porque se está ejecutando un proceso o se está ejecutando 
	 * la tarea IDLE.
	 *
	 * Si proceso es de tipo IDLE verifica si hay otro proceso encolado y si no 
	 * lo encuentra sigue ejecutando IDLE.
	 *
	 * En caso que encuentre otro proceso, verifica si tiene quantum para seguir ejecutandose.
	 * En caso que no lo tenga, verifica si hay otro proceso pendiente a ser ejecutado, de
	 * ser asi, se cambia de proceso, sino, se sigue
	 * ejecutando por un quantum mas.
	 *
	 */
	if (m == TICK) {
		if (current_pid(cpu) == IDLE_TASK) {
			if (procesos.empty()) {
				return IDLE_TASK;
			}
			reset(cpu);
			return next(cpu);
		} 

		if (nucleos[cpu] == 0) {
			if (procesos.empty()) {
				reset(cpu);
				return current_pid(cpu);
			} 
			
			procesos.push(current_pid(cpu));
			reset(cpu);
			return next(cpu);	
		}
			
		nucleos[cpu]--;
		return current_pid(cpu);
	}

	if (m == BLOCK) {
		if (procesos.empty()) {
			return IDLE_TASK;
		} 
		reset(cpu);
		return next(cpu);
	}
	return IDLE_TASK;
}

int SchedRR::next(int cpu) {
	int next_pid = procesos.front();
	procesos.pop();
	return next_pid;;
}

void SchedRR::reset(int cpu) {
	nucleos[cpu] = quantums[cpu];
}
