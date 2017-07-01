/*
  This script is responsible for initialising the panels and registering them
  in userDataManager

*/
var path = require('path')

var roles = require(path.join(ROOT, 'app/panels/assessments/roles/roles.js'))
roles.load()
dataManager.addPanel(roles.name, roles)

var skills = require(path.join(ROOT, 'app/panels/assessments/skills/skills.js'))
skills.load()
dataManager.addPanel(skills.name, skills)

dataManager.load()
