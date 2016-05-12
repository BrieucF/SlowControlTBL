//This file contains some instructions to doxygen. Please do not delete.

/*! \mainpage VME trigger documentation - calibration branch
 *
 * \section intro_sec Introduction
 *
 * This library was created in order to provide a flexible remote control system to a  <a href="https://dl.dropboxusercontent.com/u/33459975/cosmicTrigger/DocHardware.pdf">cosmic muon trigger system</a>  .
 * 
 * This tree includes the modifications of 2015 to calibrate and operate the setup.
 * 
 * The library has the following structure:
 *
 * \image html Lib.png
 * 
 * \li vmeController is a virtual class. It has the definition of a few basic i/o functions. It also contains the verbosity level.
 * 
 * \li UsbController is the instantiation of vmeController for a CAEN VME Controller.
 * 
 * \li vmeBoard is a virtual class containing the definition of a fiew read/write functions. It also contains the module's address and default AM/DW modes.
 * 
 * \li vmeBoard daughter classes: classes implementing the functions that can be used by the user. Each class is different and has different functionalities depending on the card.
 * 
 * \li CommonDef is a file containing functions and enum types that can be used by anyone.
 * 
 * To see a complete list of implemented boards, please go to the vmeBoard documention page.
 * 
 * \section dwl Download
 * 
 * <a href="https://github.com/md987/CosmicTrigger/tree/calibration">Github</a> 
 * 
 * 
 * \section install_sec Installation
 *
 * For the moment, the only bridge implemented is from CAEN. To use it, you should first install CAENVME's driver.
 * 
 * When the library was first created, the driver used were  <a href="https://dl.dropboxusercontent.com/u/33459975/cosmicTrigger/datasheets/CAENUSBdrvB-1.2.tgz">CAENUSBdrvB-1.2</a>  and  <a href="https://dl.dropboxusercontent.com/u/33459975/cosmicTrigger/datasheets/CAENVMELib-2.30.2.tgz">CAENVMELib-2.30.2</a>. These drivers worked on a 64bits distribution of linux. More drivers can be found on  <a href="http://www.caen.it/csite/CaenProd.jsp?idmod=417&parent=11">Caen's website</a>   * 
 * After installing those drivers, the library should be ready to use (yay!). A makefile is provided to compile a program named "main.cpp". The script "compile.py" will compile everything in the "script" folder and the output will be generated in the "out" folder.
 * 
 * \section concl_sec Example
 * 
 * A few examples are provided in the folder in /scripts. More examples can be found on the master branch.
 * 
 * \section contact Contact
 * 
 * For any further information, please feel free to contact me on <a href="https://github.com/md987/CosmicTrigger">github</a> or using by email.
 * 
 */
 /**
 *\example normalOp.cpp
 * This is example shows how the system can be used for a regular cosmic trigger system. 
 * 
 * Please note that the high voltage is not regulated in this program. Go to \ref Alim.cpp to see how it can be done.
 */ 
 /**
 *\example exampleTDC.cpp
 * This was how the tdc was used to analyse the phase between the clock and the trigger.
 */
 /**
 *\example Alim.cpp
 * This example shows you how the control of the High voltage was implemented.
 */ 
 /**
 *\example HvCalib.cpp
 * Shows how the scaler could be used to test the PMs at different voltages.
 */