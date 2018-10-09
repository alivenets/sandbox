killall wpa_supplicant
ifconfig wlp58s0 down
ifconfig wlp58s0 up
wpa_supplicant -B -iwlp58s0 -c/etc/wpa_supplicant.conf -Dwext
dhclient wlp58s0
