.PHONY += ejercicio7

ejercicio7: all
	@echo -e '\033[0;32m'
	@echo '[INFO] Generating images for ejercicio 7...'
	@echo -e '\033[0m'
	simusched ej7/mist.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > ej7/images/mist1.png
	simusched ej7/mist2.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > ej7/images/mist2.png
	simusched ej7/mist3.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > ej7/images/mist3.png
	simusched ej7/mist.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | ./graphsched.py > ej7/images/mist11.png
	simusched ej7/mist2.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | ./graphsched.py > ej7/images/mist22.png
	simusched ej7/mist3.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | graphsched.py > ej7/images/mist33.png
