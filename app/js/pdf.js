// Migrating from jspdf to html-pdf
// Sample file.

var _fs = require('fs');
var _pdf = require('html-pdf');
const utils = require('./utils.js');
class pdf {
     constructor() {
          this._buffer = "";
          this._options = {
               format: 'A4'
          };
     }

     addHTML(text) {
          this._buffer += text;
     }

     create(name) {
          _pdf.create(this._buffer, this._options).toFile(name, function(err, res) {
               if (err)
                    console.log("An error " + err + " occured.");
          });
     }

     _getBuffer(){
          return this._buffer;
     }

     _setBuffer(buffer){
          this._buffer = buffer;
     }

     _setOptions(opt){
          this._options = opt;
     }
