################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
SDCardLib/sdcard.obj: ../SDCardLib/sdcard.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --code_model=large --data_model=large --near_data=none --use_hw_mpy=F5 --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/FatFs" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/HAL" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/SDCardLib" --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="SDCardLib/sdcard.d_raw" --obj_directory="SDCardLib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


