/*
  1. Load Elements from Markdown
*/

var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

var skillsPanel = new panel.PanelCheckBoxes('skills', 'tab_skills',
  path.join(ROOT, 'gui/Assessments/Skills.md'),
  path.join(ROOT, 'app/panels/assessments/skills/skills.html'),
  'skills_container')

module.exports = skillsPanel
