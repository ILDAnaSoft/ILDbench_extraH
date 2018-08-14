# MyProcessor
MyProcessor for new higgs analyse

## Usage
  - In order to use this processor, one should first download [ToolSet_ILCSOFT](http://github.com/YancyW/ToolSet_ILCSOFT). Then edit CMakeList to link ToolSet package
  - Then use the script in the bin_2018 to run the processor
     - ./bin_2018/active.sh   # This will compile the processor 
     - ./bin_2018/run.sh steering_file_name_in_the_xml_isr_folder  # This will run the processor and generate a root file with some observables.
     - when a root file is generated, it can be further analysed by [BASDA](http://github.com/YancyW/BASDA) to get exclusion limits and all plots.
     - The configure files for BASDA is in the control_basda folder, put it into BASDA folder, and run with ./BASDA contron_basda/path.dat
 
     
