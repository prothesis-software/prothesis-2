/** @module panel */
/*
  A panel has the following roles:
    - Inject the respective panel HTML using gui.injectPage()
    - Load the respective GUI elements from markdown using the guiLoader module
    - Create the required components using the gui module
    - Apply a style to the components
    - Handle panel specific logic
      - EG: Refresh the elements when the tab is activated
      - Validate user input

  Panels with common format should be defined here.
  EG: Roles and Skills are only checkboxes, therefore they make use of
  the PanelCheckBoxes object defined here.
  This is to ensure a standard style accross common panels
*/

var guiLoader = require(path.join(ROOT, 'app/js/guiLoader.js'))
var gui = require(path.join(ROOT, 'app/js/gui.js'))

/*
  The base Panel Object
*/

/**
 * Panel Object
 * @class
 * @memberof panel
 * @param  {String} panelName Name of the Panel
 * @return {Panel}
 */
var Panel = function(panelName) {

  this.name = panelName // Used for save/load

  this.getName = function() {
    return this.name
  }

  /*
    Load the GUI data from Markdown and initialise internal state
  */
  this.load = function() {
    console.log('Panel.load() Has not been implemented!')
  }

  this.setStateFromMarkdown = function(markdown) {
    console.log('Panel.setStateFromMarkdown() Has not been implemented!')
  }
  /*
    Inject the internal state into the DOM
  */
  this.inject = function() {
    console.log('Panel.inject() Has not been implemented!')
  }

  this.getStateAsMarkdown = function(markdown) {
    console.log('Panel.getStateAsMarkdown() Has not been implemented!')
  }

}

/**
 * A panel used for displaying Check Boxes
 * @class
 * @extends {Panel}
 * @memberof panel
 * @param  {String} panelName           Name of the panel
 * @param  {String} panelRootID         The ID of the root element for the panel
 * @param  {String} markdownPath        Path of the markdown File containing the GUI elements
 * @param  {String} htmlPath            Path of the HTML file containing the GUI layout
 * @param  {String} checkBoxContainerID ID of element to inject the CheckBoxContainer into
 * @property {Element} rootElement The element the panel has been injected into
 * @property {CheckBoxContainer} checkBoxContainer  The checkBoxContainer created by the panel
 * @return {PanelCheckBoxes}
 */
var PanelCheckBoxes = function(panelName, panelRootID, markdownPath, htmlPath, checkBoxContainerID) {
  Panel.call(this, panelName)

  // This will be the ID from index.html
  this.rootElementID = panelRootID

  this.rootElement = document.getElementById(this.rootElementID)
  this.markdownPath = markdownPath
  this.htmlpath = htmlPath
  this.checkBoxContainerID = checkBoxContainerID

  this.itemsFromMarkdown = null
  this.checkBoxContainer = new gui.CheckBoxContainer()

  /*
    Inject the HTML (panel.html) into the DOM
    Load the GUI elements from file
    Construct the components based on the GUI elements
    Inject the components into the DOM
  */

  /**
   * Inject and initialise the panel
   * @memberof panel.PanelCheckBoxes
   */
  this.load = function() {
    //console.log('Loading')
    gui.injectPage(this.rootElementID, htmlPath)

    this.itemsFromMarkdown = guiLoader.loadItemCollection(this.markdownPath)

    for (var i = 0; i < this.itemsFromMarkdown.length; i++) {
      this.checkBoxContainer.addItem(this.itemsFromMarkdown[i].title, false)
    }

    this.applyStyle()
    this.inject()
  }

  /**
   * Apply style to the elements of the panel
   * @memberof panel.PanelCheckBoxes
   */
  this.applyStyle = function() {

    // Apply background to checkBoxContainer
    this.checkBoxContainer.rootElement.setAttribute('class', 'card-panel teal lighten-2')

    // Apply Tool Tips
    for (var i = 0; i < this.checkBoxContainer.items.length; i++) {
      this.checkBoxContainer.items[i].labelElement.setAttribute('class', 'tooltipped black-text')
      this.checkBoxContainer.items[i].labelElement.setAttribute('data-position', 'top')
      this.checkBoxContainer.items[i].labelElement.setAttribute('data-delay', '50')
      this.checkBoxContainer.items[i].labelElement.setAttribute('data-tooltip', this.itemsFromMarkdown[i].items[0])
    }
  }

  /*
    Inject the constructed components into the DOM
  */

 /**
  * Inject the Components into the DOM
  * @memberof panel.PanelCheckBoxes
  */
  this.inject = function() {
    //console.log(this.checkBoxContainerID)
    document.getElementById(this.checkBoxContainerID).appendChild(this.checkBoxContainer.rootElement)
  }

  /**
   * Get the items that have been checked in the container
   * @memberof panel.PanelCheckBoxes
   * @return {Array} Array of CheckBox labels that have been checked
   */
  this.getCheckedItems = function() {
    return this.checkBoxContainer.getCheckedItems()
  }

  /*
    Return the internal state as markdown

    ```
    # this.panelName
    - Administrator
    - Collector
    ```
  */

 /**
  * Get the internal state as markdown
  * @memberof panel.PanelCheckBoxes
  * @return {String} Internal State as markdown
  */
  this.getStateAsMarkdown = function() {

    var markdown = ''
    markdown += '# ' + this.name + '\n'

    var items = this.getCheckedItems()

    for (var i = 0; i < items.length; i++) {
      markdown += '- ' + items[i] + '\n'
    }

    return markdown
  }

  /*
    Sets the internal state from markdown obtained from getStateAsMarkdown()

    ```
    - Item A
    - Item B
    - Item C
    ```
  */

 /**
  * Set the internal state
  * @memberof panel.PanelCheckBoxes
  * @param  {String} markdown The markdown representing the state
  */
  this.setStateFromMarkdown = function(markdown) {

    if (markdown == null) {
      return false
    }

    var lines = markdown.split('\n')

    for (var i = 0; i < lines.length; i++) {
      var lineParts = lines[i].split(' ')

      if (lineParts[0] == '-') {
        var itemName = lineParts.slice(1, lineParts.length).join(' ')
        this.checkBoxContainer.setCheckStateByText(itemName, true)
      }
    }
  }
}

var PanelQuestions = function(panelName, panelRootID, markdownPath, htmlPath, questionContainerID) {
  Panel.call(this, panelName)

  this.rootElementID = panelRootID
  this.rootElement = null


  this.questionContainerID = questionContainerID
  this.markdownPath = markdownPath
  this.htmlPath = htmlPath

  this.questionContainer = null

  this.questionsFromMarkdown = []

  this.load = function() {
    gui.injectPage(this.rootElementID, this.htmlPath)
    this.rootElement = document.getElementById(this.rootElementID).firstElementChild

    var data = guiLoader.loadItemCollection(this.markdownPath)

    this.questionContainer = new gui.QuestionContainer()

    for (var i = 0; i < data[0].items.length; i++) {
      this.questionsFromMarkdown.push(data[0].items[i])
      this.questionContainer.addQuestion(data[0].items[i])
    }

    this.inject()
  }

  this.inject = function() {
    this.rootElement.appendChild(this.questionContainer.rootElement)
  }

  this.getQuestions = function() {
    return this.questionContainer.questions
  }

  /*
    ### Question Title
    - Line A
    - Line B
    - Line C
  */

  this.getStateAsMarkdown = function() {
    var markdown = '# ' + this.name + '\n'

    var qs = this.questionContainer.questions
    for (var i = 0; i < qs.length; i++) {
      markdown += '### ' + qs[i].title + '\n'

      var tmpVal = qs[i].getAnswer().split('\n')

      for (var j = 0; j < tmpVal.length; j++) {
        markdown += '- ' + tmpVal[j] + '\n'
      }

    }

    return markdown
  }

  /*
  ### title
  - Line A
  - Line B
   */
  this.setStateFromMarkdown = function(markdown) {
    var itemCollection = guiLoader.loadItemCollectionMarkdown(markdown)

    //console.log(itemCollection)
    if (itemCollection == null) {
      return null
    }

    for (var i = 0; i < itemCollection.length; i++) {

      var ans = ''

      if (itemCollection[i] != null) {
        var ans = itemCollection[i].items.join('\n')

      }

      this.questionContainer.setAnswerForTitle(itemCollection[i].title, ans)
    }
  }

}

module.exports.Panel = Panel
module.exports.PanelCheckBoxes = PanelCheckBoxes
module.exports.PanelQuestions = PanelQuestions
