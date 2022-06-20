/*
 * Copyright 2021 CNRS-UM LIRMM, CNRS-AIST JRL
 */

#pragma once

#include <mc_control/GlobalPlugin.h>
#include <openvr/openvr.h>
#include <openvr/openvr_capi.h>
#include "VivePluginData.h"
#include <thread>
#include <mutex>

namespace mc_vive_plugin
{

struct VivePlugin : public mc_control::GlobalPlugin
{
  void init(mc_control::MCGlobalController & controller, const mc_rtc::Configuration & config) override;

  void reset(mc_control::MCGlobalController & controller) override;

  void before(mc_control::MCGlobalController &) override;

  void after(mc_control::MCGlobalController & controller) override;

  mc_control::GlobalPlugin::GlobalPluginConfiguration configuration() override;

  ~VivePlugin() override;

private:
  //Datastore
  std::thread th_;
  std::mutex mut_;
  bool running_ = true;
  std::vector<double> calc_acc; 

  //Vive Tracking Retargeting
  ViveData data_;
  ViveData rotdata_;
  ViveData button_;
  ViveData data_vel_; 
  ViveData isTracked; 
};

} // namespace mc_vive_plugin
