# adclab

## Create bootable usb:
  - Download Centos 7 1810 from [here](http://centos.cs.nctu.edu.tw/7.6.1810/isos/x86_64/CentOS-7-x86_64-DVD-1810.iso)
  - use [rufus](https://github.com/pbatard/rufus/releases/download/v3.5/rufus-3.5.exe) to make a bootable usb

## Install the system:
  - select `gnome desktop`(select all)
  - create `sudo user`, and assign administration permission.
  
## preparation step:
  - install the graphic driver for graphic card `WX 2100`
    - Download from [here](https://www.amd.com/en/support/kb/release-notes/rn-rad-lin-18-50-unified?fbclid=IwAR08JQ2wFH7q1R56RMYwth0GXeb2yf5A1GzaFg8YXy4k36Vr2UppQkeJAPc)
    - driver installation [step](https://www.amd.com/en/support/kb/release-notes/amdgpu-installation?fbclid=IwAR2NtjI4khr9AIba_e88YGInfTBS70fNDmssxubDpgJCPkv5b_uwpXrrnoY)
    - 要載 [`amdgpu-pro-preinstall.sh`](https://www2.ati.com/drivers/linux/17.50/amdgpu-pro-preinstall.sh)
    - 裝到 `./amdgpu-install -y` 這個步驟就好
    - reboot
  - setting the network interface
    - ip: `140.113.xxx.xxx`
    - netmask: `255.255.255.0`
    - dns: `140.113.6.2`
  - change `chinese directory` to `english directory`
    - export LANG=en_US
    - xdg-user-dirs-gtk-update : `update new name`
    - export LANG=zh_CN.UTF-8
    - xdg-user-dirs-gtk-update : `keep old name`
  - install google
    - sudo vi /etc/yum.repos.d/google.repo
    - sudo yum -y install google-chrome-stable

## ssh server install
  - turn off SELinux
    - xxx
  - copy welcome script
    - sudo mkdir -p /usr/lib/lab-script
    - vi /usr/lib/lab-script/mkmotd
    - vi /usr/lib/lab-script/labShell
    - sudo chown adc /usr/lib/lab-script/mkmotd
    - sudo chgrp adc /usr/lib/lab-script/mkmotd
    - sudo chmod 755 /usr/lib/lab-script/mkmotd
    - sudo chown adc /usr/lib/lab-script/labShell
    - sudo chgrp adc /usr/lib/lab-script/labShell
    - sudo chmod 755 /usr/lib/lab-script/labShell
  - install ssh server
    - sudo yum install openssh openssh-server
    - sudo vi /etc/ssh/sshd_config
    - sudo service sshd restart
  
