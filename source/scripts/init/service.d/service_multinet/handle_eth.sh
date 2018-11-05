#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2015 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
# 
#   Licensed under the Apache License, Version 2.0 (the \"License\");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an \"AS IS\" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#######################################################################

#------------------------------------------------------------------
# ENTRY
#------------------------------------------------------------------

TYPE=Eth

#service_init
case "$1" in
#  Synchronous calls
    #Args: netid, members
    create)
        echo ${TYPE}_READY=\"$3\"
        ;;
    destroy)
        service_stop
        ;;
    #Args: netid, netvid, members
    addVlan)
 #     if [ x"unknown" != x"$SYSEVENT_current_hsd_mode" ]; then
        
 #     fi
      ;;
    #Args: netid, netvid, members
    delVlan)
    
    ;;
      
#  Sysevent calls
    *)
        exit 3
        ;;
esac
