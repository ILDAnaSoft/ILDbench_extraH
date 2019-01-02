# MyProcessor
MyProcessor for new higgs analyse

## Usage
  - In order to use this processor, one should first download [ToolSet_ILCSOFT](http://github.com/YancyW/ToolSet_ILCSOFT). Then edit CMakeList to link ToolSet package
  - Then use the script in the bin_2018 to run the processor
     - ./bin_2018/active.sh   # This will compile the processor 
     - ./bin_2018/run.sh steering_file_name_in_the_xml_isr_folder  # This will run the processor and generate a root file with some observables.
     - ./bin_2018/run_all.sh code no # run for all mass benchmark points, before doing this, please change the output folder to your own path.
     - ./bin_2018/run_all.sh code submit # run for all mass benchmark points with DESY HTCondor, before doing this, please download [HTCondor script](https://github.com/beyerja/RIOT-RunItOnhTcondor-) and set the correct path for
       HTCondor in bin_2018/channel.sh. Or one can change wo his own submit scripts.
     - when a root file is generated, it can be further analysed by [BASDA](http://github.com/YancyW/BASDA) to get exclusion limits and all plots.
     - The configure files for BASDA is in the control_basda folder, put it into BASDA folder, and run with ./BASDA contron_basda/path.dat

# How to read the code
	- All processors are based on the same template --> "Minimal_Processor", the readers could first read this processor for understanding the structure of my processors.
	- In order to make the code concisely and easier to read, it uses many functions provided in the ToolSet library. Most of the functions can be understood by their names. The readers can go to ToolSet doc for further checking.
	- In this package, the Extra_Scalar is the main processor, it uses the collections generated from other processors, the structure is in the following figures.
        ![Image of main structure](http://github.com/ILDAnaSoft/ILDbench_extraH/raw/master/doc/main_structure.png)
