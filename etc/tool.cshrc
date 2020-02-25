# /etc/cshrc

source /usr/cad/synopsys/CIC/hspice.cshrc
source /usr/cad/synopsys/CIC/cosmos_scope.cshrc
source /usr/cad/synopsys/CIC/customexplorer.cshrc
source /usr/cad/synopsys/CIC/laker.cshrc
source /usr/cad/synopsys/CIC/adp.cshrc
source /usr/cad/cadence/CIC/ic.cshrc
source /usr/cad/cadence/CIC/ic_51.41.151.cshrc
source /usr/cad/cadence/CIC/ic_06.17.709.cshrc
setenv PATH {$PATH}:/usr/sbin:/opt/sublime_text:/usr/local/MATLAB/R2018b/bin
setenv META_QUEUE 1
setenv W3264_NO_HOST_CHECK 1

# Analog FastSpice
setenv AFS_ROOT /var/tmp/amsv/amsv
setenv PATH {$PATH}:$AFS_ROOT/bin
setenv MGLS_LICENSE_FILE 1717@lscic

# auCore.cxt patch
setenv CDS_AUTO_64BIT NONE
