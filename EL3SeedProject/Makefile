EASYLOCAL = ../../easylocal-3
FLAGS = -std=c++11 -Wall #-O3 # -g
COMPOPTS = -I$(EASYLOCAL)/include $(FLAGS)
EASYLOCALLIB = -lEasyLocal -lboost_program_options
LINKOPTS = -L$(EASYLOCAL)/lib $(EASYLOCALLIB)  -pthread

SOURCE_FILES = XYZ_Data.cc XYZ_Basics.cc XYZ_Helpers.cc  XYZ_Main.cc
OBJECT_FILES = XYZ_Data.o XYZ_Basics.o XYZ_Helpers.o XYZ_Main.o
HEADER_FILES = XYZ_Data.hh XYZ_Basics.hh XYZ_Helpers.hh  

xyz: $(OBJECT_FILES)
	g++ $(OBJECT_FILES) $(LINKOPTS) -o xyz

XYZ_Data.o: XYZ_Data.cc XYZ_Data.hh
	g++ -c $(COMPOPTS) XYZ_Data.cc

XYZ_Basics.o: XYZ_Basics.cc XYZ_Basics.hh XYZ_Data.hh
	g++ -c $(COMPOPTS) XYZ_Basics.cc

XYZ_Helpers.o: XYZ_Helpers.cc XYZ_Helpers.hh XYZ_Basics.hh XYZ_Data.hh
	g++ -c $(COMPOPTS) XYZ_Helpers.cc

XYZ_Main.o: XYZ_Main.cc XYZ_Helpers.hh XYZ_Basics.hh XYZ_Data.hh
	g++ -c $(COMPOPTS) XYZ_Main.cc

clean:
	rm -f $(OBJECT_FILES) xyz

