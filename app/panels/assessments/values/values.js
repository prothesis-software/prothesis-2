var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var valuesPanel = new panel.PanelQuestions('values', 'tab_values',
  path.join(ROOT, 'gui/Assessments/Values.md'),
  path.join(ROOT, 'app/panels/assessments/values/values.html'))

module.exports = valuesPanel
