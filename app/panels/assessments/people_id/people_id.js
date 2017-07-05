var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var peoplePanel = new panel.PanelQuestions('people_id', 'tab_people_id',
  path.join(ROOT, 'gui/Assessments/People_ID.md'),
  path.join(ROOT, 'app/panels/assessments/people_id/people_id.html'))

module.exports = peoplePanel
