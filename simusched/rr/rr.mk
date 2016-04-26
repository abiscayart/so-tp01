.PHONY += ejercicio05 , ejercicio06

ejercicio5: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 05'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 2  | graphsched.py  >  rr/images/rr_000.png
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 10 | graphsched.py  >  rr/images/rr_001.png
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 30 | graphsched.py  >  rr/images/rr_002.png
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 2  > rr/output/rr_010.out 
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 10 > rr/output/rr_011.out
	simusched rr/rr_001.tsk 1 2 1 SchedRR 1 30 > rr/output/rr_012.out

ejercicio6: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 06'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched rr/rr_001.tsk 1 2 1 SchedFCFS 1 2 0 | graphsched.py  >  FCFS/images/FCFS_000.png
