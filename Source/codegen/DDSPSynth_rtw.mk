###########################################################################
## Makefile generated for MATLAB file/project 'DDSPSynth'. 
## 
## Makefile     : DDSPSynth_rtw.mk
## Generated on : Tue Nov 24 15:35:39 2020
## MATLAB Coder version: 5.0 (R2020a)
## 
## Build Info:
## 
## Final product: .\DDSPSynth.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = DDSPSynth
MAKEFILE                  = DDSPSynth_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2020a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2020a\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
MASTER_ANCHOR_DIR         = 
START_DIR                 = C:\Users\svkly\ONEDRI~1\SMC7Proj\MATLAB~1\codegen\lib\DDSPSY~1
TGT_FCN_LIB               = ISO_C++
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = .
COMPILER_COMMAND_FILE     = DDSPSynth_rtw_comp.rsp
CMD_FILE                  = DDSPSynth_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = DDSPSynth.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2019 v16.0 | nmake (64-bit Windows)
# Supported Version(s):    16.0
# ToolchainInfo Version:   2020a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\DDSPSynth.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=DDSPSynth

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\rt_nonfinite.cpp $(START_DIR)\rtGetNaN.cpp $(START_DIR)\rtGetInf.cpp $(START_DIR)\DDSPSynth_data.cpp $(START_DIR)\DDSPSynth_initialize.cpp $(START_DIR)\DDSPSynth_terminate.cpp $(START_DIR)\additive.cpp $(START_DIR)\subtractive.cpp $(START_DIR)\ColoredNoise.cpp $(START_DIR)\SystemCore.cpp $(START_DIR)\randn.cpp $(START_DIR)\eml_rand_mt19937ar_stateful.cpp $(START_DIR)\firls.cpp $(START_DIR)\mldivide.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj DDSPSynth_data.obj DDSPSynth_initialize.obj DDSPSynth_terminate.obj additive.obj subtractive.obj ColoredNoise.obj SystemCore.obj randn.obj eml_rand_mt19937ar_stateful.obj firls.obj mldivide.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{C:\Users\svkly\ONEDRI~1\SMC7Proj\MATLAB~1}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{C:\Users\svkly\ONEDRI~1\SMC7Proj\MATLAB~1}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


rt_nonfinite.obj : $(START_DIR)\rt_nonfinite.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rt_nonfinite.cpp


rtGetNaN.obj : $(START_DIR)\rtGetNaN.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetNaN.cpp


rtGetInf.obj : $(START_DIR)\rtGetInf.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\rtGetInf.cpp


DDSPSynth_data.obj : $(START_DIR)\DDSPSynth_data.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\DDSPSynth_data.cpp


DDSPSynth_initialize.obj : $(START_DIR)\DDSPSynth_initialize.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\DDSPSynth_initialize.cpp


DDSPSynth_terminate.obj : $(START_DIR)\DDSPSynth_terminate.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\DDSPSynth_terminate.cpp


additive.obj : $(START_DIR)\additive.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\additive.cpp


subtractive.obj : $(START_DIR)\subtractive.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\subtractive.cpp


ColoredNoise.obj : $(START_DIR)\ColoredNoise.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\ColoredNoise.cpp


SystemCore.obj : $(START_DIR)\SystemCore.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\SystemCore.cpp


randn.obj : $(START_DIR)\randn.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\randn.cpp


eml_rand_mt19937ar_stateful.obj : $(START_DIR)\eml_rand_mt19937ar_stateful.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\eml_rand_mt19937ar_stateful.cpp


firls.obj : $(START_DIR)\firls.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\firls.cpp


mldivide.obj : $(START_DIR)\mldivide.cpp
	$(CPP) $(CPPFLAGS) -Fo"$@" $(START_DIR)\mldivide.cpp


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


