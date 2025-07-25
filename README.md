# Tstats

Tstats is a front-end terminal program to display data about hardware on a linux machine. \
The backend is handled by my library, [LibHPD](https://github.com/Vortron-rd/libhpd).

## Feature Goals
(Not ordered chronologically)

- [ ] -z : Displays hertz of a cpu core. (Requires -c)
- [ ] -c CORE : Selects which core to display data for. (Default: all)
- [ ] -L Displays CPU load. (Will display the load of a single core if -c is specified)
- [ ] -D : Shows disk IO.
- [ ] -d DEVICE : Which disk to display data for. (Default: all)
- [ ] -R Shows RAM memory usage and speed.
- [ ] -r DEVICE : Selects RAM device to display data for. (Default: all)
- [ ] -t seconds : Selects how many seconds to record data measurements over. (Default: 3)
- [ ] -l : Loops the program output every 3 seconds (Or how many are specified with -t)
- [ ] -m : Displays the output in a machine-readable format. (Probably XML or JSON, this will be decided in the future)
- [ ] -B : Display storage amounts in bytes (By default, this program will use Gibibytes)
- [ ] -b : Display storage amounts with Gigabytes (By default, this program will use Gibibytes)
- [ ] -h : Displays help and usage options.
- [ ] -F : Display fan speed.
- [ ] -f DEVICE : Selects the fan to display data for. (Default: all)
- [ ] -T : Displays Temperature data.
- [ ] -th SENSOR : Select what thermostat to display data for. (Default: all)
- [ ] -I : Displays data related to Internet I/O.
- [ ] -i DEVICE : Which device to display internet data for. (Default: all)
- [ ] -G : Displays data related to dedicated graphics cards.
- [ ] -g DEVICE : Select which graphics card to display data for.
- [ ] -cl : Colorizes the output.
- [ ] Make device selecting options have the ability to select multiple devices.
- [ ] Create manpage
- [ ] Create Wiki
- [ ] Fix Install/Uninstall Script
- [ ] Create Archlinux AUR package
- [ ] Create APT package
- [ ] Create .deb package (Is that the same as APT?)
- [ ] Create flatpak
