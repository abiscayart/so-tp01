#include "tasks.h"

#define CPU_TASK 1
#define IO_TASK 0

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

// Ej1.
void TaskConsola(int pid, vector<int> params){
	// cantidad de llamadas bloqueantes
	int n = params[0];
	// duracion minima de la llamada
	int bmin = params[1];
	//duracion maxima de la llamada
	int bmax = params[2];
	// numero aleatorio entre [bmin, bmax]
	int diff = bmax - bmin;
	srand(time(NULL));
	
	//se realizan las n llamadas bloqueantes al sistema
		int rnumber = 0;
	for (int i = 0; i < n; ++i) {
		rnumber  = diff != 0 ? (rand() % diff) : 0;
		rnumber += bmin;
		uso_IO(pid, rnumber);
	}
}


// Ej3. (No sé si entendí bien la aclaración entre () de los tiempos. Revisar.)
void TaskBatch(int pid, vector<int> params) { // params: total_cpu, cant_bloqueos

	// tiempo de cpu total que utilice la tarea
	int total_cpu = params[0];
	// cantidad llamadas bloqueantes al sistema
	int cant_bloqueos = params[1];
	/**
	 * Generamos un vector con la cantidad de ciclos que va a
	 * tener el tiempo de CPU utilizado, guardando el flag CPU_TASK para indicar que el sistema debera
	 * ejecutar un ciclo de CPU.
	 */
	std::vector<int> ciclos(total_cpu, CPU_TASK);
	/**
	 * A las primeras cant_bloqueos posiciones las pisamos con el flag IO_TASK para indicar que se debe
	 * realizar una llamada bloqueante.
	 */
	std::fill(ciclos.begin(), ciclos.begin() + cant_bloqueos, IO_TASK);
	
	// Mezclamos el vector para que las llamadas sean aleatoreas.
	srand(time(NULL) * pid);
	std::random_shuffle(ciclos.begin(), ciclos.end());
	
	/**
	 * Recorremos el vector y vamos realizando la llamda que corresponda según su flag.
	 */
	for (int i = 0; i < total_cpu; i++) {
		if (ciclos[i] == CPU_TASK){
			uso_CPU(pid, 1);
		} else {
			//TODO: ver si solo esta llamada tiene que tardar 2 ciclos.
			uso_IO(pid, 2);
		}
	}

}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
