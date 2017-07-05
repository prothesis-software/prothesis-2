/** @module dataManager */
/*
  DataManager

  DESCRIPTION:
    This object is basically a big wrapper for the panels.
    In globals.js it is initialised as a global.

    Use this object for getting data from another panel

  EXAMPLE:
    userDataManager.getRoles() // ['Cat', 'Dogs', 'Carrots']
*/

var path = require('path')
var utils = require(path.join(ROOT, 'app/js/utils.js'))

/**
 * DataManager Object
 * @class
 * @memberof dataManager
 * @param  {String} dataFilePath User Data file path
 */
var DataManager = function(dataFilePath) {

  // Reigster save on close
  window.onbeforeunload = this.save

  this.dataFilePath = dataFilePath

  this.panelList = new utils.AssocArray()

  this.getRoles = function() {
    return this.panelList.getByName('roles').getCheckedItems()
  }

  this.getSkills = function() {
    return this.panelList.getByName('skills').getCheckedItems()
  }

  this.addPanel = function(name, panelObject) {
    this.panelList.push(name, panelObject)
  }

  /*
    Ask every panel from panelList for its internal state as markdown
    and return it
  */
  this.getAllStateAsMarkdown = function() {

    var markdown = ''

    for (var i = 0; i < this.panelList.getLength(); i++) {
      markdown += this.panelList.getByIndex(i).getStateAsMarkdown()
    }
    //var panels = this.panelList.

    return markdown
  }

  /*
    Get all states as markdown and write to file
  */
  this.save = function() {
    //console.log("SAVE")
    var data = this.getAllStateAsMarkdown()

    utils.write(this.dataFilePath, data)
  }

  /*
    Load the internal state from file.
    Send the markdown to the respective panels for loading
  */
  this.load = function() {
    var data = this.parseMarkdown(this.dataFilePath)

    for (var i = 0; i < this.panelList.getLength(); i++) {

      var panelObject = this.panelList.getByIndex(i)

      var panelName = panelObject.getName()
      var panelData = data.getByName(panelName)

      //console.log(panelData)
      panelObject.setStateFromMarkdown(panelData)
    }
  }

  /*
  Parse markdown into an AssocArray
  ```
  # A
  - some
  - stuff
  ## Lolcat
  # B
  - More
  - stuff
  ```
  ->
  arr.getByName('A') // "- some\n- stuff\n## Lolcat"
  */
  this.parseMarkdown = function() {
    var data = utils.read(this.dataFilePath)

    var lines = data.split('\n')
    var sections = new utils.AssocArray()

    var currentTitle = ''
    var currentData = ''

    for (var i = 0; i < lines.length; i++) {
      //console.log(lines[i])
      var lineParts = lines[i].split(' ')
      if (lineParts[0] == '#') {

        var tmpTitle = lineParts.slice(1, lineParts.length).join(' ')

        if (currentTitle != '') {
          sections.push(currentTitle, currentData)
          currentData = ''
        }

        currentTitle = tmpTitle

      } else {
        currentData += lineParts.join(' ') + '\n'
      }
    }

    // Push the last section
    sections.push(currentTitle, currentData)

    return sections
  }

}

module.exports = DataManager
