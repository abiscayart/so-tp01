#include <vector>
#include <queue>
#include <map>
#include "sched_no_mistery.h"
#include "basesched.h"

using namespace std;

// Ej7. - primera parte
SchedNoMistery::SchedNoMistery(vector<int> argn) {
  // MFQ recibe los quantums por parÃ¡metro
	for (unsigned int i = 0; i < argn.size(); i++) {
		quantum.push_back(argn[i]-1);
		queue<pid> entrada;
		process.push_back(entrada);
	}
}

/** El proceso que llega empezara a ejecutar en el primer nivel.*/ 
void SchedNoMistery::load(int pid) {
	QuantumTarea.insert(std::pair<int,int>(pid,0));
	process[0].push(pid);
}

void SchedNoMistery::unblock(int pid) {
	process[QuantumTarea[pid]].push(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	/**
	 * El proseso termino => buscamos el siguiente.
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

		} else {
			if (QuantumActual == 0) { // termino su quantum
				int cpid=current_pid(cpu);
					if(QuantumTarea[cpid] < (quantum.size() - 1))
						QuantumTarea[cpid]++;
						
					process[QuantumTarea[cpid]].push(cpid);
					return next();
			} else {
				QuantumActual--;
				return current_pid(cpu);
			}
		}
	}
	
	/**
	 * Si el proceso se bloquea, =>  se le baja un nivel de quantum y 
	 * se busca el siguiente.
	 */

	if (m == BLOCK) {
			int cpid=current_pid(cpu);
			if(QuantumTarea[cpid] > 0)
				QuantumTarea[cpid]--;
			return next();
		}
		
	return IDLE_TASK;
}

/**
 * Buscamos recorremos process desde el primer nivel, fijandonos si hay
 * algun proceso encolado, de ser asi, ese sera el proseso a ejecutar.
 * Sino se busca en el siguiente nivel. 
 * Si recorrimos todos los niveles y no hay ningun proceso encolado 
 * devolvemos IDLE. Si no devolvemos IDLE => QuantumActual sera la cantidad
 * del nivel actual.
 */

int SchedNoMistery::next(void) {
	int next_pid=IDLE_TASK;
	
	for(unsigned int i=0; i<quantum.size(); i++) {
		if(process[i].empty())
			continue;
			
		next_pid=process[i].front();
		process[i].pop();
		break;
	}
	
	if(next_pid!=IDLE_TASK)
		QuantumActual=quantum[QuantumTarea[next_pid]];
	
	return next_pid;
}
