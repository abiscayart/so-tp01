#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include "basesched.h"

using namespace std;

typedef int pid;

typedef int cpu;

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		/**
		 * Cola para todos los procesos que van llegando
		 * al scheduler, es una unica cola en comun para
		 * todos los proceso.
		 */
		std::queue<pid> process;
		/**
		 * Quantum que tiene el scheduler para cada uno
		 * de los procesadores que tiene el sistema, el
		 * indice del operador [] representa el numero
		 * de procesador con indice en 0.
		 */
		std::vector<cpu> quantum;
		/**
		 * Representa el quantum restante que tiene cada
		 * uno de los procesadores que tiene el sistema,
		 * el indice del operador [] representa el numero
		 * de procesador con indice en 0.
		 */
		std::vector<cpu> core;
		/**
		 * Retorna el proximo proceso de la cola, requiere
		 * que la cola no se encuentre vacia.
		 */
		int next(int cpu);
		/**
		 * Restablece los valores del quantum para un
		 * determinado CPU.
		 */
		void reset(int cpu);
};

#endif
