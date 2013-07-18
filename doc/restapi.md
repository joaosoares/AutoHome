The RESTful API
===============

This is the API used for data interchange between a device and a client application. Its main purpose is to allow for the state of the system to be viewed and modified by a client application.


URL schemes
-----------

### /overview
Returns a bird's eye overview of the system so that the main structure of the client application can be built.

GET:

    [
        {
            "name": "Florinda"
            "id":
            "ip":
            "modules": [
                {
                    "name":,
                    "id":,
                    "type":,
                    "group":
                    "status":
                        {
                            // Example for light module
                            "brightness":,
                            "current":,
                            "voltage":,
                            "frequency":,
                            "temperature":
                        }
                },
                {
                    "name":,
                    "id":,
                    "type",
                    "group":,
                    "status":
                        {
                            // Example for outlet module
                            "consumption":,
                            "on/off":,
                            "current":,
                            "voltage":,
                            "frequency":,
                            "temperature":
                        }
                }]
        }, etc...
    ]


### /settings
Returns some settings that will be checked against the client application, mainly the separation into groups.

    {
        "groups": [
            {
                "name":,
                "device-ids": [ ],
            }, etc...
        ]
    }

### /devices
A collection of all devices in a system.

Parameter | Filters by              | Example                      
--        | --                      | --                           
group     | Group device belongs to | `/devices?group=living-room` 




Typical usage
-------------

$http.get("192.168.254.67/api/overview").success(function (data) {
    $scope.overview = data;
})

$scope.overview[0].name -> Florinda
$scope.overview[0].modules.name
