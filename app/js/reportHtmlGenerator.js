/** @module reportHtmlGenerator */

function reportHtmlGenerator(userdata) {
    this._path = require('path');
    this._utils = require('./utils.js'); //TODO: Fix me!
    this._buffer = this._utils.read('../resources/styling.html');
    this._userdata = this._utils.strjson(this._utils.read(userdata));
    this._md = require('marked');

    this._md.setOptions({
        renderer: new this._md.Renderer(),
        gfm: true,
        tables: true,
        breaks: false,
        pedantic: false,
        sanitize: true,
        smartLists: true,
        smartypants: false,
        highlight: function(code) {
            return require('highlight.js').highlightAuto(code).value;
        }
    });
}

reportHtmlGenerator.prototype._finalise = function() {
    this._buffer += "</article></body></html>";
}

reportHtmlGenerator.prototype.load = function() {
	// Get the data manager
	let dm = dataManager;
	console.log(dm);		
}

reportHtmlGenerator.prototype.interpet_path_to_type = function(path){
							
}


rtHtmlGenerator.prototype.save = function(filename) {
    this._finalise();

    this._utils.write(filename, this._buffer);
}
