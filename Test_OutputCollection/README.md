# Minimal_Processor
- Usage
This processor is used for testing the output collections from other processors, i.e. 
	- MCLevelClassify
	- MCLeptonTagging
	- MCPhotonFinder
	- PandoraPFOFinder 
	- Overlay_Removal 
	- Strange_Photon 

The examples are given in the xml folder.  Run them with
```
./bin/run.sh ***.xml 
```
After runing this processor, a root file will be generated in the resutls folder, it contains the basic variables of the input collections. 

- Setting
If you want to change the setting, just change the Input collection names and the output root file name.
This steering file can accept two MCPARTICLE and two RECONSTRUCTEDPARTICLE types and the same time. 
