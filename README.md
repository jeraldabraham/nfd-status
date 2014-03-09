NFD Status Information (nfd-status)
=======================================

This tool is designed to retrieve status information of the nfd application
running on the localhost machine. It leverages NFD Face Status protocol and
NFD FIB enumeration protocol to retrieve details about the faces and FIB 
table. Additionally, it retrieve NFD version information.

MORE CONTENT TO BE ADDED

-----------------------------------------------------

## 1. Compile And Installation Instructions: ##

    git clone git://github.com/jeraldabraham/nfd-status nfd-status
    cd nfd-status
    ./waf configure 
    ./waf
    sudo ./waf install

## 2. Tool Run Instructions & Command Line Options: ##

Usage: build/nfd-status [options]
Shows NFD Status Information
Displays Version Information (NFD Version, Start Timestamp, Current Timestamp).
Face Status Information via NFD Face Status Protocol (FaceID, URI, Counters).
FIB Information via NFD FIB Enumeration Protocol (Prefix, Nexthop).
If no options are provided, all information is retrieved.
  [-v] - retrieve version information
  [-f] - retrieve face status information
  [-b] - retrieve FIB information
  [-h] - print help and exit

## 3. Sample Run Instructions ##

* Use command line options shown above to adjust traffic configuration.

MORE CONTENT TO BE ADDED

