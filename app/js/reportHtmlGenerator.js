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
	// this._userdata is a json object.
	let size = this._userdata['Dreams'].length;
	for(i = 0; i < size ; i++){
		let str = this._md('# ' + this._userdata['Dreams'][i]['Title']);
		str += this._userdata['Dreams'][i]['Answer'];
		this._buffer += str;
	}
}

reportHtmlGenerator.prototype._loadDreams = function(dreams) {
		
}

reportHtmlGenerator.prototype.save = function(filename) {
	this._finalise();

	this._utils.write(filename, this._buffer);
}

var re = new reportHtmlGenerator('../../userData.json');
re.load();
re.save('./report.pdf.html');
