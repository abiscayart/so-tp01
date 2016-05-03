#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include "basesched.h"

using namespace std;

// defino tipos para leer mejor el codigo
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
		 * Unica cola global para todos los procesos que llegan al scheduler.
		 */
		std::queue<pid> procesos;
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
		 * Retorna el proximo proceso de la cola, requiere que la cola no se encuentre vacia.
		 */
		int next(int cpu);
		/**
		 * Restablece los valores del quantum para un determinado CPU.
		 */
		void reset(int cpu);
};

#endif
