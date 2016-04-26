#include "tasks.h"

#define MUST_EXECUTE_CPU 1
#define MUST_EXECUTE_IO 0

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
	/**
	 * Cantidad de llamadas bloqueantes
	 */
	int n = params[0];
	/**
	 * Duracion minima
	 */
	int bmin = params[1];
	/**
	 * Duracion maxima
	 */
	int bmax = params[2];
	/**
	 * Genero el numero aleatorio entre [bmin, bmax]
	 */
	int diff = bmax - bmin;
	srand(time(NULL));
	/**
	 * Genero los n bloqueos en el sistema
	 */
	int rnumber = 0;
	for (int i = 0; i < n; ++i) {
		rnumber  = diff != 0 ? (rand() % diff) : 0;
		rnumber += bmin;
		uso_IO(pid, rnumber);
	}
}


// Ej3. (No entiendo bien la aclaración entre () de los tiempos. Revisar.)
void TaskBatch(int pid, vector<int> params) { // params: total_cpu, cant_bloqueos
	/**
	 * Guardo los parametros de entrada que vienen desde la
	 * consola, los definimos como total_cpu que representa
	 * la cantidad de ciclos de CPU a ejecutar y cant_bloqueos
	 * que representa la cantidad de bloqueos que va a tener
	 * el sistema.
	 */
	int total_cpu = params[0];
	int cant_bloqueos = params[1];
	/**
	 * Generamos un vector con la cantidad de ciclos que va a
	 * tener la CPU, todas las posiciones son rellenadas con
	 * el flag MUST_EXECUTE_CPU. Es decir, en donde el valor
	 * del vector es MUST_EXECUTE_CPU, el sistema debera
	 * ejecutar un ciclo de CPU.
	 */
	std::vector<int> ciclos(total_cpu, MUST_EXECUTE_CPU);
	/**
	 * Ahora llenamos las primeras #cant_bloqueos posiciones
	 * con el flag MUST_EXECUTE_IO. Es decir, en donde el valor
	 * del vector sea MUST_EXECUTE_IO, debe ejecutar 1 ciclo
	 * de I/O
	 */
	std::fill(ciclos.begin(), ciclos.begin() + cant_bloqueos, MUST_EXECUTE_IO);
	/**
	 * Hasta este punto realiza a medias lo solcitado por el
	 * enunciado, ya que siempre van a ser las primeras llamadas
	 * las bloqueantes y necesitamos que sean pseudo-aleatorio.
	 */
	srand(time(NULL) * pid);
	std::random_shuffle(ciclos.begin(), ciclos.end()); //, random);
	/**
	 * Recorremos el vector y vamos haciendo una a una la ejecucion
	 */
	for (int i = 0; i < total_cpu; i++) {
		if (ciclos[i] == MUST_EXECUTE_CPU){
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
