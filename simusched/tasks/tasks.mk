.PHONY += ejercicio01,ejercicio02

ejercicio1: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 01'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched tasks/tasks_001.tsk 1 1 1 SchedFCFS | graphsched.py > tasks/images/tasks_000.png	
ejercicio2: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 02'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	
	simusched tasks/tasks_002.tsk 1 5 1 SchedFCFS > tasks/output/tasks_002.out 
	cat tasks/output/tasks_002.out | graphsched.py   > tasks/images/tasks_001.png
	cat tasks/output/tasks_002.out | graph_cores.py  >  /dev/null 2>&1
	mv out_cores_timeline.png tasks/images/tasks_002.png
	cat tasks/output/tasks_002.out | event_parser.py >  /dev/null 2>&1
	mv out_cores_resume.png  tasks/images/tasks_003.png
	mv out_pids_resume.png   tasks/images/tasks_004.png
	mv out_pids_timeline.png tasks/images/tasks_005.png
	
	simusched tasks/tasks_002.tsk 2 5 1 SchedFCFS > tasks/output/tasks_003.out 
	cat tasks/output/tasks_003.out | graphsched.py  > tasks/images/tasks_011.png
	cat tasks/output/tasks_003.out | graph_cores.py >  /dev/null 2>&1
	mv out_cores_timeline.png tasks/images/tasks_012.png
	cat tasks/output/tasks_002.out | event_parser.py > /dev/null 2>&1
	mv out_cores_resume.png   tasks/images/tasks_013.png
	mv out_pids_resume.png    tasks/images/tasks_014.png
	mv out_pids_timeline.png  tasks/images/tasks_015.png
	
	simusched tasks/tasks_002.tsk 4 5 1 SchedFCFS > tasks/output/tasks_004.out 
	cat tasks/output/tasks_004.out | graphsched.py  > tasks/images/tasks_021.png
	cat tasks/output/tasks_004.out | graph_cores.py >  /dev/null 2>&1
	mv out_cores_timeline.png tasks/images/tasks_022.png
	cat tasks/output/tasks_002.out | event_parser.py > /dev/null 2>&1
	mv out_cores_resume.png   tasks/images/tasks_023.png
	mv out_pids_resume.png    tasks/images/tasks_024.png
	mv out_pids_timeline.png  tasks/images/tasks_025.png

