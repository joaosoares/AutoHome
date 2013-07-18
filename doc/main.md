AutoHome Project
================

Goal
----
To have production-level, specialized software and hardware to control common domestic appliances flexible enough to adapt to diverse uses and reliable enough to replace current systems without loss of availability.

Components
----------
### Client application (desktop/mobile)
A set of client-side applications to allow the end user to configure and control a set of installed devices in his home.

Currently, the desktop application is built with modern web technologies (node.js, express, angular), since they allow the creation of a pleasing user interface in acceptable development time.

### Device hardware/firmware
A device comprises a physical motherboard that coordinates many different appliances and exposes an API for the client applications. Each device is able to communicate with other devices in the home and relay their information to the client apps as well.

For the initial prototypes, the Arduino platform is used in the devices, due to its versability. The API is built on RESTful principles and available via HTTP, although authentication issues have to be solved.

### Module hardware/firmware
The module is the hardware that physically connects electrical appliances to the AutoHome system. There will be distinct modules for each kind of appliance. Their functionality will depend on the kind of control desire, eg. light control modules will connect to lightbulbs and allow them to be dimmed, turned on, or off.

For initial prototypes of the system, modules yet do not perform useful functionality, except for communication with the device motherboard.

- Dimmer
- Light switch
- Electrial outlet
- Presence sensor
- Sensors and actuators
- Infrared
- Fan
- Irrigation
- Porteiro eletronico
- Pool