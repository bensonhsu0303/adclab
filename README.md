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
  - setting the network interface
    - ip: `140.113.xxx.xxx`
    - netmask: `255.255.255.0`
    - dns: `140.113.6.2`
  - change chinese directory to english directory
  
  - install google
