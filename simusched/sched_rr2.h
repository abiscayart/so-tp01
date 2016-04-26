#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include "basesched.h"

/**
 * Indica que el core se encuentra con una
 * tarea en estado RUNNING.
 */
#define BUSY 1
/**
 * Indica que el core no se encuentra con una
 * tarea en estado RUNNING
 */
#define IDLE 0

using namespace std;

/**
 * Defino tipo de dato PID.
 * Solo agrega mas legibilidad
 * al codigo. Representa el pid
 * que viene como numero entero.
 */
typedef int pid;
/**
 * Defino tipo de dato CPU.
 * Solo agrega mas legibilidad
 * al codigo. Representa el core
 * den una cpu.
 */
typedef int cpu;

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		/**
		 * Cola para todos los procesos que van llegando
		 * al scheduler, es una unica cola en comun para
		 * todos los proceso.
		 */
		std::vector<std::queue<pid> > process;
		/*
		 * Contiene los procesos que se encuentran bloqueados
		 * por llamadas I/O.
		 */
		std::vector<std::list<pid> > blocked;

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
		 * Representa si el procesador se encuentra con
		 * un proceso activo. Si el valor es 1, indica
		 * que el cpu esta con un proceso activo, si el
		 * valor es 0 representa que el proceso esta
		 * ejecutando idle
		 */
		std::vector<cpu> active;
		/**
		 * Sin implementacion.
		 */
		int next(int cpu);
		/**
		 * Restablece los valores del quantum para un
		 * determinado CPU.
		 */
		void reset(int cpu);
};

#endif
