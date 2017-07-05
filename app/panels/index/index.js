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

var passions = require(path.join(ROOT, 'app/panels/assessments/passions/passions.js'))
passions.load()
dataManager.addPanel(passions.name, passions)

var dreams = require(path.join(ROOT, 'app/panels/assessments/dreams/dreams.js'))
dreams.load()
dataManager.addPanel(dreams.name, dreams)

var people = require(path.join(ROOT, 'app/panels/assessments/people_id/people_id.js'))
people.load()
dataManager.addPanel(people.name, people)

var values = require(path.join(ROOT, 'app/panels/assessments/values/values.js'))
values.load()
dataManager.addPanel(values.name, values)

dataManager.load()
