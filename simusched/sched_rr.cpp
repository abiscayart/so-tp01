#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

// Ej4.
SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	for (int i = 0; i < argn[1]; i++) {
		quantum.push_back(argn[i+2]);
		core.push_back(argn[i+2]);
	}
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	process.push(pid);
}

void SchedRR::unblock(int pid) {
	process.push(pid);
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	/**
	 * Si el proceso ha finalizado, verifica si en
	 * la cola de procesos restantes hay otra tarea
	 * a ejecutar, si no hay otra, retorna la tarea
	 * IDLE
	 */
	if (m == EXIT) {
		if (process.empty()) {
			return IDLE_TASK;
		} else {
			reset(cpu);
			return next(cpu);
		}
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
			if (process.empty()) {
				return IDLE_TASK;
			} else {
				reset(cpu);
				return next(cpu);
			}
		} else {
			if (core[cpu] == 0) {
				if (process.empty()) {
					reset(cpu);
					return current_pid(cpu);
				} else {
					process.push(current_pid(cpu));
					reset(cpu);
					return next(cpu);
				}
			} else {
				core[cpu]--;
				return current_pid(cpu);
			}
		}
	}

	if (m == BLOCK) {
		if (process.empty()) {
			return IDLE_TASK;
		} else {
			reset(cpu);
			return next(cpu);
		}
	}
	return IDLE_TASK;
}

int SchedRR::next(int cpu) {
	int next_pid = process.front();
	process.pop();
	return next_pid;;
}

void SchedRR::reset(int cpu) {
	core[cpu] = quantum[cpu];
}
