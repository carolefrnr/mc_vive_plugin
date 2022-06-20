# VivePlugin

The `VivePlugin` handles integration between `HTC VIVE` sensors, `SteamVR` data and `mc_rtc`.

This package depends on:
- [mc_rtc](https://github.com/jrl-umi3218/mc_rtc)
- [openvr api](https://github.com/ValveSoftware/openvr)
```sh 
sudo apt-get install libopenvr-dev
```
- Steam 
```sh 
sudo apt install steam 
```
- SteamVR, installed from the Steam store 

## Installation

After installing the afformentioned dependencies,

```sh
git clone git@gite.lirmm.fr:cfournier/teleoperation.git 
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j8
sudo make install
```

## Running instructions
Run using your `mc_rtc` interface of choice, add `VivePlugin` to the Plugins configuration entry or enable the autoload option