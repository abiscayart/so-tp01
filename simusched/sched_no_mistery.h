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


    /**
     * Única Cola global para todos los procesos que van llegando al scheduler. 
     * Cada procesos[i] representa el nivel de quantum en el que ejecutaran las tareas encoladas.
     */
     std::vector< std::queue<pid> >procesos;
    /**
     * quantums pasados por parametro.
     */
    std::vector<cpu> quantums;

    /**
     * Mapa que vincula un proceso con su quantum
     * quatum_tarea[pid] devuelve la posicion en el vector quantums[] para la tarea pid.
     */
    std::map<int,unsigned int> quantum_tarea;
    
    int current_quantum;
    /**
     * Retorna el proximo proceso de la cola, requiere
     * que la cola no se encuentre vacia.
     */

    int next(void);
};

#endif
