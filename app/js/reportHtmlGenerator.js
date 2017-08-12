/** @module reportHtmlGenerator */

function reportHtmlGenerator(userdata) {
    this._path = require('path');
    this._utils = require('./utils.js'); //TODO: Fix me!
    this._buffer = this._utils.read('../resources/styling.html');
    this._userdata = this._utils.read(userdata);
    let md = require('marked');

    md.setOptions({
        renderer: new md.Renderer(),
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
    var json_buffer = this._utils.strjson(this._userdata);

    this._loadDreams(json_buffer['Dreams']);
    console.log(json_buffer['Dreams']);

    this._finalise();
}

reportHtmlGenerator.prototype._loadDreams = function(dreams) {



}

reportHtmlGenerator.prototype.save = function(filename) {
    this._utils.write(filename + ".html", this._buffer);

    var fs = require('fs');
    var pdf = require('html-pdf');
    var options = {
        "base": `file:///home/evert/github/prothesis-2/app/frameworks/css`
    };

    pdf.create(this._buffer, options).toFile(filename, function(err, res) {
        if (err) return console.log(err);
        console.log(res); // { filename: '/app/businesscard.pdf' }
    });

}


var re = new reportHtmlGenerator('../../userData.json');

re.load();
re.save("report.pdf");
