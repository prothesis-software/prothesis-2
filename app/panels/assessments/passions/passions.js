var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var passionsPanel = new panel.PanelQuestions('passions', 'tab_passions',
  path.join(ROOT, 'gui/Assessments/Passions.md'),
  path.join(ROOT, 'app/panels/assessments/passions/passions.html'))

module.exports = passionsPanel
