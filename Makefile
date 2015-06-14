.PHONY: clean All

All:
	@echo "----------Building project:[ CrossBench - Release ]----------"
	@cd "CrossBench" && $(MAKE) -f  "CrossBench.mk"
clean:
	@echo "----------Cleaning project:[ CrossBench - Release ]----------"
	@cd "CrossBench" && $(MAKE) -f  "CrossBench.mk" clean
