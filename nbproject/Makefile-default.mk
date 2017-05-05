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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c remappable.c dsPWM.c dsEInt.c dsSPI.c dsTimers.c C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c dsOscillator.c circular_buffer.c dsEserial.c dsUART.c dsStepper.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/remappable.o ${OBJECTDIR}/dsPWM.o ${OBJECTDIR}/dsEInt.o ${OBJECTDIR}/dsSPI.o ${OBJECTDIR}/dsTimers.o ${OBJECTDIR}/_ext/772281530/encoding.o ${OBJECTDIR}/dsOscillator.o ${OBJECTDIR}/circular_buffer.o ${OBJECTDIR}/dsEserial.o ${OBJECTDIR}/dsUART.o ${OBJECTDIR}/dsStepper.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/remappable.o.d ${OBJECTDIR}/dsPWM.o.d ${OBJECTDIR}/dsEInt.o.d ${OBJECTDIR}/dsSPI.o.d ${OBJECTDIR}/dsTimers.o.d ${OBJECTDIR}/_ext/772281530/encoding.o.d ${OBJECTDIR}/dsOscillator.o.d ${OBJECTDIR}/circular_buffer.o.d ${OBJECTDIR}/dsEserial.o.d ${OBJECTDIR}/dsUART.o.d ${OBJECTDIR}/dsStepper.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/remappable.o ${OBJECTDIR}/dsPWM.o ${OBJECTDIR}/dsEInt.o ${OBJECTDIR}/dsSPI.o ${OBJECTDIR}/dsTimers.o ${OBJECTDIR}/_ext/772281530/encoding.o ${OBJECTDIR}/dsOscillator.o ${OBJECTDIR}/circular_buffer.o ${OBJECTDIR}/dsEserial.o ${OBJECTDIR}/dsUART.o ${OBJECTDIR}/dsStepper.o

# Source Files
SOURCEFILES=main.c remappable.c dsPWM.c dsEInt.c dsSPI.c dsTimers.c C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c dsOscillator.c circular_buffer.c dsEserial.c dsUART.c dsStepper.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ64GP802
MP_LINKER_FILE_OPTION=,--script=p33FJ64GP802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/remappable.o: remappable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/remappable.o.d 
	@${RM} ${OBJECTDIR}/remappable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  remappable.c  -o ${OBJECTDIR}/remappable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/remappable.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/remappable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsPWM.o: dsPWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsPWM.o.d 
	@${RM} ${OBJECTDIR}/dsPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsPWM.c  -o ${OBJECTDIR}/dsPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsPWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsPWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsEInt.o: dsEInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsEInt.o.d 
	@${RM} ${OBJECTDIR}/dsEInt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsEInt.c  -o ${OBJECTDIR}/dsEInt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsEInt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsEInt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsSPI.o: dsSPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsSPI.o.d 
	@${RM} ${OBJECTDIR}/dsSPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsSPI.c  -o ${OBJECTDIR}/dsSPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsSPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsSPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsTimers.o: dsTimers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsTimers.o.d 
	@${RM} ${OBJECTDIR}/dsTimers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsTimers.c  -o ${OBJECTDIR}/dsTimers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsTimers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsTimers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/772281530/encoding.o: C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/772281530" 
	@${RM} ${OBJECTDIR}/_ext/772281530/encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/772281530/encoding.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c  -o ${OBJECTDIR}/_ext/772281530/encoding.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/772281530/encoding.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/772281530/encoding.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsOscillator.o: dsOscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsOscillator.o.d 
	@${RM} ${OBJECTDIR}/dsOscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsOscillator.c  -o ${OBJECTDIR}/dsOscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsOscillator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsOscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/circular_buffer.o: circular_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/circular_buffer.o.d 
	@${RM} ${OBJECTDIR}/circular_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  circular_buffer.c  -o ${OBJECTDIR}/circular_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/circular_buffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/circular_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsEserial.o: dsEserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsEserial.o.d 
	@${RM} ${OBJECTDIR}/dsEserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsEserial.c  -o ${OBJECTDIR}/dsEserial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsEserial.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsEserial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsUART.o: dsUART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsUART.o.d 
	@${RM} ${OBJECTDIR}/dsUART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsUART.c  -o ${OBJECTDIR}/dsUART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsUART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsUART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsStepper.o: dsStepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsStepper.o.d 
	@${RM} ${OBJECTDIR}/dsStepper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsStepper.c  -o ${OBJECTDIR}/dsStepper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsStepper.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsStepper.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/remappable.o: remappable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/remappable.o.d 
	@${RM} ${OBJECTDIR}/remappable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  remappable.c  -o ${OBJECTDIR}/remappable.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/remappable.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/remappable.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsPWM.o: dsPWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsPWM.o.d 
	@${RM} ${OBJECTDIR}/dsPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsPWM.c  -o ${OBJECTDIR}/dsPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsPWM.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsPWM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsEInt.o: dsEInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsEInt.o.d 
	@${RM} ${OBJECTDIR}/dsEInt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsEInt.c  -o ${OBJECTDIR}/dsEInt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsEInt.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsEInt.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsSPI.o: dsSPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsSPI.o.d 
	@${RM} ${OBJECTDIR}/dsSPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsSPI.c  -o ${OBJECTDIR}/dsSPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsSPI.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsSPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsTimers.o: dsTimers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsTimers.o.d 
	@${RM} ${OBJECTDIR}/dsTimers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsTimers.c  -o ${OBJECTDIR}/dsTimers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsTimers.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsTimers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/772281530/encoding.o: C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/772281530" 
	@${RM} ${OBJECTDIR}/_ext/772281530/encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/772281530/encoding.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X/encoding.c  -o ${OBJECTDIR}/_ext/772281530/encoding.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/772281530/encoding.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/772281530/encoding.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsOscillator.o: dsOscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsOscillator.o.d 
	@${RM} ${OBJECTDIR}/dsOscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsOscillator.c  -o ${OBJECTDIR}/dsOscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsOscillator.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsOscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/circular_buffer.o: circular_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/circular_buffer.o.d 
	@${RM} ${OBJECTDIR}/circular_buffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  circular_buffer.c  -o ${OBJECTDIR}/circular_buffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/circular_buffer.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/circular_buffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsEserial.o: dsEserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsEserial.o.d 
	@${RM} ${OBJECTDIR}/dsEserial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsEserial.c  -o ${OBJECTDIR}/dsEserial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsEserial.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsEserial.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsUART.o: dsUART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsUART.o.d 
	@${RM} ${OBJECTDIR}/dsUART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsUART.c  -o ${OBJECTDIR}/dsUART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsUART.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsUART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsStepper.o: dsStepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsStepper.o.d 
	@${RM} ${OBJECTDIR}/dsStepper.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsStepper.c  -o ${OBJECTDIR}/dsStepper.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsStepper.o.d"        -g -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/dsStepper.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X"  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf  -menable-fixed -I"C:/Users/Manuel/Documents/PICLibrary/PICLibraries.X" -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dsTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
