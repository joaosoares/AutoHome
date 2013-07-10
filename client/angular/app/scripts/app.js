'use strict';

angular.module('angularApp', [])
  .config(['$routeProvider', function ($routeProvider) {
    $routeProvider
      .when('/', {
        templateUrl: 'views/main.html',
        controller: 'MainCtrl'
      })
      .when('/:groupId/', {
        templateUrl: 'views/group.html',
        controller: 'GroupCtrl'
      })
      .otherwise({
        redirectTo: '/'
      });
  }]);
