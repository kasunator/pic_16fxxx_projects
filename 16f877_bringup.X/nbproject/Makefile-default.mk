#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Drivers/button_inputs.c Drivers/display_multiplexer.c System/GPIO_driver.c System/Timer1_driver.c System/Timer0_driver.c main.c marquee.c boy.c screen_buffer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Drivers/button_inputs.p1 ${OBJECTDIR}/Drivers/display_multiplexer.p1 ${OBJECTDIR}/System/GPIO_driver.p1 ${OBJECTDIR}/System/Timer1_driver.p1 ${OBJECTDIR}/System/Timer0_driver.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/marquee.p1 ${OBJECTDIR}/boy.p1 ${OBJECTDIR}/screen_buffer.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/Drivers/button_inputs.p1.d ${OBJECTDIR}/Drivers/display_multiplexer.p1.d ${OBJECTDIR}/System/GPIO_driver.p1.d ${OBJECTDIR}/System/Timer1_driver.p1.d ${OBJECTDIR}/System/Timer0_driver.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/marquee.p1.d ${OBJECTDIR}/boy.p1.d ${OBJECTDIR}/screen_buffer.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Drivers/button_inputs.p1 ${OBJECTDIR}/Drivers/display_multiplexer.p1 ${OBJECTDIR}/System/GPIO_driver.p1 ${OBJECTDIR}/System/Timer1_driver.p1 ${OBJECTDIR}/System/Timer0_driver.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/marquee.p1 ${OBJECTDIR}/boy.p1 ${OBJECTDIR}/screen_buffer.p1

# Source Files
SOURCEFILES=Drivers/button_inputs.c Drivers/display_multiplexer.c System/GPIO_driver.c System/Timer1_driver.c System/Timer0_driver.c main.c marquee.c boy.c screen_buffer.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F877A
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Drivers/button_inputs.p1: Drivers/button_inputs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/button_inputs.p1.d 
	@${RM} ${OBJECTDIR}/Drivers/button_inputs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/Drivers/button_inputs.p1 Drivers/button_inputs.c 
	@-${MV} ${OBJECTDIR}/Drivers/button_inputs.d ${OBJECTDIR}/Drivers/button_inputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Drivers/button_inputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Drivers/display_multiplexer.p1: Drivers/display_multiplexer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/display_multiplexer.p1.d 
	@${RM} ${OBJECTDIR}/Drivers/display_multiplexer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/Drivers/display_multiplexer.p1 Drivers/display_multiplexer.c 
	@-${MV} ${OBJECTDIR}/Drivers/display_multiplexer.d ${OBJECTDIR}/Drivers/display_multiplexer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Drivers/display_multiplexer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/GPIO_driver.p1: System/GPIO_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/GPIO_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/GPIO_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/GPIO_driver.p1 System/GPIO_driver.c 
	@-${MV} ${OBJECTDIR}/System/GPIO_driver.d ${OBJECTDIR}/System/GPIO_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/GPIO_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/Timer1_driver.p1: System/Timer1_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/Timer1_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/Timer1_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/Timer1_driver.p1 System/Timer1_driver.c 
	@-${MV} ${OBJECTDIR}/System/Timer1_driver.d ${OBJECTDIR}/System/Timer1_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/Timer1_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/Timer0_driver.p1: System/Timer0_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/Timer0_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/Timer0_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/Timer0_driver.p1 System/Timer0_driver.c 
	@-${MV} ${OBJECTDIR}/System/Timer0_driver.d ${OBJECTDIR}/System/Timer0_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/Timer0_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/marquee.p1: marquee.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/marquee.p1.d 
	@${RM} ${OBJECTDIR}/marquee.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/marquee.p1 marquee.c 
	@-${MV} ${OBJECTDIR}/marquee.d ${OBJECTDIR}/marquee.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/marquee.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/boy.p1: boy.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boy.p1.d 
	@${RM} ${OBJECTDIR}/boy.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/boy.p1 boy.c 
	@-${MV} ${OBJECTDIR}/boy.d ${OBJECTDIR}/boy.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/boy.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/screen_buffer.p1: screen_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/screen_buffer.p1.d 
	@${RM} ${OBJECTDIR}/screen_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit3   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/screen_buffer.p1 screen_buffer.c 
	@-${MV} ${OBJECTDIR}/screen_buffer.d ${OBJECTDIR}/screen_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/screen_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/Drivers/button_inputs.p1: Drivers/button_inputs.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/button_inputs.p1.d 
	@${RM} ${OBJECTDIR}/Drivers/button_inputs.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/Drivers/button_inputs.p1 Drivers/button_inputs.c 
	@-${MV} ${OBJECTDIR}/Drivers/button_inputs.d ${OBJECTDIR}/Drivers/button_inputs.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Drivers/button_inputs.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/Drivers/display_multiplexer.p1: Drivers/display_multiplexer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/Drivers" 
	@${RM} ${OBJECTDIR}/Drivers/display_multiplexer.p1.d 
	@${RM} ${OBJECTDIR}/Drivers/display_multiplexer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/Drivers/display_multiplexer.p1 Drivers/display_multiplexer.c 
	@-${MV} ${OBJECTDIR}/Drivers/display_multiplexer.d ${OBJECTDIR}/Drivers/display_multiplexer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Drivers/display_multiplexer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/GPIO_driver.p1: System/GPIO_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/GPIO_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/GPIO_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/GPIO_driver.p1 System/GPIO_driver.c 
	@-${MV} ${OBJECTDIR}/System/GPIO_driver.d ${OBJECTDIR}/System/GPIO_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/GPIO_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/Timer1_driver.p1: System/Timer1_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/Timer1_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/Timer1_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/Timer1_driver.p1 System/Timer1_driver.c 
	@-${MV} ${OBJECTDIR}/System/Timer1_driver.d ${OBJECTDIR}/System/Timer1_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/Timer1_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/System/Timer0_driver.p1: System/Timer0_driver.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/System" 
	@${RM} ${OBJECTDIR}/System/Timer0_driver.p1.d 
	@${RM} ${OBJECTDIR}/System/Timer0_driver.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/System/Timer0_driver.p1 System/Timer0_driver.c 
	@-${MV} ${OBJECTDIR}/System/Timer0_driver.d ${OBJECTDIR}/System/Timer0_driver.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/System/Timer0_driver.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/marquee.p1: marquee.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/marquee.p1.d 
	@${RM} ${OBJECTDIR}/marquee.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/marquee.p1 marquee.c 
	@-${MV} ${OBJECTDIR}/marquee.d ${OBJECTDIR}/marquee.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/marquee.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/boy.p1: boy.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/boy.p1.d 
	@${RM} ${OBJECTDIR}/boy.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/boy.p1 boy.c 
	@-${MV} ${OBJECTDIR}/boy.d ${OBJECTDIR}/boy.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/boy.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/screen_buffer.p1: screen_buffer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/screen_buffer.p1.d 
	@${RM} ${OBJECTDIR}/screen_buffer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/screen_buffer.p1 screen_buffer.c 
	@-${MV} ${OBJECTDIR}/screen_buffer.d ${OBJECTDIR}/screen_buffer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/screen_buffer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit3  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -mrom=default,-1f00-1fff -mram=default,-0-0,-70-70,-80-80,-f0-f0,-100-100,-170-170,-180-180,-1e5-1f0  $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/16f877_bringup.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
