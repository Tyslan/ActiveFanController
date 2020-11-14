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

## Install as a service

After building the program, from inside the root folder of the project:

> sudo cp ./build/app/afc /usr/local/sbin/afc
> sudo cp etc/afc.conf /etc/afc.conf
> sudo cp systemd/afc.service /etc/systemd/system/afc.service

Now everything is in place to start the service:

> sudo systemctl start afc

And check status with:

> sudo systemctl status afc

## Config

```json
{  
    "temp_zone0_path": "/sys/devices/virtual/thermal/thermal_zone0/temp",
    "temp_zone1_path": "/sys/devices/virtual/thermal/thermal_zone0/temp",
    "pwm_path": "/sys/devices/platform/pwm-fan/hwmon",
    "pwm_file": "pwm1",
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
