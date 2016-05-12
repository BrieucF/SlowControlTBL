# SlowControlTBL
Slow control interface for Test Beam at Louvain

## Install
- Prerequisites: libncurses, libqt5, cmake >= 2.8, pthread, libjsoncpp
- Initialise git repository: `git clone --recursive https://github.com/swertz/SlowControlTBL ; cd SlowControlTBL`
- Get [CAEN library](http://www.caen.it/jsp/Template2/CaenProd.jsp?parent=38&idmod=689&downloadSoftwareFileId=11059), install (admin rights needed): `cd lib; sh install_x64`
- Compile Martin's library: `cd CosmicTrigger; make`
- Build: `mkdir build; cd build; cmake ..; make -j 4` 
- NB : if on cmslab computer, use cmake28 instead of cmake
