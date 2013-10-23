subsystem:
	$(MAKE) -C c_neig
	$(MAKE) -C neighborhoods

clean:
	$(MAKE) clean -C c_neig
	$(MAKE) clean -C neighborhoods
