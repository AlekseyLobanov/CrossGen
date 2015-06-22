.PHONY: clean All

All:
	@echo "----------Building project:[ wxCrossGen - Release ]----------"
	@cd "wxCrossGen" && $(MAKE) -f  "wxCrossGen.mk"
clean:
	@echo "----------Cleaning project:[ wxCrossGen - Release ]----------"
	@cd "wxCrossGen" && $(MAKE) -f  "wxCrossGen.mk" clean
