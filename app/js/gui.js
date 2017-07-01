/** @module gui */

var globalIDCounter = 0

/*
  This module defines basic components for building a GUI.
  For example a container for checkboxes.

  A component has the following roles
    - Maintain an internal state (Answers, checked boxes etc)
    - Update the state based on DOM events (When answer changes, box is checked etc)
    - Provide an interface to update the internal state
      - Update the DOM when the internal state is changed
    - Provide a rootElement to be injected to other modules
    - It may inject other components, but should not inject itself

  A Component generally has the following HTML structure:

    <div id='root_x'> // rootElement
      <div id='Label_x'>
        ...
      </div>

      <div id='CheckBox_x'>
        ...
      </div>
    </div>

    The IDs for the components are automatically generated
*/



/*
  Reads a file and inserts the file contents into the DOM as
  children of the given hostElementID
*/

/** @function injectPage
 * Load HTML from file and inject into DOM
 * @memberof gui
 * @param  {String} hostElementID The element ID to inject into
 * @param  {String} HTMLFilePath  Path of the HTML file
 */
var injectPage = function (hostElementID, HTMLFilePath) {
  var path = require('path')

  var utils = require(path.join(ROOT, 'app/js/utils.js'))

  console.log('Injecting ' + HTMLFilePath + ' into ' + hostElementID)

  var element = document.getElementById(hostElementID)
  var data = utils.read(HTMLFilePath)

  element.innerHTML = data
}

/**
 * The base Object for GUI components
 * @class
 * @abstract
 * @memberof gui
 * @property {Element} rootElement  - The root element of the Component
 */
var Component = function() {
  var COMPONENT_ROOT_PREFIX = 'gui_root_'

  this.id = globalIDCounter++

  // Create the root element
  this.rootElement = document.createElement('div')
  this.rootElement.setAttribute('id', COMPONENT_ROOT_PREFIX + this.id)

}

/*
# CheckBox

## State
  - id (integer)
  - text (string)
  - checked (boolean)
  - rootElement (element)
  - labelElement (element)
  - checkBoxElement (element)
  - changeEventHandler (function)

## HTML Structure
div (rootElement)
  label
  input type=checkbox

### Example
  <div id='root_55'>
    <label>
    <input type='checkbox'
*/

/**
 * CheckBox GUI component
 * @extends Component
 * @class
 * @memberof gui
 * @param  {String} text    The label of the CheckBox
 * @param  {Boolean} checked State of the checkbox
 */
var CheckBox = function(text, checked) {
  Component.call(this)
  var LABEL_PREFIX = 'gui_label_'
  var CHECKBOX_PREFIX = 'gui_checkbox_'

  this.text = text
  this.checked = checked
  this.changeEventHandler = null

  // Need to use _this for event callbacks, as this gets replaced with the triggering element
  var _this = this
  this.onChangeHandler = function(e) {
    _this.checked = this.checked
  }

  /**
   * Set the state of the checkBox
   * @param  {Boolean} checked State of the check box
   * @memberof gui.CheckBox
   */
  this.setCheckState = function(checked) {
    this.checked = checked
    this.checkBoxElement.checked = checked
  }

  /**
   * Create the HTML element for the CheckBox
   * @private
   * @param  {int} id      The id of the CheckBox
   * @param  {Boolean} checked State of box
   * @return {Element}         A CheckBox Element
   */
  this.createCheckBoxElement = function(id, checked) {
    var chkElem = document.createElement('input')
    chkElem.setAttribute('id', CHECKBOX_PREFIX + id)

    chkElem.setAttribute('type', 'checkbox')
    chkElem.checked = checked

    return chkElem
  }

  this.createLabelElement = function(id, text) {
    var lbl = document.createElement('label')
    lbl.setAttribute('id', LABEL_PREFIX + id)
    lbl.setAttribute('for', CHECKBOX_PREFIX + id)
    lbl.innerHTML = String(text)

    return lbl
  }

  // Create elements and attach to root
  this.labelElement = this.createLabelElement(this.id, text)
  this.checkBoxElement = this.createCheckBoxElement(this.id, checked)

  this.rootElement.appendChild(this.checkBoxElement)
  this.rootElement.appendChild(this.labelElement)

  // Register event handler to update our internal state
  this.checkBoxElement.addEventListener('change', this.onChangeHandler)
}

/*
  Manages multiple checkboxes
*/

/**
 * Container for CheckBoxes
 * @class
 * @memberof gui
 * @property {CheckBox[]} items - CheckBoxes that are managed by the container
 */
var CheckBoxContainer = function() {
  Component.call(this)

  // Array of CheckBox
  this.items = []

  /**
   * Add a checkbox to the container
   * @param  {String} text    Label of the check box
   * @param  {Boolean} checked State of the box
   * @memberof gui.CheckBoxContainer
   */
  this.addItem = function(text, checked) {
    var chk = new CheckBox(text, checked)
    this.items.push(chk)
    this.rootElement.appendChild(chk.rootElement)
  }

  /**
   * Get all the item labels that are checked
   * @memberof gui.CheckBoxContainer
   * @return {String[]} Array of labels that are checked
   */
  this.getCheckedItems = function() {
    var result = []

    for (var i = 0; i < this.items.length; i++) {
      if (this.items[i].checked) {
        result.push(this.items[i].text)
      }
    }

    return result
  }

  /**
   * Set the Checkbox with the given text to the give state
   * @memberof gui.CheckBoxContainer
   * @param  {String} text  The label of the checkbox to find
   * @param  {Boolean} state State of the box
   * @return {True|False}       True if found, otherwise False
   */
  this.setCheckStateByText = function(text, state) {

    for (var i = 0; i < this.items.length; i++) {
      if (this.items[i].text == text) {
        this.items[i].setCheckState(state)
        return true
      }
    }

    return false
  }
}

/*
  An extension of CheckBoxContainer. Includes a title
*/

/**
 * CheckBoxContainer with a Title_
 * @memberof gui
 * @extends CheckBoxContainer
 * @inheritdoc
 * @class
 * @param  {String} title The title of the CheckBoxContainer
 * @property {CheckBoxContainer} checkBoxContainer
 * @property {Element} titleElement
 * @property {Element} rootElement
 */
var CheckBoxContainerWithTitle = function(title) {
  Component.call(this)

  TITLE_PREFIX = 'Title_'
  CONTAINER_PREFIX = 'CheckBoxContainer_'

  // Wrapper for the CheckBoxContainer

  /**
   * Add checkbox to container
   * @memberof gui.CheckBoxContainerWithTitle
   * @param  {String} text    label
   * @param  {Boolean} checked state
   */
  this.addItem = function(text, checked) {
    this.checkBoxContainer.addItem(text, checked)
  }

  /**
   * Get count of checkboxes
   * @memberof gui.CheckBoxContainerWithTitle
   * @return {int} Number of checkboxes
   */
  this.length = function() {
    return this.checkBoxContainer.length
  }

  this.createContainerElement = function(id) {
    var cont = document.createElement('div')
    cont.setAttribute('id', CONTAINER_PREFIX + id)

    return cont
  }

  this.createTitleElement = function(id, title) {
    var titleElement = document.createElement('div')
    titleElement.setAttribute('id', TITLE_PREFIX + id)
    titleElement.innerHTML = title

    return titleElement
  }

  this.checkBoxContainer = new CheckBoxContainer()

  this.titleElement = this.createTitleElement(this.id, title)

  this.rootElement.appendChild(this.titleElement)
  this.rootElement.appendChild(this.checkBoxContainer.rootElement)

}

module.exports.CheckBox = CheckBox
module.exports.CheckBoxContainer = CheckBoxContainer
module.exports.CheckBoxContainerWithTitle = CheckBoxContainerWithTitle
module.exports.injectPage = injectPage
