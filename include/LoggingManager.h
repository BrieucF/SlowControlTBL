#pragma once

#include <atomic>
#include <memory>
#include <fstream>

#include <json/value.h>

#include "ConditionManager.h"

// Forward declaration
class Interface;

/*
 * LoggingManager: run by the background thread, manages all the logging: conditions (json), continuous (csv, root)
 */
class LoggingManager {
  public:

      LoggingManager(Interface& m_interface, uint32_t m_continuous_log_time = 1000, uint32_t m_interface_refresh_time = 250);
      ~LoggingManager() {};

      void run();
      void stop();
  
  private:
        
      using m_clock = std::chrono::system_clock;

      void initConditionManagerLog();
      void updateConditionManagerLog(m_clock::time_point log_time, bool first_time = false);
      void finalizeConditionManagerLog();
      
      void initContinuousLog();
      void updateContinuousLog(m_clock::time_point log_time);
      void finalizeContinuousLog();

      Interface& m_interface;
      ConditionManager& m_conditions;
      std::atomic<bool> is_running;

      uint32_t m_continuous_log_time;
      uint32_t m_interface_refresh_time;

      Json::Value m_condition_json_root;
      Json::Value m_condition_json_list;

      std::ofstream m_continuous_log;
};
 
