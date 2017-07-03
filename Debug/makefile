################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./util.obj" \
"./ETF5438A_HAL/hal_board.obj" \
"./ETF5438A_HAL/hal_led.obj" \
"./ETF5438A_HAL/ringbuffer.obj" \
"./ETF5438A_HAL/uart.obj" \
"./F5XX_6XX_Core_Lib/hal_PMM.obj" \
"./F5XX_6XX_Core_Lib/hal_UCS.obj" \
"./FreeRTOS_Source/event_groups.obj" \
"./FreeRTOS_Source/list.obj" \
"./FreeRTOS_Source/queue.obj" \
"./FreeRTOS_Source/tasks.obj" \
"./FreeRTOS_Source/timers.obj" \
"./FreeRTOS_Source/portable/CCS/MSP430X/port.obj" \
"./FreeRTOS_Source/portable/CCS/MSP430X/portext.obj" \
"./FreeRTOS_Source/portable/MemMang/heap_1.obj" \
"../lnk_msp430f5438a.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ETF5438A_HAL/subdir_vars.mk
-include F5XX_6XX_Core_Lib/subdir_vars.mk
-include FreeRTOS_Source/subdir_vars.mk
-include FreeRTOS_Source/portable/CCS/MSP430X/subdir_vars.mk
-include FreeRTOS_Source/portable/MemMang/subdir_vars.mk
-include subdir_rules.mk
-include ETF5438A_HAL/subdir_rules.mk
-include F5XX_6XX_Core_Lib/subdir_rules.mk
-include FreeRTOS_Source/subdir_rules.mk
-include FreeRTOS_Source/portable/CCS/MSP430X/subdir_rules.mk
-include FreeRTOS_Source/portable/MemMang/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
minimal.out \

EXE_OUTPUTS__QUOTED += \
"minimal.out" \

BIN_OUTPUTS += \
minimal.hex \

BIN_OUTPUTS__QUOTED += \
"minimal.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "minimal.out"

# Tool invocations
minimal.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/bin/cl430" -vmspx --code_model=large --data_model=small --use_hw_mpy=F5 --advice:power=all --define=__MSP430F5438A__ --define=__LARGE_CODE_MODEL__ --define=__SMALL_DATA_MODEL__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 -z -m"minimal.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccsv7/ccs_base/msp430/include" -i"C:/ti/ccsv7/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/lib" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="minimal_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "minimal.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

minimal.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.0.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "minimal.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "util.obj" "ETF5438A_HAL\hal_board.obj" "ETF5438A_HAL\hal_led.obj" "ETF5438A_HAL\ringbuffer.obj" "ETF5438A_HAL\uart.obj" "F5XX_6XX_Core_Lib\hal_PMM.obj" "F5XX_6XX_Core_Lib\hal_UCS.obj" "FreeRTOS_Source\event_groups.obj" "FreeRTOS_Source\list.obj" "FreeRTOS_Source\queue.obj" "FreeRTOS_Source\tasks.obj" "FreeRTOS_Source\timers.obj" "FreeRTOS_Source\portable\CCS\MSP430X\port.obj" "FreeRTOS_Source\portable\CCS\MSP430X\portext.obj" "FreeRTOS_Source\portable\MemMang\heap_1.obj" 
	-$(RM) "main.d" "util.d" "ETF5438A_HAL\hal_board.d" "ETF5438A_HAL\hal_led.d" "ETF5438A_HAL\ringbuffer.d" "ETF5438A_HAL\uart.d" "F5XX_6XX_Core_Lib\hal_PMM.d" "F5XX_6XX_Core_Lib\hal_UCS.d" "FreeRTOS_Source\event_groups.d" "FreeRTOS_Source\list.d" "FreeRTOS_Source\queue.d" "FreeRTOS_Source\tasks.d" "FreeRTOS_Source\timers.d" "FreeRTOS_Source\portable\CCS\MSP430X\port.d" "FreeRTOS_Source\portable\MemMang\heap_1.d" 
	-$(RM) "FreeRTOS_Source\portable\CCS\MSP430X\portext.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

