.PHONY += ejercicio07

ejercicio7: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 07'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched mistery/mist.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > mistery/mist1.png
	simusched mistery/mist2.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > mistery/mist2.png
	simusched mistery/mist3.tsk 1 2 0 SchedMistery 5 15 10 4 2 | ./graphsched.py > mistery/mist3.png
	simusched mistery/mist.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | ./graphsched.py > mistery/mist11.png
	simusched mistery/mist2.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | ./graphsched.py > mistery/mist22.png
	simusched mistery/mist3.tsk 1 2 0 SchedNoMistery 5 15 10 4 2 | graphsched.py > mistery/mist33.png





		

