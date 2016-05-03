.PHONY += ejercicio5

ejercicio5: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 5...'
	@echo -e '\033[0m'
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 2  | graphsched.py  >  ej5/images/rr_000.png
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 10 | graphsched.py  >  ej5/images/rr_001.png
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 30 | graphsched.py  >  ej5/images/rr_002.png
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 2  > ej5/output/rr_010.out 
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 10 > ej5/output/rr_011.out
	simusched ej5/task_ej5.tsk 1 2 1 SchedRR 1 30 > ej5/output/rr_012.out
