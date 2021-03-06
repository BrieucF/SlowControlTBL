#include <iostream>
#include <string>
#include <chrono>
#include <atomic>
#include <exception>

#include <json/writer.h>

#include "LoggingManager.h"
#include "Interface.h"
#include "Utils.h"

LoggingManager::LoggingManager(Interface& m_interface, uint32_t m_continuous_log_time, uint32_t m_interface_refresh_time): 
    m_interface(m_interface),
    m_conditions(m_interface.getConditions()),
    is_running(true),
    m_continuous_log_time(m_continuous_log_time),
    m_interface_refresh_time(m_interface_refresh_time),
    m_condition_json_list(Json::arrayValue)
{
    std::cout << "Creating LoggingManager." << std::endl;
}

void LoggingManager::run(){
    
    std::cout << "Starting logger." << std::endl;
    
    initConditionManagerLog();
    initContinuousLog();
    
    auto logging_start = m_clock::now();
    auto interface_start = m_clock::now();
    
    while(is_running){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        auto interface_stop = m_clock::now();
        std::chrono::duration<double> interface_delta = interface_stop - interface_start;
        if(std::chrono::duration_cast<std::chrono::milliseconds>(interface_delta).count() >= m_interface_refresh_time){
            interface_start = interface_stop;
            
            m_interface.notifyUpdate();
        } 
        
        auto logging_stop = m_clock::now();
        std::chrono::duration<double> logging_delta = logging_stop - logging_start;
        if(std::chrono::duration_cast<std::chrono::milliseconds>(logging_delta).count() >= m_continuous_log_time){
            logging_start = logging_stop;

            updateContinuousLog(logging_stop);
        }
    }

    std::cout << "Stopping logger." << std::endl;
    finalizeConditionManagerLog();
    finalizeContinuousLog();
}

void LoggingManager::stop() {
    std::cout << "LoggingManager was asked to stop." << std::endl;
    is_running = false;
}


//--- Continuous logging

void LoggingManager::initContinuousLog() {
    m_continuous_log.open("cont_log.csv"); // FIXME add run number
    if(!m_continuous_log.is_open())
        throw std::ios_base::failure("Could not open file cont_log.csv");
    m_continuous_log << "timestamp,hv_0" << std::endl;
}
    
void LoggingManager::updateContinuousLog(m_clock::time_point log_time) {
    int counter = m_conditions.getCounter();
    std::vector<int> hv = m_conditions.getHVPMTSetValues();
    m_continuous_log << log_time.time_since_epoch().count() << "," << hv[0] << std::endl;
    std::cout << timeToString<m_clock>(log_time) << " -- HV = " << hv[0] << std::endl;
}

void LoggingManager::finalizeContinuousLog() {
    m_continuous_log.close();
}

//--- ConditionManager logging

void LoggingManager::initConditionManagerLog() {
    auto start_time = m_clock::now();
    m_condition_json_root["start_time_human"] = timeToString<m_clock>(start_time);
    m_condition_json_root["start_time"] = timeToJson<m_clock>(start_time); 
    updateConditionManagerLog(start_time, true);
}

void LoggingManager::updateConditionManagerLog(m_clock::time_point log_time, bool first_time) {
    std::cout << "Updating conditions log" << std::endl;

    m_condition_json_root["conditions_changed"] = !first_time;
    
    Json::Value this_condition;
    
    Json::Value hv_values;
    hv_values["hv_0_set"] = m_conditions.getHVPMTSetValues()[0];
    this_condition["hv_values"] = hv_values;
    
    this_condition["time"] = timeToJson<m_clock>(log_time); 
    
    m_condition_json_list.append(this_condition);
}

void LoggingManager::finalizeConditionManagerLog() {
    auto stop_time = m_clock::now();
    m_condition_json_root["stop_time_human"] = timeToString<m_clock>(stop_time);
    m_condition_json_root["stop_time"] = timeToJson<m_clock>(stop_time); 
    m_condition_json_root["conditions"] = m_condition_json_list;

    Json::StyledWriter m_writer;

    std::ofstream file_stream;
    file_stream.open("cond_log.json"); // FIXME add run number
    if(!file_stream.is_open())
        throw std::ios_base::failure("Could not open file cond_log.json");
    file_stream << m_writer.write(m_condition_json_root);
    file_stream.close();
}    
