#include "VivePlugin.h"
#include "VivePluginData.h"
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <mc_control/GlobalPluginMacros.h>


namespace mc_vive_plugin
{

ViveTracking::~ViveTracking() {
  if (vr_pointer != NULL) {
      // VR Shutdown: https://github.com/ValveSoftware/openvr/wiki/API-Documentation#initialization-and-cleanup
      vr::VR_Shutdown();
      vr_pointer = NULL;
  }
}

// Constructor for the PoseTracking object
ViveTracking::ViveTracking() {
    vr::EVRInitError eError {vr::VRInitError_None};
    vr_pointer = VR_Init(&eError, vr::VRApplication_Background);
    if (eError != vr::VRInitError_None) {
        vr_pointer = NULL;
        std::cout << "Unable to init VR runtime: " << VR_GetVRInitErrorAsEnglishDescription(eError) << "\n";
        exit(EXIT_FAILURE);
    }
}

vr::HmdVector3_t ViveTracking::GetPosition(vr::HmdMatrix34_t matrix) {
    vr::HmdVector3_t vectorPos;
    vectorPos.v[0] = matrix.m[0][3];
    vectorPos.v[1] = matrix.m[1][3];
    vectorPos.v[2] = matrix.m[2][3];
    return vectorPos;
}

vr::HmdQuaternion_t ViveTracking::GetRotation(vr::HmdMatrix34_t matrix) {
    vr::HmdQuaternion_t q;
    q.w = sqrt(fmax(0, 1 + matrix.m[0][0] + matrix.m[1][1] + matrix.m[2][2]))/ 2;
    q.x = sqrt(fmax(0, 1 + matrix.m[0][0] - matrix.m[1][1] - matrix.m[2][2]))/ 2;
    q.y = sqrt(fmax(0, 1 - matrix.m[0][0] + matrix.m[1][1] - matrix.m[2][2]))/ 2;
    q.z = sqrt(fmax(0, 1 - matrix.m[0][0] - matrix.m[1][1] + matrix.m[2][2]))/ 2;
    q.x = copysign(q.x, matrix.m[2][1] - matrix.m[1][2]);
    q.y = copysign(q.y, matrix.m[0][2] - matrix.m[2][0]);
    q.z = copysign(q.z, matrix.m[1][0] - matrix.m[0][1]);
    return q;
}

ViveData_Vector ViveTracking::getPoseData() {
  ViveData_Vector tracking;

  for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++) {

    if (!vr_pointer->IsTrackedDeviceConnected(unDevice))
        continue;

    vr::VRControllerState_t state;

    if (vr_pointer->GetControllerState(unDevice, &state, sizeof(state))) {

      vr::TrackedDevicePose_t trackedControllerPose;
      vr::TrackedDevicePose_t trackedDevicePose;
      vr::VRControllerState_t controllerState;
      vr::HmdVector3_t position; vr::HmdQuaternion_t quaternion;  vr::HmdVector3_t velocity; vr::HmdVector3_t angularvelocity;
      vr::HmdMatrix34_t matrix_rotation;
      vr::ETrackedDeviceClass trackedDeviceClass = vr_pointer->GetTrackedDeviceClass(unDevice);
      auto trackedControllerRole = vr::VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDevice);
      double whichBody = 0;

      // TRACKERS
      if(trackedDeviceClass==vr::ETrackedDeviceClass::TrackedDeviceClass_GenericTracker) {
        vr_pointer->GetControllerStateWithPose(vr::TrackingUniverseStanding, unDevice,
                                              &controllerState, sizeof(controllerState),
                                              &trackedControllerPose);
        char serialNumber[13];
        vr::VRSystem()->GetStringTrackedDeviceProperty(unDevice, vr::Prop_SerialNumber_String, serialNumber, sizeof(serialNumber));

        position = GetPosition(trackedControllerPose.mDeviceToAbsoluteTracking);
        quaternion = GetRotation(trackedControllerPose.mDeviceToAbsoluteTracking);
        matrix_rotation = trackedControllerPose.mDeviceToAbsoluteTracking;
        velocity = trackedControllerPose.vVelocity;
        angularvelocity = trackedControllerPose.vAngularVelocity;
        time(&tracking.timer); // get current time;                          
        int RightFoot = strcmp(serialNumber, "LHR-D756B287");  // Right Foot tracker id
        int LeftFoot = strcmp(serialNumber, "LHR-659508D3");  // Left Foot tracker id
        int RightArm = strcmp(serialNumber, "LHR-9F12939E"); // Right Arm tracker id 9F12939E
        int LeftArm = strcmp(serialNumber, "LHR-A108F2F9"); // Left Arm tracker id A108F2F9
        int Pelvis = strcmp(serialNumber, "LHR-2741ADA8"); // Pelvis tracker id

        if(RightFoot == 0){
          whichBody = 1;
          tracking.q_track_rfoot = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2],whichBody};
          tracking.r_rfoot << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
          tracking.rfoot_tracked = trackedControllerPose.bPoseIsValid;
        }
        else if (LeftFoot == 0){
          whichBody = 2;
          tracking.q_track_lfoot = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2],whichBody};
          tracking.r_lfoot << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
          tracking.lfoot_tracked = trackedControllerPose.bPoseIsValid;
        }
        else if(RightArm == 0){
          whichBody = 3;
          tracking.q_track_rarm = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2],whichBody};
          tracking.r_rarm << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
          tracking.rarm_tracked = trackedControllerPose.bPoseIsValid;
        }
        else if (LeftArm == 0){
          whichBody = 4;
          tracking.q_track_larm = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2],whichBody};
          tracking.r_larm << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
          tracking.larm_tracked = trackedControllerPose.bPoseIsValid;
        }
        else if (Pelvis == 0){
          whichBody = 5;
          tracking.q_track_pelvis = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2], whichBody};
          tracking.r_pelvis << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
          tracking.pelvis_tracked = trackedControllerPose.bPoseIsValid;
        }
      }

      //CONTROLLERS
      if(trackedDeviceClass==vr::ETrackedDeviceClass::TrackedDeviceClass_Controller) {
          vr_pointer->GetControllerStateWithPose(vr::TrackingUniverseStanding, unDevice,
                                                  &controllerState, sizeof(controllerState),
                                                  &trackedControllerPose);
        position = GetPosition(trackedControllerPose.mDeviceToAbsoluteTracking);
        quaternion = GetRotation(trackedControllerPose.mDeviceToAbsoluteTracking);
        matrix_rotation = trackedControllerPose.mDeviceToAbsoluteTracking;
        velocity = trackedControllerPose.vVelocity;
        angularvelocity = trackedControllerPose.vAngularVelocity; 

        switch (trackedControllerRole){
          case vr::TrackedControllerRole_Invalid:
            // invalid
            break;

          case vr::TrackedControllerRole_RightHand:
            whichBody = 6;
            tracking.q_track_rhand = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2], whichBody};
            tracking.r_rhand << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
            tracking.rhand_tracked = trackedControllerPose.bPoseIsValid;
            break;

          case vr::TrackedControllerRole_LeftHand:
            whichBody = 7;
            tracking.q_track_lhand = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w, velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2],whichBody};
            tracking.r_lhand << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
            tracking.lhand_tracked = trackedControllerPose.bPoseIsValid;
            break;

          default:
            break;
				}
      }

      // HMD
      if(trackedDeviceClass==vr::ETrackedDeviceClass::TrackedDeviceClass_HMD) {
        whichBody = 8;
        vr_pointer->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0, &trackedDevicePose, 1);
        position = GetPosition(trackedDevicePose.mDeviceToAbsoluteTracking);
        quaternion = GetRotation(trackedDevicePose.mDeviceToAbsoluteTracking);
        matrix_rotation = trackedDevicePose.mDeviceToAbsoluteTracking;
        velocity = trackedDevicePose.vVelocity;
        angularvelocity = trackedDevicePose.vAngularVelocity;
        tracking.q_track_head = {position.v[0], position.v[1], position.v[2], quaternion.x, quaternion.y, quaternion.z, quaternion.w,velocity.v[0], velocity.v[1], velocity.v[2], angularvelocity.v[0], angularvelocity.v[1], angularvelocity.v[2], whichBody}; 
        tracking.r_head << matrix_rotation.m[0][0],matrix_rotation.m[0][1],matrix_rotation.m[0][2],matrix_rotation.m[1][0],matrix_rotation.m[1][1],matrix_rotation.m[1][2],matrix_rotation.m[2][0],matrix_rotation.m[2][1],matrix_rotation.m[2][2];
        tracking.head_tracked = trackedDevicePose.bPoseIsValid;
      }
    }
  }
  return tracking;
}

void ViveTracking::triggerHaptics(bool triggerRight_, bool triggerLeft_)
{
  for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++) {
    vr::ETrackedDeviceClass trackedDeviceClass = vr_pointer->GetTrackedDeviceClass(unDevice);
    if(trackedDeviceClass==vr::ETrackedDeviceClass::TrackedDeviceClass_Controller) {
      auto trackedControllerRole = vr::VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDevice);
      switch(trackedControllerRole){
        case vr::TrackedControllerRole_RightHand :
          if(triggerRight_){
            vr_pointer->TriggerHapticPulse(unDevice, 0, 300); 
          } 
          break; 
        case vr::TrackedControllerRole_LeftHand: 
          if(triggerLeft_){
            vr_pointer->TriggerHapticPulse(unDevice, 0, 300); 
          } 
          break; 
        case vr::TrackedControllerRole_Invalid:
          //invalid
          break; 
        default:
          //other cases
          break; 
      }
    }
  }
}

/** Get VR Button Events
 * For HTC VIVE
 * Axis 0 = Left/Right on the touchpad
 * Axis 1 = Forward/Backward on the touchpad
 * Axis 2 = Front trigger
 * Button 1 = menu button
 * Button 2 = side buttons
 * Button 14 = press down on touchpad
 * Button 15 = Front trigger (on/off version of Axis 2)
 */
ViveDataControllerButton ViveTracking::getControllerEvent() {
  ViveDataControllerButton joy;

  bool m_rbShowTrackedDevice[vr::k_unMaxTrackedDeviceCount];
  for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++) {
    vr::ETrackedDeviceClass trackedDeviceClass = vr_pointer->GetTrackedDeviceClass(unDevice);

    if (!vr_pointer->IsTrackedDeviceConnected(unDevice))
        continue;       

      vr::VRControllerState_t state;

      if (vr_pointer->GetControllerState(unDevice, &state, sizeof(state))) {
        if(trackedDeviceClass==vr::ETrackedDeviceClass::TrackedDeviceClass_Controller){
          auto trackedControllerRole = vr::VRSystem()->GetControllerRoleForTrackedDeviceIndex(unDevice);

          switch (trackedControllerRole){
            case vr::TrackedControllerRole_Invalid:
              // invalid
              break;

            case vr::TrackedControllerRole_RightHand:
              joy.RightController = assignedButtonEvent(state, joy.RightController,unDevice, m_rbShowTrackedDevice);
              break;

            case vr::TrackedControllerRole_LeftHand:
              joy.LeftController = assignedButtonEvent(state, joy.LeftController,unDevice, m_rbShowTrackedDevice);
              break;

            default:
              break;
          }
      }
    }
  }
  return joy;

}

ViveDataButtonEvent ViveTracking::assignedButtonEvent(vr::VRControllerState_t state, ViveDataButtonEvent joy, vr::TrackedDeviceIndex_t unDevice,bool m_rbShowTrackedDevice[vr::k_unMaxTrackedDeviceCount]) {
    state.ulButtonPressed = 0;
    state.ulButtonTouched = 0;
    if (vr_pointer->GetControllerState(unDevice, &state, sizeof(state))) {
      m_rbShowTrackedDevice[unDevice] = state.ulButtonPressed == 0;
      m_rbShowTrackedDevice[unDevice] = state.ulButtonTouched == 0;
      // Trigger
      if(state.ulButtonTouched == vr::ButtonMaskFromId(vr::k_EButton_Axis1) || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger){ 
        joy.triggerIsTouch= true;
      } else{ joy.triggerIsTouch = false; }
      if(state.ulButtonPressed == vr::ButtonMaskFromId(vr::k_EButton_Axis1) || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger){
        joy.triggerIsPress = true;
      } else{ joy.triggerIsPress = false; }
      // Touchpad
      if(state.ulButtonTouched == vr::ButtonMaskFromId(vr::k_EButton_Axis0) || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger){ 
        joy.trackpadIsTouch= true;
        joy.x = 0; //state.rAxis->x;
        joy.y = 0; //state.rAxis->y;
      } else{ joy.trackpadIsTouch = false; }
      if(state.ulButtonPressed == vr::ButtonMaskFromId(vr::k_EButton_Axis0) || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger){
        joy.trackpadIsPress = true;
        joy.x = state.rAxis->x;
        joy.y = state.rAxis->y;
      } else{ joy.trackpadIsPress = false; }
      // Menu 
      if(state.ulButtonTouched == vr::ButtonMaskFromId(vr::k_EButton_ApplicationMenu) || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger_Gripper_Menu || 
         state.ulButtonTouched == mc_vive_plugin::Touchpad_Gripper_Menu  || state.ulButtonTouched == mc_vive_plugin::Touchpad_Trigger_Menu || state.ulButtonTouched == mc_vive_plugin::Trigger_Gripper_Menu ||
         state.ulButtonTouched == mc_vive_plugin::Touchpad_Menu || state.ulButtonTouched == mc_vive_plugin::Trigger_Menu || state.ulButtonPressed == mc_vive_plugin::Gripper_Menu )
      { 
       joy.menuIsTouch = true;
      }else{joy.menuIsTouch = false;}
      if(state.ulButtonPressed == vr::ButtonMaskFromId(vr::k_EButton_ApplicationMenu) || state.ulButtonPressed == mc_vive_plugin::Touchpad_Trigger_Gripper_Menu || 
         state.ulButtonPressed == mc_vive_plugin::Touchpad_Gripper_Menu  || state.ulButtonPressed == mc_vive_plugin::Touchpad_Trigger_Menu || state.ulButtonPressed == mc_vive_plugin::Trigger_Gripper_Menu ||
         state.ulButtonPressed == mc_vive_plugin::Touchpad_Menu || state.ulButtonPressed == mc_vive_plugin::Trigger_Menu || state.ulButtonPressed == mc_vive_plugin::Gripper_Menu )
      { 
        joy.menuIsPress = true;
      } else{joy.menuIsPress = false; }; 
      // Gripper
      if(state.ulButtonTouched == vr::ButtonMaskFromId(vr::k_EButton_Grip)){ 
        joy.gripIsPress = true; joy.gripIsTouch = true; //The button is not very effective, to improve the feedback, the button pressed and the touch are identical.
      }else {joy.gripIsPress = false; joy.gripIsTouch = false; }
      // No button 
      if(state.ulButtonTouched == 0)
      {
        joy.triggerIsPress = false ; joy.triggerIsTouch = false; 
        joy.trackpadIsTouch = false; joy.trackpadIsPress = false; 
        joy.gripIsTouch = false;     joy.gripIsPress = false ;  
        joy.menuIsTouch = false;     joy.menuIsPress = false; 
        joy.x = joy.y = 0;
      }
    }
    
  return joy;
}

VivePlugin::~VivePlugin()
{
running_ = false;
th_.join();
}

void VivePlugin::init(mc_control::MCGlobalController & controller, const mc_rtc::Configuration & config)
{
  mc_rtc::log::info("VivePlugin::init called with configuration:\n{}", config.dump(true, true));
  auto & ctl = controller.controller();

  /** Store data on the datastore
   * Position - Rotation for retargetting
   * Button events
   */
  // Datastore - position rotation target PTransformd-
  ctl.datastore().make<bool>("VivePlugin", true);
  auto & data = ctl.datastore().make<ViveData>("VivePlugin::Data");
  ctl.datastore().make_call("VivePlugin::GetPos",[&data](std::string & segmentName) {return data.body_poses_.at(segmentName);});
  // Datastore - rotation pos
  auto & data_rot = ctl.datastore().make<ViveData>("VivePlugin::RotPos");
  ctl.datastore().make_call("VivePlugin::GetRot", [&data_rot](std::string & segmentName) {return data_rot.rot_poses_.at(segmentName);});
  //Button events
  auto & button_event = ctl.datastore().make<ViveData>("VivePlugin::Button");
  ctl.datastore().make_call("VivePlugin::GetButtonEvent",[&button_event](std::string & deviceName) {return button_event.buttonPress.at(deviceName);});
  // Datastore - angular velocity - 
  auto & data_ang_vel = ctl.datastore().make<ViveData>("VivePlugin::AngularVelocity"); 
  ctl.datastore().make_call("VivePlugin::GetAngularVelocity", [&data_ang_vel](std::string & segmentName) {return data_ang_vel.body_vel_.at(segmentName);});
  // Datastore - linear velocity - 
  auto & data_vel = ctl.datastore().make<ViveData>("VivePlugin::LinearVelocity"); 
  ctl.datastore().make_call("VivePlugin::GetLinearVelocity", [&data_vel](std::string & segmentName) {return data_vel.body_vel_.at(segmentName);});
  // Acceleration 
  auto & data_acc = ctl.datastore().make<ViveData>("VivePlugin::Acceleration"); 
  ctl.datastore().make_call("VivePlugin::GetAcceleration", [&data_acc](std::string & segmentName) {return data_acc.body_acc_.at(segmentName);});
  // Connected or not connected ? That is the question
  auto & connect = ctl.datastore().make<ViveData>("VivePlugin::DeviceConnected");
  ctl.datastore().make_call("VivePlugin::GetTrackingInfo",[&connect](std::string & deviceName){return connect.isConnect.at(deviceName);});
  

  th_ = std::thread(
    [this]()
    {
    ViveTracking Vive;

    while(running_)
    {
    auto dataHTC = Vive.getPoseData();
    auto buttonHTC = Vive.getControllerEvent();
    
    std::lock_guard<std::mutex> lock(mut_);
    /** Retargetting
     * For each bodypart define in table "bodyPart", it will be associated
     * the position/rotation/position&rotation tracked by the trackers,
     * controllers and HMD of HTC VIVE
     */
    std::string bodyPart[] = {"Head", "LeftHand", "RightHand", "LeftArm", "RightArm","LeftFoot", "RightFoot","Pelvis"};
    for (int i = 0; i < int(sizeof(bodyPart)); i++){
      std::string & name = bodyPart[i];
      Eigen::Vector3d target{};
      Eigen::Vector3d targetPepper{};
      switch (i){
        case 0: // Head
          if(!dataHTC.q_track_head.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_head[0], dataHTC.q_track_head[1], dataHTC.q_track_head[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_head.transpose();
            //auto acc = Vive.AccelData(dataHTC.q_track_head, t, dataHTC.t_head, data_vel_.body_vel_[name]); 
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_head[7], dataHTC.q_track_head[8], dataHTC.q_track_head[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_head[10], dataHTC.q_track_head[11], dataHTC.q_track_head[12]);
            // data_vel_.body_acc_[name] = acc; 
            isTracked.isConnect[name] = dataHTC.head_tracked; 
          }
          break;
        case 1 : // LeftHand
          if(!dataHTC.q_track_lhand.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_lhand[0], dataHTC.q_track_lhand[1], dataHTC.q_track_lhand[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_lhand.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_lhand[7], dataHTC.q_track_lhand[8], dataHTC.q_track_lhand[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_lhand[10], dataHTC.q_track_lhand[11], dataHTC.q_track_lhand[12]); 
            isTracked.isConnect[name] = dataHTC.lhand_tracked; 
          }
          break;
        case 2: // RightHand
          if(!dataHTC.q_track_rhand.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_rhand[0], dataHTC.q_track_rhand[1], dataHTC.q_track_rhand[2]);  
            rotdata_.rot_poses_[name] = dataHTC.r_rhand.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rhand[7], dataHTC.q_track_rhand[8], dataHTC.q_track_rhand[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rhand[10], dataHTC.q_track_rhand[11], dataHTC.q_track_rhand[12]); 
            isTracked.isConnect[name] = dataHTC.rhand_tracked; 
          }
          break;
        case 3: // LeftArm
          if(!dataHTC.q_track_larm.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_larm[0], dataHTC.q_track_larm[1], dataHTC.q_track_larm[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_larm.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_larm[7], dataHTC.q_track_larm[8], dataHTC.q_track_larm[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_larm[10], dataHTC.q_track_larm[11], dataHTC.q_track_larm[12]); 
            isTracked.isConnect[name] = dataHTC.larm_tracked; 
          }
          break;
        case 4: // RightArm
          if(!dataHTC.q_track_rarm.empty()){
            data_.body_poses_[name]  = Eigen::Vector3d(dataHTC.q_track_rarm[0], dataHTC.q_track_rarm[1], dataHTC.q_track_rarm[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_rarm.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rarm[7], dataHTC.q_track_rarm[8], dataHTC.q_track_rarm[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rarm[10], dataHTC.q_track_rarm[11], dataHTC.q_track_rarm[12]); 
            isTracked.isConnect[name] = dataHTC.rarm_tracked; 
          }
          break;
        case 5: // LeftFoot or Elbow
          if(!dataHTC.q_track_lfoot.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_lfoot[0], dataHTC.q_track_lfoot[1], dataHTC.q_track_lfoot[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_lfoot.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_lfoot[7], dataHTC.q_track_lfoot[8], dataHTC.q_track_lfoot[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_lfoot[10], dataHTC.q_track_lfoot[11], dataHTC.q_track_lfoot[12]); 
            isTracked.isConnect[name] = dataHTC.lfoot_tracked; 
          }
          break;
        case 6: // RightFoot or Elbow
          if(!dataHTC.q_track_rfoot.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_rfoot[0], dataHTC.q_track_rfoot[1], dataHTC.q_track_rfoot[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_rfoot.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rfoot[7], dataHTC.q_track_rfoot[8], dataHTC.q_track_rfoot[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_rfoot[10], dataHTC.q_track_rfoot[11], dataHTC.q_track_rfoot[12]); 
            isTracked.isConnect[name] = dataHTC.rfoot_tracked; 
          }
          break;
        case 7: // Pelvis
          if(!dataHTC.q_track_pelvis.empty()){
            data_.body_poses_[name] = Eigen::Vector3d(dataHTC.q_track_pelvis[0], dataHTC.q_track_pelvis[1], dataHTC.q_track_pelvis[2]); 
            rotdata_.rot_poses_[name] = dataHTC.r_pelvis.transpose();
            data_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_pelvis[7], dataHTC.q_track_pelvis[8], dataHTC.q_track_pelvis[9]);
            data_ang_vel_.body_vel_[name] = Eigen::Vector3d(dataHTC.q_track_pelvis[10], dataHTC.q_track_pelvis[11], dataHTC.q_track_pelvis[12]); 
            isTracked.isConnect[name] = dataHTC.pelvis_tracked; 
          }
          break;
      }
    }
    /** Button Events
     * For each controllers device, all buttons events are returned
     * Grip
     * Trackpad
     * Button system and menu
     * Trigger
     */
    std::string Controller_RL[] = {"RightController", "LeftController"};
    for (int i = 0; i < int(sizeof(Controller_RL)); i++){
      std::string & name = Controller_RL[i];
      switch(i){
        case 0: //RightController
        // 
          button_.buttonPress[name] = buttonHTC.RightController;
          break;
        case 1: //LeftController
          button_.buttonPress[name] = buttonHTC.LeftController;
          break;
      }
    }

    /**
     * Trigger Haptics 
     * 
    */
    Vive.triggerHaptics(rightHaptics_, leftHaptics_); //right hand

  }//end while running
}
);
}

void VivePlugin::reset(mc_control::MCGlobalController & /* controller */)
{
  mc_rtc::log::info("VivePlugin::reset called");
}

void VivePlugin::before(mc_control::MCGlobalController & controller)
{
  auto & ctl = controller.controller();
  std::lock_guard<std::mutex> lock(mut_);
  auto & data = ctl.datastore().get<ViveData>("VivePlugin::Data");
  data = data_;
  auto & data_rot = ctl.datastore().get<ViveData>("VivePlugin::RotPos");
  data_rot = rotdata_;
  auto & button_event = ctl.datastore().get<ViveData>("VivePlugin::Button");
  button_event = button_;
  auto & data_vel = ctl.datastore().get<ViveData>("VivePlugin::LinearVelocity"); 
  data_vel = data_vel_; 
  auto & data_ang_vel = ctl.datastore().get<ViveData>("VivePlugin::AngularVelocity"); 
  data_ang_vel = data_ang_vel_; 
  auto & connect = ctl.datastore().get<ViveData>("VivePlugin::DeviceConnected"); 
  connect = isTracked; 
  if(ctl.datastore().has("TeleoPepper::HapticFeedback"))
  {
    rightHaptics_ = ctl.datastore().call<bool>("TeleoPepper::GetHapticFeedback", Controller_RL[0]); 
    leftHaptics_  = ctl.datastore().call<bool>("TeleoPepper::GetHapticFeedback", Controller_RL[1]); 
  }

}

void VivePlugin::after(mc_control::MCGlobalController & /* controller */)
{
}

mc_control::GlobalPlugin::GlobalPluginConfiguration VivePlugin::configuration()
{
  mc_control::GlobalPlugin::GlobalPluginConfiguration out;
  out.should_run_before = true;
  out.should_run_after = false;
  out.should_always_run = true;
  return out;
}

} // namespace mc_vive_plugin

EXPORT_MC_RTC_PLUGIN("VivePlugin", mc_vive_plugin::VivePlugin)