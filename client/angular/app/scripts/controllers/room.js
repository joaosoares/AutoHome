'use strict';

angular.module('angularApp')
  .controller('RoomCtrl', function ($http, $routeParams, $scope) {

  	$http.get('testdb/' + $routeParams.roomId + '.json').success( function(data){
  		$scope.room = data;
  	});
  });
