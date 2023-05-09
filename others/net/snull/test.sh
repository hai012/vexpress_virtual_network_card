# modify /etc/networks
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
snullnet0   192.168.0.0
snullnet1   192.168.1.0
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#modify /etc/hosts
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
192.168.0.1 local0
192.168.0.2 remote0
192.168.1.2 local1
192.168.1.1 remote1
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#Test Snull modules
sudo dmesg -c
sudo ./snull_load
sudo dmesg -c
ip a
sudo ifconfig sn0 local0
sudo ifconfig sn1 local1
ifconfig -a

ping -c 2 remote0
ping -c 2 remote1

sudo ./snull_unload
sudo dmesg -c
