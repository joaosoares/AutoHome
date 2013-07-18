The RESTful API
===============

This is the API used for data interchange between a device and a client application. Its main purpose is to allow for the state of the system to be viewed and modified by a client application.

$http.get("192.168.254.67/api/overview").success(function (data) {
	$scope.overview = data;
})

$scope.overview[0].name -> Florinda
$scope.overview[0].modules.name


/overview
GET only
[
	{
		"name": "Florinda"
		"id":
		"ip":
		"modules": 
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
			}
	},	
	{
		"name":
		"id":
		"ip":
		"modules": 
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
			}
	}	
]


/groups





