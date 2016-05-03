.PHONY += ejercicio8

ejercicio8: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 8...'
	@echo -e '\033[0m'
	simusched ej8/rr2_1.tsk 2 4 0  SchedRR  2 4 4 | graphsched.py  >  ej8/images/ej8_rr_1.png
	simusched ej8/rr2_1.tsk 2 4 0  SchedRR2 2 4 4 | graphsched.py  >  ej8/images/ej8_rr2_1.png
	simusched ej8/rr2_2.tsk 2 1 20 SchedRR  2 2 2 | graphsched.py  >  ej8/images/ej8_rr_2.png
	simusched ej8/rr2_2.tsk 2 1 20 SchedRR2 2 2 2 | graphsched.py  >  ej8/images/ej8_rr2_2.png
