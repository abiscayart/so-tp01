.PHONY += ejercicio8

ejercicio8: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 8...'
	@echo -e '\033[0m'
	simusched ej8/rr2_001.tsk 2 4 0  SchedRR  2 4 4 | graphsched.py  >  ej8/images/rr2_000.png
	simusched ej8/rr2_001.tsk 2 4 0  SchedRR2 2 4 4 | graphsched.py  >  ej8/images/rr2_001.png
	simusched ej8/rr2_002.tsk 2 1 20 SchedRR  2 2 2 | graphsched.py  >  ej8/images/rr2_002.png
	simusched ej8/rr2_002.tsk 2 1 20 SchedRR2 2 2 2 | graphsched.py  >  ej8/images/rr2_003.png
