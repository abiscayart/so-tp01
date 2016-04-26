.PHONY += ejercicio08

ejercicio8: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 08'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched rr2/rr2_001.tsk 2 4 0  SchedRR  2 4 4 | graphsched.py  >  rr2/images/rr2_000.png
	simusched rr2/rr2_001.tsk 2 4 0  SchedRR2 2 4 4 | graphsched.py  >  rr2/images/rr2_001.png
	simusched rr2/rr2_002.tsk 2 1 20 SchedRR  2 2 2 | graphsched.py  >  rr2/images/rr2_002.png
	simusched rr2/rr2_002.tsk 2 1 20 SchedRR2 2 2 2 | graphsched.py  >  rr2/images/rr2_003.png
