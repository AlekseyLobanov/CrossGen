.PHONY: clean All

All:
	@echo "----------Building project:[ wxCrossGen - Debug ]----------"
	@cd "wxCrossGen" && $(MAKE) -f  "wxCrossGen.mk"
clean:
	@echo "----------Cleaning project:[ wxCrossGen - Debug ]----------"
	@cd "wxCrossGen" && $(MAKE) -f  "wxCrossGen.mk" clean
