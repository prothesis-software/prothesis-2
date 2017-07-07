/*
  1. Load Elements from Markdown
*/

var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var people_orientation_Panel = new panel.PanelCheckBoxes('people_orientation', 'tab_people_orientation',
  path.join(ROOT, 'gui/Assessments/People_Orientation.md'),
  path.join(ROOT, 'app/panels/assessments/people_orientation/people_orientation.html'),
  'people_container')

module.exports = people_orientation_Panel
