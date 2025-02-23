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
#   This file contains the code to initialize the board
#------------------------------------------------------------------


changeFilePermissions() {

	if [ -e $1 ]; then 
		filepermission=$(stat -c %a $1)
	
		if [ $filepermission -ne $2 ] 
		then
		
			chmod $2 $1
			echo "[utopia][init] Modified File Permission to $2 for file - $1"
		fi
	else
		echo "[utopia][init] changeFilePermissions: file $1 doesn't exist"
	fi
}

echo "*******************************************************************"
echo "*                                                                  "
echo "* Copyright 2014 Cisco Systems, Inc. 				 "
echo "* Licensed under the Apache License, Version 2.0                   "
echo "*                                                                  "
echo "*******************************************************************"

source /etc/utopia/service.d/log_capture_path.sh

if [ -f /etc/device.properties ]
then
    source /etc/device.properties
fi

dmesg -n 5

TR69TLVFILE="/nvram/TLVData.bin"
REVERTFLAG="/nvram/reverted"
MAINT_START="/nvram/.FirmwareUpgradeStartTime"
MAINT_END="/nvram/.FirmwareUpgradeEndTime"

# determine the build type (debug or production)
if [ -f /etc/debug_build ] ; then
    debug_build=1
else
    debug_build=0
fi

firmware_name=`cat /version.txt | grep ^imagename: | cut -d ":" -f 2`
utc_time=`date -u`
echo "[$utc_time] [utopia][init] DEVICE_INIT:$firmware_name"
if [ -e "/usr/bin/onboarding_log" ]; then
    /usr/bin/onboarding_log "[utopia][init] DEVICE_INIT:$firmware_name"
fi

echo 4096 > /proc/sys/net/ipv6/neigh/default/gc_thresh1
echo 8192 > /proc/sys/net/ipv6/neigh/default/gc_thresh2
echo 8192 > /proc/sys/net/ipv6/neigh/default/gc_thresh3

#echo "[utopia][init] Loading drivers"
#MODULE_PATH=/lib/modules/`uname -r`/
#insmod $MODULE_PATH/drivers/net/erouter_ni.ko netdevname=erouter0

echo "Starting log module.."
/usr/sbin/log_start.sh

echo "[utopia][init] Starting udev.."

mkdir -p /tmp/cron

BUTTON_THRESHOLD=15
FACTORY_RESET_KEY=factory_reset
FACTORY_RESET_RGWIFI=y
FACTORY_RESET_WIFI=w
SYSCFG_MOUNT=/nvram
SYSCFG_TMP_LOCATION=/tmp
SYSCFG_FILE=$SYSCFG_TMP_LOCATION/syscfg.db
SYSCFG_BKUP_FILE=$SYSCFG_MOUNT/syscfg.db
SYSCFG_OLDBKUP_FILE=$SYSCFG_MOUNT/syscfg_bkup.db
SYSCFG_ENCRYPTED_PATH=/opt/secure/
SYSCFG_PERSISTENT_PATH=/opt/secure/data
SYSCFG_NEW_FILE=$SYSCFG_PERSISTENT_PATH/syscfg.db
SYSCFG_NEW_BKUP_FILE=$SYSCFG_PERSISTENT_PATH/syscfg_bkup.db
PSM_CUR_XML_CONFIG_FILE_NAME="$SYSCFG_TMP_LOCATION/bbhm_cur_cfg.xml"
PSM_BAK_XML_CONFIG_FILE_NAME="$SYSCFG_MOUNT/bbhm_bak_cfg.xml"
PSM_TMP_XML_CONFIG_FILE_NAME="$SYSCFG_MOUNT/bbhm_tmp_cfg.xml"
XDNS_DNSMASQ_SERVERS_CONFIG_FILE_NAME="$SYSCFG_MOUNT/dnsmasq_servers.conf"
FACTORY_RESET_REASON=false
FR_COUNT_FILE=/nvram/.factory_reset_count
HOTSPOT_BLOB="/nvram/hotspot_blob"

if [ -d $SYSCFG_ENCRYPTED_PATH ]; then
    if [ ! -d $SYSCFG_PERSISTENT_PATH ]; then
           echo "$SYSCFG_PERSISTENT_PATH path not available creating directory and touching $SYSCFG_NEW_FILE file"
           mkdir $SYSCFG_PERSISTENT_PATH
           touch $SYSCFG_NEW_FILE
    fi
fi

CheckAndReCreateDB()
{
	NVRAMFullStatus=`df -h $SYSCFG_MOUNT | grep "100%"`
	if [ "$NVRAMFullStatus" != "" ]; then
		if [ -f "/rdklogger/rdkbLogMonitor.sh" ]
		then
			  #Remove Old backup files if there	
			  sh /rdklogger/rdkbLogMonitor.sh "remove_old_logbackup"		 

		  	  #Re-create syscfg create again
			  syscfg_create -f $SYSCFG_FILE
			  syscfg_oldDB=$?
			  if [ $syscfg_oldDB -ne 0 ]; then
				  NVRAMFullStatus=`df -h $SYSCFG_MOUNT | grep "100%"`
				  if [ "$NVRAMFullStatus" != "" ]; then
					 echo "[utopia][init] NVRAM Full(100%) and below is the dump"
					 du -h $SYSCFG_MOUNT 
					 ls -al $SYSCFG_MOUNT	 
				  fi
			  fi 
		fi
	fi 
}

#SKYH4-5485: The admin user unable to login to GUI after flashing factory image.
if [ -s $SYSCFG_NEW_FILE ]; then
     echo "[utopia][init] Starting syscfg using file store ($SYSCFG_NEW_FILE)"
     cp $SYSCFG_NEW_FILE $SYSCFG_FILE 
     syscfg_create -f $SYSCFG_FILE
     if [ $? != 0 ]; then
          CheckAndReCreateDB
     fi          
else
     echo -n > $SYSCFG_FILE
     echo -n > $SYSCFG_NEW_FILE
   syscfg_create -f $SYSCFG_FILE
   if [ $? != 0 ]; then
	 CheckAndReCreateDB
   fi
   #>>zqiu
   echo "[utopia][init] need to reset wifi when ($SYSCFG_NEW_FILE) file is not available"
   syscfg set $FACTORY_RESET_KEY $FACTORY_RESET_WIFI
   #<<zqiu
   touch /nvram/.apply_partner_defaults
   # Put value 204 into networkresponse.txt file so that
   # all LAN services start with a configuration which will
   # redirect everything to Gateway IP.
   # This value again will be modified from network_response.sh 
   echo "[utopia][init] Echoing network response during Factory reset"
   echo 204 > /var/tmp/networkresponse.txt
fi

if [ -f $SYSCFG_OLDBKUP_FILE ];then
	rm -rf $SYSCFG_OLDBKUP_FILE
fi
if [ -f $SYSCFG_NEW_BKUP_FILE ]; then
	rm -rf $SYSCFG_NEW_BKUP_FILE
fi
if [ -f $SYSCFG_BKUP_FILE ]; then
        rm -rf $SYSCFG_BKUP_FILE
fi

SYSCFG_LAN_DOMAIN=`syscfg get lan_domain` 

if [ "$SYSCFG_LAN_DOMAIN" == "utopia.net" ]; then
   echo "[utopia][init] Setting lan domain to NULL"
   syscfg set lan_domain ""
   syscfg commit
fi

#Hard Factory reset from mount-fs.sh
if [ `cat /data/HFRES_UTOPIA` -eq 1 ]; then
   syscfg set $FACTORY_RESET_KEY $FACTORY_RESET_RGWIFI
   echo "0" > /data/HFRES_UTOPIA
fi

SYSCFG_FR_VAL="`syscfg get $FACTORY_RESET_KEY`"

if [ "x$FACTORY_RESET_RGWIFI" = "x$SYSCFG_FR_VAL" ]; then
   echo "[utopia][init] Performing factory reset"

rebReason=`syscfg get X_RDKCENTRAL-COM_LastRebootReason`   
rebCounter=`syscfg get X_RDKCENTRAL-COM_LastRebootCounter`
echo "[utopia][init] Current Reason:$rebReason Counter:$rebCounter"

SYSCFG_PARTNER_FR="`syscfg get PartnerID_FR`"
if [ "1" = "$SYSCFG_PARTNER_FR" ]; then
   echo_t "[utopia][init] Performing factory reset due to PartnerID change"
fi
# Remove log file first because it need get log file path from syscfg   
   /usr/sbin/log_handle.sh reset
   syscfg_destroy -f

# Remove syscfg and PSM storage files

#mark the factory reset flag 'on'
   FACTORY_RESET_REASON=true 
   rm -f /nvram/.keys/*
   rm -f /nvram/ble-enabled
   touch /nvram/.apply_partner_defaults
   rm -f /nvram/mesh_enabled
   rm -f $SYSCFG_BKUP_FILE
   rm -f $SYSCFG_FILE
   rm -f $SYSCFG_NEW_FILE
   rm -f $PSM_CUR_XML_CONFIG_FILE_NAME
   rm -f $PSM_BAK_XML_CONFIG_FILE_NAME
   rm -f $PSM_TMP_XML_CONFIG_FILE_NAME
   rm -f $TR69TLVFILE
   rm -f $REVERTFLAG
   rm -f $XDNS_DNSMASQ_SERVERS_CONFIG_FILE_NAME
   rm -f $MAINT_START
   rm -f $MAINT_END

   #remove Aker configuration
   rm -f /nvram/pcs.bin
   rm -f /nvram/pcs.bin.md5

   # Remove DHCP lease file
   rm -f /nvram/dnsmasq.leases
   rm -f /nvram/server-IfaceMgr.xml
   rm -f /nvram/server-AddrMgr.xml
   rm -f /nvram/server-CfgMgr.xml
   rm -f /nvram/server-TransMgr.xml
   rm -f /nvram/server-cache.xml
   rm -f /nvram/server-duid
   rm -f /nvram/partners_defaults.json 
   rm -f /nvram/bootstrap.json
   rm -f /opt/secure/RFC/tr181store.json
   if [ -f /nvram/.CMchange_reboot_count ];then
      rm -f /nvram/.CMchange_reboot_count
   fi
   if [ -f /etc/ONBOARD_LOGGING_ENABLE ]; then
   	# Remove onboard files
   	rm -f /nvram/.device_onboarded
	rm -f /nvram/DISABLE_ONBOARD_LOGGING
   	rm -rf /nvram2/onboardlogs
   fi
   if [ -f /nvram/ETH_WAN_PORT_RECLAIMED ];then
        rm -f /nvram/ETH_WAN_PORT_RECLAIMED
   fi
   if [ -d /nvram/lxy/ ]; then
	rm -rf /nvram/lxy
        rm -rf /nvram/certs
	/bin/sh -c '/usr/bin/lxyinit.sh /etc/lxybundl.bz2 /nvram/lxy'
   fi

    if [ -f "$HOTSPOT_BLOB" ];then
      rm -f "$HOTSPOT_BLOB"
   fi
  
   if [ -f /etc/WEBCONFIG_ENABLE ]; then
      #Remove webconfig_db.bin on factory reset on all RDKB platforms
      rm -f /nvram/webconfig_db.bin
   fi

   #Needs to increment factory reset count during PIN method
   #If GUI FR reboot reason will come as factory-reset and reboot counter should be 1. so we don't need to increment
   if [ "$rebCounter" != "1" ] ; then
      FR_COUNT=0
      if [ -f $FR_COUNT_FILE ]
      then
           FR_COUNT=`cat $FR_COUNT_FILE`
      fi
      FR_COUNT=$((FR_COUNT + 1))
      echo $FR_COUNT > $FR_COUNT_FILE

      echo "[utopia][init] Incremented Factory Reset Count after PIN method"
   fi

   echo "[utopia][init] Retarting syscfg using file store ($SYSCFG_NEW_FILE)"
   touch $SYSCFG_NEW_FILE
   touch $SYSCFG_FILE
   syscfg_create -f $SYSCFG_FILE
   syscfg_oldDB=$?
   if [ $syscfg_oldDB -ne 0 ];then
	 CheckAndReCreateDB
   fi
   
#>>zqiu
   # Put value 204 into networkresponse.txt file so that
   # all LAN services start with a configuration which will
   # redirect everything to Gateway IP.
   # This value again will be modified from network_response.sh 
   echo "[utopia][init] Echoing network response during Factory reset"
   echo 204 > /var/tmp/networkresponse.txt
    

elif [ "x$FACTORY_RESET_WIFI" = "x$SYSCFG_FR_VAL" ]; then
    echo "[utopia][init] Performing wifi reset"
    syscfg unset $FACTORY_RESET_KEY
#<<zqiu
fi
#echo "[utopia][init] Cleaning up vendor nvram"
# /etc/utopia/service.d/nvram_cleanup.sh

echo "*** HTTPS root certificate for TR69 ***"

if [ ! -f /etc/cacert.pem ]; then
	echo "HTTPS root certificate for TR69 is missing..."

fi
if [ -f /nvram/cacert.pem ]; then
        echo "Remove HTTPS root certificate for TR69 if available in NVRAM to prevent updating cert"
	rm -f /nvram/cacert.pem
fi

#CISCOXB3-6085:Removing current configuration from nvram as a part of PSM migration.
if [ -f /nvram/bbhm_cur_cfg.xml  ]; then
       mv /nvram/bbhm_cur_cfg.xml $PSM_CUR_XML_CONFIG_FILE_NAME
elif [ -f $PSM_BAK_XML_CONFIG_FILE_NAME  ]; then
        cp -f $PSM_BAK_XML_CONFIG_FILE_NAME $PSM_CUR_XML_CONFIG_FILE_NAME
fi

# update max number of msg in queue based on system maximum queue memory.
# This update will be used for presence detection feature.
MSG_SIZE_MAX=`cat /proc/sys/fs/mqueue/msgsize_max`
MSG_MAX_SYS=`ulimit -q`
TOT_MSG_MAX=50
if [ "x$MSG_MAX_SYS" = "x" ]; then
echo "ulimit cmd not avail assign mq msg_max :$TOT_MSG_MAX"
else
TOT_MSG_MAX=$((MSG_MAX_SYS/MSG_SIZE_MAX))
echo "mq msg_max :$TOT_MSG_MAX"
fi
echo $TOT_MSG_MAX > /proc/sys/fs/mqueue/msg_max


echo "[utopia][init] Starting sysevent subsystem"
#syseventd --threads 18
syseventd

# we want plugged in usb devices to propagate events to sysevent
#echo "[utopia][init] Late loading usb drivers"
#MODULE_PATH=/lib/modules/`uname -r`/
#insmod $MODULE_PATH/usbcore.ko
#insmod $MODULE_PATH/ehci-hcd.ko
#insmod $MODULE_PATH/scsi_mod.ko
#insmod $MODULE_PATH/sd_mod.ko
#insmod $MODULE_PATH/libusual.ko
#insmod $MODULE_PATH/usb-storage.ko
#insmod $MODULE_PATH/nls_cp437.ko
#insmod $MODULE_PATH/nls_iso8859-1.ko
#insmod $MODULE_PATH/fat.ko
#insmod $MODULE_PATH/vfat.ko

#ARRISXB6-1554: apply_system_defaults calls sysevent API. Logs showed binaries weren't fully started
attemptCounter=0

until [ -e "/tmp/syseventd_connection" ]; do
    
    if [ $attemptCounter -lt 3 ]
    then
       sleep 2
       let "attemptCounter++"
    else
       break
    fi
done

echo "[utopia][init] Setting any unset system values to default"
apply_system_defaults
#ARRISXB6-2998
changeFilePermissions $SYSCFG_BKUP_FILE 400
changeFilePermissions $SYSCFG_NEW_FILE 400
echo "[utopia][init] SEC: Syscfg stored in $SYSCFG_NEW_FILE"
syscfg unset UpdateNvram
syscfg commit
if [ -s /nvram/.secure_mount_failure ]; then
     if [ `cat /nvram/.secure_mount_failure` -gt 3 ]; then
           echo "[utopia][init] Device needs to be replaced as it is unable to recover /opt/secure mount issue"
           rm -f /nvram/.secure_mount_failure
     fi
fi

eth_wan_enable=`cat /nvram/bbhm_cur_cfg.xml | grep dmsb.wanagent.if.2.Enable | cut -d ">" -f 2 | cut -d "<" -f 1`
if [ "$eth_wan_enable" == "FALSE" ]
then
    touch /nvram/ETH_WAN_PORT_RECLAIMED
fi

# Get the syscfg value which indicates whether unit is activated or not.
# This value is set from network_response.sh based on the return code received.
activated=`syscfg get unit_activated`
echo "[utopia][init] Value of unit_activated got is : $activated"
if [ "$activated" = "1" ]
then
    echo "[utopia][init] Echoing network response during Reboot"
    echo 204 > /var/tmp/networkresponse.txt
fi 

echo "[utopia][init] Applying iptables settings"

lan_ifname=`syscfg get lan_ifname`
cmdiag_ifname=`syscfg get cmdiag_ifname`
ecm_wan_ifname=`syscfg get ecm_wan_ifname`
wan_ifname=`sysevent get wan_ifname`

#disable telnet / ssh ports
iptables -A INPUT -i $lan_ifname -p tcp --dport 23 -j DROP
iptables -A INPUT -i $lan_ifname -p tcp --dport 22 -j DROP
iptables -A INPUT -i $cmdiag_ifname -p tcp --dport 23 -j DROP
iptables -A INPUT -i $cmdiag_ifname -p tcp --dport 22 -j DROP

ip6tables -A INPUT -i $lan_ifname -p tcp --dport 23 -j DROP
ip6tables -A INPUT -i $lan_ifname -p tcp --dport 22 -j DROP
ip6tables -A INPUT -i $cmdiag_ifname -p tcp --dport 23 -j DROP
ip6tables -A INPUT -i $cmdiag_ifname -p tcp --dport 22 -j DROP

#protect from IPv6 NS flooding
ip6tables -t mangle -A PREROUTING -i $ecm_wan_ifname -d ff00::/8 -p ipv6-icmp -m icmp6 --icmpv6-type 135 -j DROP
ip6tables -t mangle -A PREROUTING -i $wan_ifname -d ff00::/8 -p ipv6-icmp -m icmp6 --icmpv6-type 135 -j DROP

echo "[utopia][init] Processing registration"
INIT_DIR=/etc/utopia/registration.d
# run all executables in the sysevent registration directory
# echo "[utopia][init] Running registration using $INIT_DIR"
execute_dir $INIT_DIR&

#Get reboot reason from driver
LastRebootReason=`cat /proc/skyrbd`
echo "[utopia][init] Detected last reboot reason from driver as $LastRebootReason"

#Once you read then clear the driver file
echo "" > /proc/skyrbd

if [ "$FACTORY_RESET_REASON" = "true" ]; then
   echo "[utopia][init] Detected last reboot reason as factory-reset"

   syscfg set X_RDKCENTRAL-COM_LastRebootReason "factory-reset"
   syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
else
#Check last reboot reasons
case "$LastRebootReason" in
    PCIEReset | OOPS | BAD | ABORT | POOM | BUG | BADS | BABORT | PANIC | POOM | OOM )
      echo "[utopia][init] Setting last reboot reason as $LastRebootReason"
      syscfg set X_RDKCENTRAL-COM_LastRebootReason $LastRebootReason
      syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
   ;;

   PinReset)
      echo "[utopia][init] Setting last reboot reason as pin-reset"
      syscfg set X_RDKCENTRAL-COM_LastRebootReason "pin-reset"
      syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
   ;;

   PORReset)
      echo "[utopia][init] Setting last reboot reason as HW or Power-On Reset"
      syscfg set X_RDKCENTRAL-COM_LastRebootReason "HW or Power-On Reset"
      syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
   ;;

   PANICBootUp)
      echo "[utopia][init] Setting last reboot reason as Panic-On-BootUp"
      syscfg set X_RDKCENTRAL-COM_LastRebootReason "Panic-On-BootUp"
      syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
   ;;

   *)
   if [ "$LastRebootReason" = "Reboot" ] || [ "$LastRebootReason" = "SWReset" ] ; then
      #extra handling for reason
      if [ -f /nvram/restore_reboot ];then
         echo "[utopia][init] Setting last reboot reason as restore-reboot"
         syscfg set X_RDKCENTRAL-COM_LastRebootReason "restore-reboot"
         syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
         rm -f /nvram/restore_reboot
         rm -f /nvram/syscfg.db.prev
      elif [ -f /tmp/.secure_mount_flag ]; then
             echo "[utopia][init] Detected last reboot reason as secure-mount failure"
             syscfg set X_RDKCENTRAL-COM_LastRebootReason "secure-mount-failure"
             syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
             rm -f /tmp/.secure_mount_flag
      else
         rebootCounter=`syscfg get X_RDKCENTRAL-COM_LastRebootCounter`
         echo "[utopia][init] Previous rebootCounter:$rebootCounter"
         if [ "$rebootCounter" != "1" ] ; then
             if [ "$LastRebootReason" = "Reboot" ] ; then
                echo "[utopia][init] Detected last reboot reason as reboot-cmd"
                syscfg set X_RDKCENTRAL-COM_LastRebootReason "reboot-cmd"
                syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
             fi
              
             if [ "$LastRebootReason" = "SWReset" ] ; then
                echo "[utopia][init] Detected last reboot reason as SWReset"
                syscfg set X_RDKCENTRAL-COM_LastRebootReason "SWReset"
                syscfg set X_RDKCENTRAL-COM_LastRebootCounter "1"
             fi
         fi
      fi
   else
      echo "[utopia][init] Setting last reboot reason as unknown"
           syscfg set X_RDKCENTRAL-COM_LastRebootReason "unknown"
   fi
   ;;

esac
fi

#Needs to commit DB value after set
syscfg commit

#Onboarding log needs to set
if [ -e "/usr/bin/onboarding_log" ]; then
rebootReason=`syscfg get X_RDKCENTRAL-COM_LastRebootReason`
  /usr/bin/onboarding_log "[utopia][init] Detected last reboot reason as $rebootReason"
fi

#SKYH4-2611 After FR boot-up needs to check default IP and lan ip is same or not
if [ "$FACTORY_RESET_REASON" = "true" ]; then
   #brlan0 v4 address check
   LAN_IF_NAME=`syscfg get lan_ifname`
   LAN_CURRENT_IP=`ifconfig $LAN_IF_NAME | grep "inet addr" | awk '/inet/{print $2}'  | cut -f2 -d:`
   LAN_DEFAULT_IP=`cat /usr/ccsp/config/bbhm_def_cfg.xml | grep dmsb.l3net.4.V4Addr | cut -d ">" -f 2 | cut -d "<" -f 1`

   echo "[utopia][init] After FR - LAN_IF_NAME:$LAN_IF_NAME Current LAN_IP:$LAN_CURRENT_IP Default LAN_IP:$LAN_DEFAULT_IP"

   if [ "$LAN_IF_NAME" != "" ] && [ "$LAN_CURRENT_IP" != "" ] && [ "$LAN_DEFAULT_IP" != "" ] && [ "$LAN_DEFAULT_IP" != "$LAN_CURRENT_IP" ]; then
       echo "[utopia][init] Current and Default LAN IP mismatch. so needs to change LAN IP as $LAN_DEFAULT_IP"

       LAN_DEFAULT_NETMASK=`cat /usr/ccsp/config/bbhm_def_cfg.xml | grep dmsb.l3net.4.V4SubnetMask | cut -d ">" -f 2 | cut -d "<" -f 1`
       ifconfig $LAN_IF_NAME down
       ifconfig $LAN_IF_NAME $LAN_DEFAULT_IP netmask $LAN_DEFAULT_NETMASK
       ifconfig $LAN_IF_NAME up
   fi
fi

#RDKB-24155 - TLVData.bin should not be used in EWAN mode
eth_wan_enable=`syscfg get eth_wan_enabled`
if [ "$eth_wan_enable" = "true" ] && [ -f $TR69TLVFILE ]; then
  rm -f $TR69TLVFILE
fi
      
#RDKB-15951 Bringup the Mesh Bhaul network
echo "[utopia][init] Mesh Bhaul bridge creation"
sysevent set meshbhaul-setup 10

echo "[utopia][init] completed creating utopia_inited flag"
touch /tmp/utopia_inited
