#include <vector>
#include <queue>
#include <map>
#include "sched_no_mistery.h"
#include "basesched.h"

using namespace std;

// Ej7. - primera parte
SchedNoMistery::SchedNoMistery(vector<int> argn) {
  // recibe los quantums por parámetro
	for (unsigned int i = 0; i < argn.size(); i++) {
		quantums.push_back(argn[i]-1);
		queue<pid> entrada;
		procesos.push_back(entrada);
	}
}

/** El proceso que llega empezara a ejecutar en el primer nivel.*/ 
void SchedNoMistery::load(int pid) {
	quantum_tarea.insert(std::pair<int,int>(pid,0));
	procesos[0].push(pid);
}

void SchedNoMistery::unblock(int pid) {
	procesos[quantum_tarea[pid]].push(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	/**
	 * Si el proseso termino entonces buscamos el siguiente.
	 */ 
	if (m == EXIT) {
		return next();
	}

	/**
	 * Si el proseso es IDLE, seguimos buscando. Si se termino el quantum
	 * de la tarea actual, se sube el nivel de la tarea actual (si no esta
	 * en el ultimo nivel) y se vuelve a encolar en el nivel correspondiente
	 * y se busca el siguiente. Sino se resta en 1 el quantum.
	 */
	 if (m == TICK) {
		if (current_pid(cpu) == IDLE_TASK) {
			return next();

		}

		//chequeo si termino el quantum actual
		if (current_quantum == 0) {
			int cpid = current_pid(cpu);
			if (quantum_tarea[cpid] < (quantums.size() - 1)) {
				quantum_tarea[cpid]++;
			}
				
			procesos[quantum_tarea[cpid]].push(cpid);
			return next();
		} else {
			current_quantum--;
			return current_pid(cpu);
		}
		
	}
	
	/**
	 * Si el proceso se bloquea, se le baja un nivel de quantum y se busca el siguiente.
	 */

	if (m == BLOCK) {
		int cpid = current_pid(cpu);
		if (quantum_tarea[cpid] > 0) {
			quantum_tarea[cpid]--;
		}
		return next();
	}
		
	return IDLE_TASK;
}

/**
 * Buscamos recorremos procesos desde el primer nivel, fijandonos si hay
 * algun proceso encolado, de ser asi, ese sera el proseso a ejecutar.
 * Sino se busca en el siguiente nivel. 
 * Si recorrimos todos los niveles y no hay ningun proceso encolado 
 * devolvemos IDLE. Si no devolvemos IDLE => current_quantum sera la cantidad
 * del nivel actual.
 */

int SchedNoMistery::next(void) {
	int next_pid = IDLE_TASK;
	
	for(unsigned int i = 0; i < quantums.size(); i++) {
		if(procesos[i].empty())
			continue;
			
		next_pid = procesos[i].front();
		procesos[i].pop();
		break;
	}
	
	if(next_pid != IDLE_TASK)
		current_quantum = quantums[quantum_tarea[next_pid]];
	
	return next_pid;
}
