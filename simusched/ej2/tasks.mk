.PHONY += ejercicio02

ejercicio2: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 2...'
	@echo -e '\033[0m'
	
	#un nucleo
	simusched ej2/tasks_ej2.tsk 1 5 1 SchedFCFS > ej2/output/tasks_ej2_1nucleo.out 
	cat ej2/output/tasks_ej2_1nucleo.out | graphsched.py   > ej2/images/tasks_001.png
	cat ej2/output/tasks_ej2_1nucleo.out | graph_cores.py  >  /dev/null 2>&1
	mv out_cores_timeline.png ej2/images/tasks_002.png
	
	#dos nuecleos
	simusched ej2/tasks_ej2.tsk 2 5 1 SchedFCFS > ej2/output/tasks_ej2_2nucleos.out 
	cat ej2/output/tasks_ej2_2nucleos.out | graphsched.py  > ej2/images/tasks_011.png
	cat ej2/output/tasks_ej2_2nucleos.out | graph_cores.py >  /dev/null 2>&1
	mv out_cores_timeline.png ej2/images/tasks_012.png
	
	#4 nucleos
	simusched ej2/tasks_ej2.tsk 4 5 1 SchedFCFS > ej2/output/tasks_ej2_4nucleos.out 
	cat ej2/output/tasks_ej2_4nucleos.out | graphsched.py  > ej2/images/tasks_021.png
	cat ej2/output/tasks_ej2_4nucleos.out | graph_cores.py >  /dev/null 2>&1
	mv out_cores_timeline.png ej2/images/tasks_022.png
	

