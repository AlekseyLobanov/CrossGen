.PHONY: clean All

All:
	@echo "----------Building project:[ CrossBench - Debug ]----------"
	@cd "CrossBench" && $(MAKE) -f  "CrossBench.mk"
clean:
	@echo "----------Cleaning project:[ CrossBench - Debug ]----------"
	@cd "CrossBench" && $(MAKE) -f  "CrossBench.mk" clean
