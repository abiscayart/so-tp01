.PHONY += ejercicio03

ejercicio3: all
	@echo -e '\033[0;32m'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo '[INFO] EJERCICIO 03'
	@echo '[INFO] ------------------------------------------------------------------------'
	@echo -e '\033[0m'
	simusched batch/batch_001.tsk 1 1 1 SchedFCFS   >  batch/output/batch_001.out
	cat batch/output/batch_001.out | graphsched.py  >  batch/images/batch_000.png
	cat batch/output/batch_001.out | graph_cores.py  >  /dev/null 2>&1
	mv out_cores_timeline.png batch/images/batch_001.png
