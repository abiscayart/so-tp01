.PHONY += ejercicio01

ejercicio1: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 1...'
	@echo -e '\033[0m'
	simusched ej1/tasks_ej1.tsk 1 1 1 SchedFCFS | graphsched.py > ej1/images/tasks_ej1.png	
