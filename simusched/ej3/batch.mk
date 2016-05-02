.PHONY += ejercicio3

ejercicio3: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 3...'
	@echo -e '\033[0m'
	simusched ej3/task_ej3.tsk 1 1 1 SchedFCFS   >  ej3/output/task_ej3.out
	cat ej3/output/task_ej3.out | graphsched.py  >  ej3/images/task_ej3.png
	cat ej3/output/task_ej3.out | graph_cores.py  >  /dev/null 2>&1
	mv out_cores_timeline.png ej3/images/task_ej3_core.png
