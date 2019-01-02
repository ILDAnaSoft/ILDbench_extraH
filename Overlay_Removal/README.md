# Minimal_Processor
It contains a minimal constituent of a Marlin processor, which can be used as a template to create your own processor.
It is much easier to use and change.

 - how to use
	- compile --> ./bin/action.sh
	- run     --> ./bin/run.sh  some_steering_file_name_in_the_xml_folder   (but do not include "xml" itself)
        - example  ./bin/run.sh higgs_vvqq.xml
    - create a new processor with this template  -> ./copy_new_Processor.sh  Minimal_Processor   new_processor_name
		- all names in this template are changed to your new name.
