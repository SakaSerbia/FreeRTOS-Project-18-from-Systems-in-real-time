################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/bin/cl430" -vmspx --code_model=large --data_model=small --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/ETF5438A_HAL" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/F5XX_6XX_Core_Lib" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/FreeRTOS_Source/include" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/FreeRTOS_Source/portable/CCS/MSP430X" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/include" --advice:power=all --define=__MSP430F5438A__ --define=__LARGE_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

util.obj: ../util.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/bin/cl430" -vmspx --code_model=large --data_model=small --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/ETF5438A_HAL" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/F5XX_6XX_Core_Lib" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/FreeRTOS_Source/include" --include_path="C:/Users/Admin/Desktop/stefan 675 2016/minimal/FreeRTOS_Source/portable/CCS/MSP430X" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/include" --advice:power=all --define=__MSP430F5438A__ --define=__LARGE_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="util.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


