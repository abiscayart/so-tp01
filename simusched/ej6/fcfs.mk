.PHONY += ejercicio6

ejercicio6: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 6...'
	@echo -e '\033[0m'
	simusched ej6/task_ej6.tsk 1 2 1 SchedFCFS 1 2 0 | graphsched.py  >  ej6/images/ej6_01.png
