#include "sched_rr2.h"

using namespace std;

struct operation {
	int operator()(std::queue<int> &e1, std::list<int> &e2){
		return e1.size() + e2.size();
	}
} add;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	for (int i = 0; i < argn[1]; i++) {
		std::list<pid> l;
		std::queue<pid> q;

		process.push_back(q);
		blocked.push_back(l);
		active.push_back(0);

		quantum.push_back(argn[i + 2]);
		core.push_back(argn[i + 2]);
	}
}

SchedRR2::~SchedRR2() {

}

void SchedRR2::load(int pid) {
	/**
	 * Busco el proceso que tiene menor cantidad de activo totales,
	 * la suma la obtiene de RUNNING + BLOCKED + READY
	 */
	std::vector<int> candidate(blocked.size(), 0);
	transform(process.begin(), process.end(), blocked.begin(), candidate.begin(), add);
	transform(candidate.begin(), candidate.end(), active.begin(), candidate.begin(), std::plus<int>());
	
	/**
	* Hasta aca tenemos la suma de las 3 colas. Ahora buscamos el minimo usando std de c.
	* Primero calculamos el iterador que apunta al minimo y luego calculamos el indice del minimo
	* calculando la distancia entre el inicio del vector y el iterador. 
	*/
	std::vector<int>::iterator minium = std::min_element(candidate.begin(), candidate.end());
	int cpu = std::distance(candidate.begin(), minium);

	process[cpu].push(pid);
}

void SchedRR2::unblock(int pid) {
	std::list<int>::iterator it;
	/**
	 * Busco el pid en la cola que se encuentra bloqueado
	 * y lo migro hacia los que estan para ser ejecutados
	 */
	for(unsigned int cpu = 0; cpu < blocked.size(); cpu ++){
		it = find(blocked[cpu].begin(), blocked[cpu].end(), pid);
		if(it != blocked[cpu].end()){
			blocked[cpu].remove(pid);
			process[cpu].push(pid);
			return;
		}
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	/**
	 * Si el proceso ha finalizado, verifica si en
	 * la cola de procesos restantes hay otra tarea
	 * a ejecutar, si no hay otra, retorna la tarea
	 * IDLE
	 */
	if (m == EXIT) {
		if (process[cpu].empty()) {
			active[cpu] = IDLE;
			return IDLE_TASK;
		} 
		
		active[cpu] = BUSY;
		reset(cpu);
		return next(cpu);
	}

	/**
	 * Cuando se produce un TICK, puede ser
	 * porque el IDLE se esta ejecutando o
	 * se esta ejecutando un proceso.
	 *
	 * Si proceso proceso es de tipo IDLE
	 * verifica si hay otro proceso enconlado
	 * sino, sigue ejecutando IDLE.
	 *
	 * En caso que sea otro proceso, verifica
	 * si tiene quantum para seguir ejecutandose
	 * en caso que no lo tenga, verifica si hay
	 * otro proceso pendiente a ser ejecutado, de
	 * ser asi, se cambia de proceso, sino, se sigue
	 * ejecutando por un quantum mas.
	 *
	 */
	if (m == TICK) {
		if (current_pid(cpu) == IDLE_TASK) {
			if (process[cpu].empty()) {
				active[cpu] = IDLE;
				return IDLE_TASK;
			} 			
			active[cpu] = BUSY;
			reset(cpu);
			return next(cpu);
		}

		if (core[cpu] == 0) {
			if (process[cpu].empty()) {
				active[cpu] = BUSY;
				reset(cpu);
				return current_pid(cpu);
			}

			active[cpu] = BUSY;
			process[cpu].push(current_pid(cpu));
			reset(cpu);
			return next(cpu);
		} 
		
		active[cpu] = BUSY;
		core[cpu]--;
		return current_pid(cpu);
	}

	if (m == BLOCK) {
		blocked[cpu].push_back(current_pid(cpu));
		if (process[cpu].empty()) {
			active[cpu] = IDLE;
			return IDLE_TASK;
		} 
		
		active[cpu] = BUSY;
		reset(cpu);
		return next(cpu);
	}
	return IDLE_TASK;
}

int SchedRR2::next(int cpu) {
	int next_pid = process[cpu].front();
	process[cpu].pop();
	return next_pid;
}

void SchedRR2::reset(int cpu) {
	core[cpu] = quantum[cpu];
}