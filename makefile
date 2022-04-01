# show compiler output
VERBOSE = 0

# include toolchain options
include src/vex/vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard src/robot/*.cpp) 
SRC_C += $(wildcard src/robot/*.c)
SRC_C += $(wildcard src/robot/*/*.cpp) 
SRC_C += $(wildcard src/robot/*/*.c)

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# # location of include files that c and cpp files depend on
SRC_H  = $(wildcard src/vex/include/*.h)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include

# build targets
all: $(BUILD)/$(PROJECT).bin

include src/vex/vex/mkrules.mk
