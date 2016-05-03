#include "sched_rr2.h"

using namespace std;

struct operation {
	int operator()(std::queue<int> &e1, std::list<int> &e2){
		return e1.size() + e2.size();
	}
} add;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de nucleos y sus cpu_quantum por parámetro
	for (int i = 0; i < argn[1]; i++) {
		std::list<pid> l;
		std::queue<pid> q;

		procesos.push_back(q);
		bloqueados.push_back(l);
		activo.push_back(0);

		quantums.push_back(argn[i + 2]);
		nucleos.push_back(argn[i + 2]);
	}
}

SchedRR2::~SchedRR2() {

}

void SchedRR2::load(int pid) {
	/**
	 * Busco el proceso que tiene menor cantidad de activo totales (RUNNING + bloqueados + READY)
	 */
	std::vector<int> candidate(bloqueados.size(), 0);
	transform(procesos.begin(), procesos.end(), bloqueados.begin(), candidate.begin(), add);
	transform(candidate.begin(), candidate.end(), activo.begin(), candidate.begin(), std::plus<int>());
	
	/**
	* Hasta aca tenemos la suma de las 3 colas, ahora buscamos el minimo usando std de c.
	* Primero calculamos el iterador que apunta al minimo y luego calculamos el indice del minimo
	* calculando la distancia entre el inicio del vector y el iterador. 
	*/
	std::vector<int>::iterator minium = std::min_element(candidate.begin(), candidate.end());
	int cpu = std::distance(candidate.begin(), minium);

	procesos[cpu].push(pid);
}

void SchedRR2::unblock(int pid) {
	std::list<int>::iterator it;
	/**
	 * Busco el pid en la cola de bloqueados y lo muevo hacia los que estan para ser ejecutados
	 */
	for(unsigned int cpu = 0; cpu < bloqueados.size(); cpu ++){
		it = find(bloqueados[cpu].begin(), bloqueados[cpu].end(), pid);
		if(it != bloqueados[cpu].end()){
			bloqueados[cpu].remove(pid);
			procesos[cpu].push(pid);
			return;
		}
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	/**
	 * Si el proceso ha finalizado, verifica si
	 * la cola de procesos restantes está vacía. Si lo está, retorna la tarea
	 * IDLE. Si no, retorna la próxima a ejecutar.
	 */
	if (m == EXIT) {
		if (procesos[cpu].empty()) {
			activo[cpu] = IDLE;
			return IDLE_TASK;
		} 
		
		activo[cpu] = BUSY;
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
			if (procesos[cpu].empty()) {
				activo[cpu] = IDLE;
				return IDLE_TASK;
			} 			
			activo[cpu] = BUSY;
			reset(cpu);
			return next(cpu);
		}

		if (nucleos[cpu] == 0) {
			if (procesos[cpu].empty()) {
				activo[cpu] = BUSY;
				reset(cpu);
				return current_pid(cpu);
			}

			activo[cpu] = BUSY;
			procesos[cpu].push(current_pid(cpu));
			reset(cpu);
			return next(cpu);
		} 
		
		activo[cpu] = BUSY;
		nucleos[cpu]--;
		return current_pid(cpu);
	}

	if (m == BLOCK) {
		bloqueados[cpu].push_back(current_pid(cpu));
		if (procesos[cpu].empty()) {
			activo[cpu] = IDLE;
			return IDLE_TASK;
		} 
		
		activo[cpu] = BUSY;
		reset(cpu);
		return next(cpu);
	}
	return IDLE_TASK;
}

int SchedRR2::next(int cpu) {
	int next_pid = procesos[cpu].front();
	procesos[cpu].pop();
	return next_pid;
}

void SchedRR2::reset(int cpu) {
	nucleos[cpu] = quantums[cpu];
}