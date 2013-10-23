subsystem:
	$(MAKE) -C c_neig
	$(MAKE) -C neighborhoods
	$(MAKE) -C neig_out

clean:
	$(MAKE) clean -C c_neig
	$(MAKE) clean -C neighborhoods
	$(MAKE) clean -C neig_out
