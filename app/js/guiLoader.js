/** @module guiLoader */

/*
  This module defines how to load different formats of data from markdown files

  The respective panel.js will use this module to get data required to construct
  the GUI
*/

var fs = require('fs')
var utils = require('./utils.js')

/*
  ItemCollection
    - title (string)
    - items (Array)

  DESCRIPTION:
    Used for reading documents containing checkboxes
*/

/**
 * ItemCollection Object
 * @class
 * @memberof guiLoader
 */
var ItemCollection = function() {

  this.title = null
  this.items = null

  /**
   * Set the title of the items
   * @memberof guiLoader.ItemCollection
   * @param  {String} title
   */
  this.setTitle = function(title) {
    this.title = title
  }

  /**
   * Add an item to the currentItemCollection
   * @param  {String} item
   * @memberof guiLoader.ItemCollection
   */
  this.addItem = function(item) {
    if (this.items === null) {
      this.items = []
    }

    this.items.push(item)
  }
}

/*

  loadItemCollection

  DESCRIPTION:
    Reads markdown files with the following format into an array of ItemCollection
    ```
    ### <Title>
    - <Item 1>
    - <Item 2>
    ```
*/

/**
 * Parse markdown and return an array of ItemCollection
 * @memberof guiLoader
 * @param  {String} filePath markdown path
 * @returns {ItemCollection[]}
 */
function loadItemCollection(filePath) {

  var data = utils.read(filePath)
  var lines = data.split('\n')

  var itemCollections = []
  var currentItemCollection = null

  for (i = 0; i < lines.length; i++) {

    var lineParts = lines[i].split(' ')

    if (lineParts[0] == '###') {
      var title = lineParts.slice(1, lineParts.length).join(' ')

      if (currentItemCollection != null) {
        itemCollections.push(currentItemCollection)

      }

      currentItemCollection = new ItemCollection()
      currentItemCollection.setTitle(title)

    } else if (lineParts[0] == '-') {
      var itemText = lineParts.slice(1, lineParts.length).join(' ')
      currentItemCollection.addItem(itemText)

      if (i == lines.length - 1) {
        itemCollections.push(currentItemCollection)
      }
    }
  }

  // Push the last item
  itemCollections.push(currentItemCollection)

  return itemCollections
}


module.exports.loadItemCollection = loadItemCollection
