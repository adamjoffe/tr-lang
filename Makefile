CC=g++
CCFLAGS=-std=c++11 -O2
LIBS=-lboost_program_options -lboost_graph -fsanitize=address

FLEX=flex
FLEXFLAGS=

BISON=bison
BISONFLAGS=-d

OBJ_DIR=obj
# need to filter out parser and scanner since they need to be compiled at linking time
# also filter out the mains
SRCS=$(filter-out tr_parser.cpp tr_scanner.cpp proc_main.cpp stand_alone_main.cpp, $(wildcard *.cpp))
OBJS=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

###############################
# make for the stand alone main
TARGET=TR-Lang

all: object_dir $(TARGET)

$(TARGET): stand_alone_main.cpp tr_parser.cpp tr_scanner.cpp $(OBJ_DIR)/blackboard.o $(OBJ_DIR)/interfacer.o $(OBJ_DIR)/data_module.o $(OBJ_DIR)/ast.o \
		$(OBJ_DIR)/print_tree.o $(OBJ_DIR)/tr_hierarchy.o $(OBJ_DIR)/tr_profiler.o $(OBJ_DIR)/tr_debugger.o \
		$(OBJ_DIR)/default_vector.o $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

clean: cleanobj
	rm -rf $(TARGET)

###############################
# make for the demo project
DEMO_TARGET=demo/Demo

demo: object_dir $(DEMO_TARGET)

$(OBJ_DIR)/ev3dev.o: demo/ev3dev-lang-cpp/ev3dev.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/ev3dev.o demo/ev3dev-lang-cpp/ev3dev.cpp

$(OBJ_DIR)/drive_control.o: demo/drive_control.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/drive_control.o demo/drive_control.cpp

$(OBJ_DIR)/sensor_control.o: demo/sensor_control.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/sensor_control.o demo/sensor_control.cpp

$(DEMO_TARGET): demo/demo_main.cpp tr_parser.cpp tr_scanner.cpp $(OBJ_DIR)/blackboard.o $(OBJ_DIR)/interfacer.o $(OBJ_DIR)/data_module.o $(OBJ_DIR)/ast.o \
		$(OBJ_DIR)/print_tree.o $(OBJ_DIR)/tr_hierarchy.o $(OBJ_DIR)/tr_profiler.o $(OBJ_DIR)/tr_debugger.o \
		$(OBJ_DIR)/default_vector.o $(OBJS) \
		$(OBJ_DIR)/ev3dev.o $(OBJ_DIR)/drive_control.o $(OBJ_DIR)/sensor_control.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

cleandemo: cleanobj
	rm -rf $(DEMO_TARGET)

###############################
# make for the process main
PROC_TARGET=TR-Proc

proc: object_dir $(PROC_TARGET)

$(PROC_TARGET): proc_main.cpp tr_parser.cpp tr_scanner.cpp $(OBJ_DIR)/blackboard.o $(OBJ_DIR)/interfacer.o $(OBJ_DIR)/data_module.o $(OBJ_DIR)/ast.o \
		$(OBJ_DIR)/print_tree.o $(OBJ_DIR)/tr_hierarchy.o $(OBJ_DIR)/tr_profiler.o $(OBJ_DIR)/tr_debugger.o \
		$(OBJ_DIR)/default_vector.o $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIBS)

cleanproc: cleanobj
	rm -rf $(PROC_TARGET)

###############################

object_dir:
	if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi

# Generated files

tr_scanner.cpp: tr_scanner.l
	$(FLEX) $(FLEXFLAGS) -o tr_scanner.cpp tr_scanner.l

tr_parser.cpp: tr_parser.y
	$(BISON) $(BISONFLAGS) -o tr_parser.cpp tr_parser.y

# blackboard root structure
$(OBJ_DIR)/blackboard.o: blackboard/blackboard.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/blackboard.o blackboard/blackboard.cpp

# blackboard module structure
$(OBJ_DIR)/data_module.o: blackboard/data_module.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/data_module.o blackboard/data_module.cpp

# blackboard TR-Lang interfacer
$(OBJ_DIR)/interfacer.o: blackboard/interfacer.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/interfacer.o blackboard/interfacer.cpp

# AST library
$(OBJ_DIR)/ast.o: AST/abstract_visitor.cpp 
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/ast.o AST/abstract_visitor.cpp

# debug tree
$(OBJ_DIR)/print_tree.o: tools/print_tree.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/print_tree.o tools/print_tree.cpp

# hierarchy tree
$(OBJ_DIR)/tr_hierarchy.o: tools/tr_hierarchy.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/tr_hierarchy.o tools/tr_hierarchy.cpp

# profiler
$(OBJ_DIR)/tr_profiler.o: tools/tr_profiler.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/tr_profiler.o tools/tr_profiler.cpp

# debugger
$(OBJ_DIR)/tr_debugger.o: tools/tr_debugger.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/tr_debugger.o tools/tr_debugger.cpp

# vectpr library
$(OBJ_DIR)/default_vector.o: libs/default_vector.cpp
	$(CC) $(CCFLAGS) -c -o $(OBJ_DIR)/default_vector.o libs/default_vector.cpp

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

###############################
# always force run the doc generation
doc: FORCE
	doxygen doc/Doxyfile

FORCE:

cleandoc:
	rm -rf doc/html

###############################

cleanobj:
	rm -rf $(OBJ_DIR)/*.o

extraclean: clean cleandoc cleandemo cleanproc
	rm -rf *.hh tr_scanner.cpp tr_parser.cpp tr_parser.h
	rm -rf $(OBJ_DIR)
	rm -rf logs/*
