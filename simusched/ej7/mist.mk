.PHONY += ejercicio7

ejercicio7: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 7...'
	@echo -e '\033[0m'
	simusched ej7/mist.tsk 1 0 0 SchedMistery 10 7 5 3 | ./graphsched.py > ej7/images/mist1.png
	simusched ej7/mist2.tsk 1 0 0 SchedMistery 20 5 15 7 23 35 | ./graphsched.py > ej7/images/mist2.png
	simusched ej7/mist3.tsk 1 0 0 SchedMistery 5 10 15 20 25 30 35 | ./graphsched.py > ej7/images/mist3.png
	
	simusched ej7/mist.tsk 1 0 0 SchedNoMistery 10 7 5 3 | ./graphsched.py > ej7/images/no-mist1.png
	simusched ej7/mist2.tsk 1 0 0 SchedNoMistery 20 5 15 7 23 35 | ./graphsched.py > ej7/images/no-mist2.png
	simusched ej7/mist3.tsk 1 0 0 SchedNoMistery 5 10 15 20 25 30 35 | graphsched.py > ej7/images/no-mist3.png
