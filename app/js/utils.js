/** @module utils*/


var _fs = require('fs');

/*
     A syncronous function to
     read from a file; Returns
     the buffer and omits any
     kind of error handling.

     Yes, sync code in node.
     No, not async code in node.
     Kys.
*/

/**
 * Read contents of file
 * @param  {String} filePath Path of filePath
 * @return {String}          Contents of file
 * @memberof utils
 */
function read(filePath){
     var path = require('path')
     return String(_fs.readFileSync(filePath));
}

/*
     A function which uses this
     silly retarded JSON.parse()
     method.
*/
function strjson(str){
     return JSON.parse(str);
}

/*
     Does this close file descriptors?
     Oh I don't care ! :D
*/

/**
 * Write data to a file
 * @param  {String} filename filePath
 * @param  {*} buffer   Data to write
 * @memberof utils
 */
function write(filename, buffer){
     return _fs.writeFileSync(filename, buffer);
}

var AssocItem = function(name, data) {
  this.name = name
  this.data = data
}

/*
  An Object that acts as an Associative Array

  assoc.getByName('lolcat') // Returns the data part of the AssocItem
*/

/**
 * Associative Array
 * @class
 * @memberof utils
 */
var AssocArray = function() {

  /**
   * Array for storing {@link AssocItem}
   * @member {Array}
   * @private
   */
  this._items = []

  /**
   * Return element by name
   * @memberof utils.AssocArray
   * @param  {String} name Key of element
   * @returns {*|Null}      The original data If it exists, otherwise Null
   */
  this.getByName = function(name) {

    for (var i = 0; i < this._items.length; i++) {
      if (this._items[i].name == name) {
        return this._items[i].data
      }
    }

    return null
  }

  /**
   * Get element given its index
   * @memberof utils.AssocArray
   * @param  {int} index The index of the element
   * @return {*}       Original data
   * @todo Handle index out of bounds
   */
  this.getByIndex = function(index) {
    return this.items[index].data
  }

  /**
   * Add an element to the Associative AssocArray
   * @memberof utils.AssocArray
   * @param  {String} name The key of the data
   * @param  {*} data Data to store
   * @return {undefined}
   */
  this.push = function(name, data) {
    var newItem = new AssocItem(name, data)
    this.items.push(newItem)
  }

  /**
   * Returns the count of items stored
   * @memberof utils.AssocArray
   * @return {int} Number of items in array
   */
  this.getLength = function() {
    return this.items.length
  }

}

module.exports.read = read;
module.exports.strjson = strjson;
module.exports.write = write;
module.exports.AssocArray = AssocArray
