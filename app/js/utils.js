/** @module utils*/


var _fs = require('fs');
const NEW_LINE = "\r\n";
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
     return clean_newlines(String(_fs.readFileSync(filePath)));
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
     return _fs.writeFileSync(filename, clean_newlines(buffer));
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
    return this._items[index].data
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
    this._items.push(newItem)
  }

  /**
   * Returns the count of items stored
   * @memberof utils.AssocArray
   * @return {int} Number of items in array
   */
  this.getLength = function() {
    return this._items.length
  }

}



/**
 * clean_newlines
 * @param {String} buffer
 * @return {String}
 * @memberof utils
 */
 function clean_newlines(buffer){
     return _universify(buffer);
}

/**
 * _universify
 * @param {String} buffer
 * @return {String}
 * @memberof utils
 */
function _universify(buffer){ // honestly this could be much cleaner.
     for (var i = 0; i < buffer.length; i++) {              //Pass one checking for new lines without carriage returns
          if(buffer[i] === '\n' && buffer[i-1] !== '\r'){
               buffer = strinsert(buffer,i,"\r");
               i++;
               continue;
          }
     }

     for (var i = 0; i < buffer.length; i++) {              //Pass two checking for carriage returns without new lines.
          if(buffer[i] === '\r' && buffer[i+1] !== '\n'){
               buffer = strinsert(buffer,i+1,"\n");
               i+=2;
               continue;
          }
     }
     return buffer;
}


/**
 * strinsert
 * @param {String} buffer
 * @param {Integer} index
 * @param {String} val
 * @return {String}
 * @memberof utils
 */
 function strinsert(buffer, index, val) {
     return buffer.substr(0, index) + val + buffer.substr(index);
 }


 /**
  * Read contents of file (raw)
  * @param  {String} filePath Path of filePath
  * @return {String}          Contents of file
  * @memberof utils
  */
 function _read(filePath){
      var path = require('path')
      return String(_fs.readFileSync(filePath));
 }

 /*
      A function which uses this
      silly retarded JSON.parse()
      method.
 */

 /**
  * Write data to a file (raw)
  * @param  {String} filename filePath
  * @param  {*} buffer   Data to write
  * @memberof utils
  */
 function _write(filename, buffer){
      return _fs.writeFileSync(filename, buffer);
 }

 function injectPage(hostElementID, HTMLFilePath) {
     let path = require('path');

     let utils = require(path.join(ROOT, 'app/js/utils.js'));

     let element = document.getElementById(hostElementID);
     let data = utils.read(HTMLFilePath);

     element.innerHTML = data;
 }

module.exports.injectPage = injectPage;
module.exports.read = read;
module.exports._read = _read;
module.exports.strjson = strjson;
module.exports._write = _write;
module.exports.write = write;
module.exports.NEW_LINE = NEW_LINE;
module.exports.clean_newlines = clean_newlines;
