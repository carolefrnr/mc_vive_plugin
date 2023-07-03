#pragma once
#include <SpaceVecAlg/SpaceVecAlg>
#include <map>
#include <string>
#include <openvr/openvr.h>
// #include <openvr/openvr_driver.h>
#include <mc_control/fsm/State.h>
#include <mc_vive_plugin/ViveData.h>

namespace mc_vive_plugin
{
    enum MaskButton {
        Touchpad = 4294967296,
        Trigger = 8589934592, 
        Touchpad_Trigger = 12884901888, 
        Touchpad_Gripper = 4294967300,
        Trigger_Gripper = 8589934596, 
        Touchpad_Menu = 4294967298,
        Trigger_Menu = 8589934596, 
        Touchpad_Trigger_Menu = 12884901890, 
        Touchpad_Gripper_Menu = 4294967302, 
        Trigger_Gripper_Menu = 8589934598, 
        Gripper_Menu = 6, 
        Touchpad_Trigger_Gripper_Menu = 12884901892
    }; 

    // Pose and rotation data of controller and trackers
    struct ViveData_Vector {
        // In order this vector contains
        std::vector<double> q_track_head;
        std::vector<double> q_track_rhand;
        std::vector<double> q_track_lhand;
        std::vector<double> q_track_rfoot;
        std::vector<double> q_track_lfoot;
        std::vector<double> q_track_rarm;
        std::vector<double> q_track_larm;
        std::vector<double> q_track_pelvis;
        std::vector<double> q_track_elbow;

        // Rotation matrix for each tracked bodypart
        Eigen::Matrix3d r_head;
        Eigen::Matrix3d r_rhand;
        Eigen::Matrix3d r_lhand;
        Eigen::Matrix3d r_rfoot;
        Eigen::Matrix3d r_lfoot;
        Eigen::Matrix3d r_rarm;
        Eigen::Matrix3d r_larm;
        Eigen::Matrix3d r_pelvis;
        Eigen::Matrix3d r_elbow;

        // Valid pose (device tracked by base station)
        bool rhand_tracked; 
        bool lhand_tracked;
        bool head_tracked; 
        bool rfoot_tracked;
        bool lfoot_tracked; 
        bool rarm_tracked; 
        bool larm_tracked; 
        bool pelvis_tracked; 

        //Init Time 
        bool t_head = true; 

        //Acel 
        time_t timer; 
    };

    struct ViveDataControllerButton{ //
        ViveDataButtonEvent RightController;
        ViveDataButtonEvent LeftController;
    };

    // All data send to the datastore
    struct ViveData {
        std::map<std::string, Eigen::Vector3d> body_poses_;
        std::map<std::string, Eigen::Matrix3d> rot_poses_;
        std::map<std::string, ViveDataButtonEvent> buttonPress;
        std::map<std::string, bool> buttonValue_;
        std::map<std::string, Eigen::Vector3d> body_vel_;
        std::map<std::string, Eigen::Vector3d> body_acc_;
        std::map<std::string, bool> isConnect;
    };

    class ViveTracking {
    private:
        vr::IVRSystem* vr_pointer {NULL};
        vr::HmdVector3_t GetPosition(vr::HmdMatrix34_t matrix);
        vr::HmdQuaternion_t GetRotation(vr::HmdMatrix34_t matrix);
    public:
        ~ViveTracking();
        ViveTracking();

        //Functions
        ViveData_Vector getPoseData();
        ViveDataControllerButton getControllerEvent();
        ViveDataButtonEvent assignedButtonEvent(vr::VRControllerState_t state, ViveDataButtonEvent joy, vr::TrackedDeviceIndex_t unDevice,bool m_rbShowTrackedDevice[vr::k_unMaxTrackedDeviceCount]);
        Eigen::Vector3d AccelData(std::vector<double> dataHTC, time_t t, bool init, Eigen::Vector3d prev_data); 
        void triggerHaptics(bool triggerRight_, bool triggerLeft_); 
        
        //Variables 
        Eigen::Vector3d init_vel = Eigen::Vector3d{0,0,0};  
        Eigen::Vector3d init_angvel = Eigen::Vector3d{0,0,0}; 
        time_t init_t = 0; 
        time_t prev_t; 
        int t = 0; 
    };

} // namespace mc_vive_plugin
