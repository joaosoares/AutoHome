'use strict';

angular.module('angularApp')
  .controller('MainCtrl', ['$scope', '$http', function ($scope, $http) {

  	$http.get('testdb/groups.json').success( function(data){
  		$scope.groups = data;
  	});
  	
  }]);
