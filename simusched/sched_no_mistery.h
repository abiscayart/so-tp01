#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

typedef int pid;

typedef int cpu;

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

  private:

    /*std::vector<std::queue<int> > vq;
    std::vector<int> def_quantum;
    std::vector<int> unblock_to;
    int quantum, n, cur_pri;*/


    /**
     * Vector de Colas para todos los procesos que van llegando
     * al scheduler, es una unico vector para
     * todos los proceso. Cada process[i] representa el nivel
     * de quantum en el que ejecutaran las tareas encoladas.
     */
     std::vector< std::queue<pid> >process;
    /**
     * Vector de Quantums pasados por parametro.
     */
    std::vector<cpu> quantum;
    /**diccionario que vincula un proceso con su quantum
     * QuantumTarea[pid] devuelve la posicion en el vector
     * quantum[] para la tarea pid.
     */
    std::map<int,unsigned int> QuantumTarea;
    //
    int QuantumActual;
    /**
     * Retorna el proximo proceso de la cola, requiere
     * que la cola no se encuentre vacia.
     */

    int next(void);
};

#endif
