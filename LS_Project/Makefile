EASYLOCAL = ../../easylocal-3
FLAGS = -std=c++11 -Wall #-O3 # -g
COMPOPTS = -I$(EASYLOCAL)/include $(FLAGS)
EASYLOCALLIB = -lEasyLocal -lboost_program_options
LINKOPTS = -L$(EASYLOCAL)/lib $(EASYLOCALLIB)  -pthread

SOURCE_FILES = LS_Data.cc LS_Basics.cc LS_Helpers.cc  LS_Main.cc
OBJECT_FILES = LS_Data.o LS_Basics.o LS_Helpers.o LS_Main.o
HEADER_FILES = LS_Data.hh LS_Basics.hh LS_Helpers.hh  

ls: $(OBJECT_FILES)
	g++ $(OBJECT_FILES) $(LINKOPTS) -o ls

LS_Data.o: LS_Data.cc LS_Data.hh
	g++ -c $(COMPOPTS) LS_Data.cc

LS_Basics.o: LS_Basics.cc LS_Basics.hh LS_Data.hh
	g++ -c $(COMPOPTS) LS_Basics.cc

LS_Helpers.o: LS_Helpers.cc LS_Helpers.hh LS_Basics.hh LS_Data.hh
	g++ -c $(COMPOPTS) LS_Helpers.cc

LS_Main.o: LS_Main.cc LS_Helpers.hh LS_Basics.hh LS_Data.hh
	g++ -c $(COMPOPTS) LS_Main.cc

clean:
	rm -f $(OBJECT_FILES) ls

