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
 * Defino tipo de dato PID. Representa el pid
 * que viene como numero entero.
 */
typedef int pid;
/**
 * Defino tipo de dato CPU. Representa el core
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
		 * Unica cola global para todos los procesos que llegan al scheduler.
		 */
		std::vector<std::queue<pid> > procesos;
		/*
		 * Vector que contiene los procesos que se encuentran bloqueados por llamadas I/O.
		 */
		std::vector<std::list<pid> > bloqueados;

		/**
		 * Este vector contiene los quantums que tiene el scheduler para cada uno
		 * de sus procesadores, el indice representa el numero
		 * de procesador.
		 */
		std::vector<cpu> quantums;
		/**
		 * En ente vector se almacena el quantum restante que tienen cada
		 * uno de los procesadores, el indice representa el numero
		 * de procesador con indice en 0.
		 */
		std::vector<cpu> nucleos;
		/**
		 * Representa si el procesador se encuentra con
		 * un proceso activo. Si el valor es 1 para proceso activo,0 para idle
		 */
		std::vector<cpu> activo;

		int next(int cpu);
		/**
		 * Restablece los valores del quantum para un
		 * determinado CPU.
		 */
		void reset(int cpu);
};

#endif
