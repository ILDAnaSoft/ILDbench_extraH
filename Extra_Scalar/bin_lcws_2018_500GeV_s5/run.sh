#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )"
cd ${DIR}/../xml_500_lcws_s5
if [[ -f $1 ]] ; then
	Marlin $1 


#Marlin template.xml \
#	global.LCIOInputFiles=$ \
#	MyHiggsProcessor.hmass= \


fi
