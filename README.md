## COOLDOWN usermode driver for popular SOCs
Useful, when you are ~~(compiling kernel under it)~~ overclocking your device\`s cpu 
or want it to live for a long time.
- It uses custom fan, connected to one of general-purpose pins, 
now it runs under: 
 * RASPBERRY PI 1,2,3 
- with any linux distribution,
can be easily ported to another SOCs, platforms 
(Uses only POSIX and linux sysfs).
- To cool your device down it uses temperature hysteresis 
(for more information please see [config](./config)).
### How to install
- First, you need schematic(ex is for bcm283\*):
![!only raspberry 1,2,3](./COOLDOWN_SCHEMATICS/cooldown.png " Only raspberry") 
 * My solution(fan uses 9v battery + 5v SOC power ):
![!only raspberry 1,2,3](./COOLDOWN_SCHEMATICS/RPI_COOL.jpg " My raspberry pi 3") 

- Compiling\Installing
```
make SOC=SOC_NAME
sudo make install
```
Run `make help` to list SOC\_NAME suitable names

- Running:
```
sudo cooldown
```
