.PHONY: install run

install:
	@echo 'Installing Simple Pong Game... \n';
	chmod +x install.sh;
	chmod +x run.sh;
	./install.sh;
	@echo '\nINSTALL COMPLETED\n';
	
run:
	./run.sh
