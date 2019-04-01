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
    - sudo vi `/etc/selinux/config`
    - SELINUX=disabled
    - sudo reboot
  - copy welcome script
    - sudo mkdir -p `/usr/lib/lab-script`
    - sudo vi `/usr/lib/lab-script/mkmotd`
    - sudo vi `/usr/lib/lab-script/labShell`
    - sudo chown adc `/usr/lib/lab-script/mkmotd`
    - sudo chgrp adc `/usr/lib/lab-script/mkmotd`
    - sudo chmod 755 `/usr/lib/lab-script/mkmotd`
    - sudo chown adc `/usr/lib/lab-script/labShell`
    - sudo chgrp adc `/usr/lib/lab-script/labShell`
    - sudo chmod 755 `/usr/lib/lab-script/labShell`
  - install figlet
    - sudo yum install epel-release
    - sudo yum install figlet
  - install ssh server
    - sudo yum install openssh openssh-server
    - sudo vi `/etc/ssh/sshd_config`
    - sudo service sshd restart
  
## Autofs
  - sudo yum install autofs*
  - sudo yum install nfs-utils nfs-utils-lib
  - sudo vim /etc/auto.syno
  - sudo vim /etc/auto.master
  - sudo service autofs restart
  - sudo chkconfig autofs on
  - cd /net/lab/ : `success`

## Ldap client
  - [reference](https://sites.google.com/a/cnsrl.cycu.edu.tw/da-shu-bi-ji/qi-ta/liyongsynologynasdangzuoldapnfsserverjianzhibuzhou?fbclid=IwAR3yzTCq-af3e2Hk-3K2pDD0zPnYfakVjHW6uikx318Ky5npqYdSSyl8yFc)
  - sudo yum install {openldap,openldap-clients,nss-pam-ldapd}
  - setup / Authentication configuration
    - authentication setup
      - 緩衝區資訊
      - 使用 LDAP
      - 使用 LDAP 認證
      - 使用 TLS
      - ldap://140.113.xxx.xxx
      - dc=xxx,dc=xxx,dc=xxx,dc=xxx
  - 匯出憑證
    - cd /etc/openldap/cacerts/
    - sudo cp ~/Downloads/cert.pem cert.pem
    - sudo cp ~/Downloads/syno-ca-cert.pem syno-ca-cert.pem
  - sudo vi `/etc/openldap/ldap.conf`

## auth config
  - [reference](https://www.certdepot.net/ldap-client-configuration-authconfig/)
  - sudo authconfig --enableforcelegacy --update
  - authconfig --enableldap --enableldapauth --ldapserver="140.113.147.69" --ldapbasedn="dc=adclab,dc=nctu,dc=edu,dc=tw" --update
  - authconfig --enableldaptls --update
  
## nsswitch.conf
  - sudo vim `/etc/nsswitch.conf`

## nslcd config
  - sudo vim `/etc/nslcd.conf`
  - sudo service nslcd start
  - sudo systemctl enable nslcd
  
## `csh.cshrc`
  - sudo vim `/etc/csh.cshrc`
  
## default shell
  - chsh : `/bin/tcsh`
