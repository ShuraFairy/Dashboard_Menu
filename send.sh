#@echo off
echo Hello, I am try to copy new app into IC-12
echo request to remove application
cd build
ssh root@$1 "rm -f /home/root/IC-12_MVP_Dashboard"
echo start copy file ...
scp -oHostKeyAlgorithms=+ssh-rsa ./IC-12_MVP_Dashboard root@$1:
ssh root@$1 "chmod +x ./IC-12_MVP_Dashboard"
echo request to add access right for run a file
echo reboot ...
ssh -oHostKeyAlgorithms=+ssh-rsa root@$1 "/sbin/reboot"
