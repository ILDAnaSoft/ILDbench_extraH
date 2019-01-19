# Minimal_Processor
It contains a minimal constituent of a Marlin processor, which can be used as a template to create your own processor.
It is much easier to use and change.

 - how to use
	- install --> First, you need to install ToolSet package, which you can find that in my repositories. Then change the "ToolSet" path to your ToolSet directory in the CMakelist.txt.
	- compile --> ./bin/action.sh
	- run     --> ./bin/run.sh  some_steering_file_name_in_the_xml_folder   (but do not include "xml" itself)
        - example  ./bin/run.sh higgs_vvqq.xml
    - create a new processor with this template  -> ./copy_new_Processor.sh  Minimal_Processor   new_processor_name
		- all names in this template are changed to your new name.
 - notice:
    - when changing xml, for the new production, you don't need the detector gear file. Please delete that.
    - when changing xml, for the new production, the MCParticle collection name is different. Please change to "MCParticle", instead of "MCParticlesSkimmed".
