#include <cstddef>
#include <iostream>

#include "VmeUsbBridge.h"
#include "HV.h"

#include "RealSetupManager.h"
#include "Interface.h"
#include "ConditionManager.h"

RealSetupManager::RealSetupManager(Interface& m_interface):
    m_interface(m_interface),
    m_controller(UsbController(NORMAL)),
    m_hvpmt(hv(&m_controller, 0xF0000, 2)) 
    { }

RealSetupManager::~RealSetupManager() {
    for (std::size_t id = 0; id < m_interface.getConditions().getNHVPMT(); id++) {
        m_hvpmt.setChState(0, id);
    }
}

bool RealSetupManager::setHVPMT(std::size_t id) { 
    int set_hv_value = m_interface.getConditions().getHVPMTSetValue(id);
    std::cout << "Setting the HV PMT number " << id << " to " << set_hv_value << "." << std::endl;

    return m_hvpmt.setChV(set_hv_value, id) == 1;
}

bool RealSetupManager::switchHVPMTON(std::size_t id) {
    std::cout << "Switching the HV PMT " << id << " ON..." << std::endl;
    
    return m_hvpmt.setChState(1, id) == 1;
}

bool RealSetupManager::switchHVPMTOFF(std::size_t id) {
    std::cout << "Switching the HV PMT " << id << " OFF..." << std::endl;
    
    return m_hvpmt.setChState(0, id) == 1;
}

std::vector< std::pair<double, double> > RealSetupManager::getHVPMTValue() {
    // FIXME Maybe we could have a function reading value of only one PM
    // Would require to modify Martin's library
    std::vector< std::pair<double, double> > hv_values;
    double ** temp_values = 0;
    temp_values = m_hvpmt.readValues(temp_values);
    for (std::size_t id = 0; id < m_interface.getConditions().getNHVPMT(); id++) {
        hv_values.push_back(std::make_pair(temp_values[id][0], temp_values[id][1]));
    }
    return hv_values;
}

//std::vector<double> RealSetupManager::getHVPMTState() {
//    // FIXME Not available yet in Martin's library
//    // Probably not needed as the HV value tells everything
//    std::vector<double> hv_values;
//    double ** temp_values = 0;
//    temp_values = m_hvpmt.readValues(temp_values);
//    for (std::size_t id = 0; id < m_interface.getConditions().getNHVPMT(); id++) {
//        std::cout << temp_values[id][0] << std::endl;
//        hv_values.push_back(temp_values[id][0]);
//    }
//    return hv_values;
//}
