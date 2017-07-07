var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var dreamsPanel = new panel.PanelQuestions('dreams', 'tab_dreams',
  path.join(ROOT, 'gui/Assessments/Dreams.md'),
  path.join(ROOT, 'app/panels/assessments/dreams/dreams.html'))

module.exports = dreamsPanel
