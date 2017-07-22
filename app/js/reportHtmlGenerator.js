/** @module reportHtmlGenerator */

function reportHtmlGenerator(userdata){
	this._buffer = "<html>";
	this._path = require('path');
	this._utils = require('./utils.js'); //TODO: Fix me!
	this._userdata = this._utils.read(userdata);		
}

reportHtmlGenerator.prototype._finalise = function(){
	reportHtmlGenerator._buffer += "</html>"
}

reportHtmlGenerator.prototype.load = function(){
	var json_buffer = this._utils.strjson(this._userdata);
	
	this._loadDreams(json_buffer['Dreams']);

	this._finalise();
}

reportHtmlGenerator.prototype._loadDreams = function(dreams){
	this._buffer += "<div id=\"Dreams\"><h>Dreams</h>";
	this._buffer += "<form>";
	for(var i in dreams){
		var title = dreams[i]['Title'];
		var ans = dreams[i]['Answer'];

		this._buffer += title;
		this._buffer += "<input type=\"text\" value=\"" + ans + "\"><br>" 
	}
	this._buffer += "</form>"
	this._buffer += "</div>"
}

reportHtmlGenerator.prototype.save = function(filename){
	this._utils.write(filename, this._buffer);
}
	
var re = new reportHtmlGenerator('../../userData.json');
re.load();
re.save("report.html");
