/** @module reportHtmlGenerator */

function reportHtmlGenerator(userdata){
	this._buffer = "<html>";
	this._path = require('path');
	this._utils = require('./utils.js'); //TODO: Fix me!
	this._userdata = this._utils.read(userdata);
}

reportHtmlGenerator.prototype._finalise = function(){

}

reportHtmlGenerator.prototype.load = function(){
	var json_buffer = this._utils.strjson(this._userdata);

	this._loadDreams(json_buffer['Dreams']);

	this._finalise();
}

reportHtmlGenerator.prototype._loadDreams = function(dreams){
	let md = require('marked');

	this._buffer = ;	// Read file here

	md.setOptions({
  renderer: new md.Renderer(),
  gfm: true,
  tables: true,
  breaks: false,
  pedantic: false,
  sanitize: true,
  smartLists: true,
  smartypants: false,
  highlight: function (code) {
  return require('highlight.js').highlightAuto(code).value;
  }
});


	this._buffer += md(`
\`\`\`cpp
int a = 5;
std::cout << "ok\n";

\`\`\`
	`);

	this._buffer += md('# h1');
	this._buffer += md('> lolcat ok ');
	this._buffer += "</article></body></html>"


}

reportHtmlGenerator.prototype.save = function(filename){
	this._utils.write(filename + ".html", this._buffer);

	var fs = require('fs');
	var pdf = require('html-pdf');
	var options = { "base": `file:///home/evert/github/prothesis-2/app/frameworks/css` };

	pdf.create(this._buffer, options).toFile(filename, function(err, res) {
	  if (err) return console.log(err);
	  console.log(res); // { filename: '/app/businesscard.pdf' }
	});

}

var re = new reportHtmlGenerator('../../userData.json');

re.load();
re.save("report.pdf");
