################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FatFs/ff.obj: ../FatFs/ff.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --code_model=large --data_model=restricted --near_data=none -O2 --use_hw_mpy=F5 --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/FatFs" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/HAL" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/SDCardLib" --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FatFs/ff.d_raw" --obj_directory="FatFs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

FatFs/mmc.obj: ../FatFs/mmc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/bin/cl430" -vmspx --code_model=large --data_model=restricted --near_data=none -O2 --use_hw_mpy=F5 --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/FatFs" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/HAL" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/SDCardLib" --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver" --include_path="C:/Users/Vickram Gidwani/Documents/GitHub/EE-107/himax-driver/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.4.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FatFs/mmc.d_raw" --obj_directory="FatFs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


