/*
  1. Load Elements from Markdown
*/

var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var rolesPanel = new panel.PanelCheckBoxes('roles', 'tab_roles',
  path.join(ROOT, 'gui/Assessments/Roles.md'),
  path.join(ROOT, 'app/panels/assessments/roles/roles.html'),
  'roles_container')

module.exports = rolesPanel
