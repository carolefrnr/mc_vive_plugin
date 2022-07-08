#pragma once

namespace mc_vive_plugin
{
    // VR Buttons Events tracking
    struct ViveDataButtonEvent{ //events states
                                //Grip
      bool gripIsPress; // 0 No 1 Yes
      bool gripIsTouch; // 0 No 1 Yes

      // Menu Button
      bool menuIsPress;
      bool menuIsTouch;

      // Trigger
      bool triggerIsPress;
      bool triggerIsTouch;

      // Trackpad
      bool trackpadIsPress;
      bool trackpadIsTouch;
      double x; // Only for trackpad, value between -1 and 1
      double y; // Only for trackpad, value between -1 and 1

      // NewData 
      bool isValid; 
    };
}
