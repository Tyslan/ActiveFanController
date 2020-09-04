# ActiveFanController

Active Fan Controller Service for Linux

## Build instructions

### Ubuntu

```bash
sudo apt install gcc cmake
./build.sh
```

## Run

> ./ActiveFanControl

or

> ./ActiveFanControl "path_to_conf"

The default conf path is /etc/afc.

### Config

```json
{  
    "temp_zone0_path": "/sys/devices/virtual/thermal/thermal_zone0/temp",
    "temp_zone1_path": "/sys/devices/virtual/thermal/thermal_zone0/temp",
    "pwm_path": "/sys/devices/platform/pwm-fan/hwmon/hwmon3/pwm1",
    "pwm_fan_jump": 50,
    "pwm_max": 255,
    "start_fan_temp": 35,
    "continious_fan_temp":60
}
```

Find the temperature zones on a RockPro64 with the following command:

> sudo find /sys -name temp

Find the pwm path on a RockPro64 with the following command:

> sudo find /sys -name pwm1 | grep hwmon

## Credits

- tuxd3v: [ATS - Active Thermal Service](https://github.com/tuxd3v/ats)
