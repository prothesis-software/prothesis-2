var path = require('path')
var panel = require(path.join(ROOT, 'app/js/panel.js'))

// JS CANCERRR
// var CustomPanel = function(a, b, c, d, e) {
//   panel.PanelQuestions.call(this, a, b, c, d)
//
//   this.titleElementID = e
//
//   this.load = function() {
//     panel.PanelQuestions.prototype.load.call(this)
//     this.setTitle()
//   }
//
//   this.setTitle = function() {
//     document.getElementById(this.titleElementID).innerHTML = this.questionsFromMarkdown[1].items[0]
//   }
// }

var spoken_words_panel = new panel.PanelQuestions('spoken_words', 'tab_spoken_words',
  path.join(ROOT, 'gui/Assessments/Spoken_Words.md'),
  path.join(ROOT, 'app/panels/assessments/spoken_words/spoken_words.html'))

// TODO: Event when panel is laoded so we can add extra style
// function onPanelLoad() {
//   document.getElementById('panel_spoken_words_title').innerHTML = spoken_words_panel.questionsFromMarkdown[1].items[0]
// }
//
// console.log(spoken_words_panel.questionsFromMarkdown)

module.exports = spoken_words_panel
