/** @module reportHtmlGenerator */
module.exports = class reportHtmlGenerator {
    constructor(userdata) {
        this._path = require('path');
        this._utils = require('./utils.js'); //TODO: Fix me!
        this._buffer = this._utils.read(this._path.join(ROOT, 'app/resources/styling.html'));
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

    _finalise() {
        this._buffer += "</article></body></html>";
    }

    load() {
        /*
         * Uses the constructor name to determine what to
         * do with the object.
         **/
        for (let i = 0; i < dataManager._panels.length; i++)
            this.handle(dataManager._panels[i]);
    }


    handle_questions(panel) {
        let data = panel.getState();
        let name = panel._guiKey.replace("_", " ");
        this._buffer += this._md("### " + name);

        for (let i = 0; i < data[panel._guiKey].length; i++) {
            this._buffer += this._md("##### " + data[panel._guiKey][i]['Title']);
            this._buffer += this._md("```\n" + data[panel._guiKey][i]['Answer'] + "\n```\n");
        }
    }

    handle_checkboxes(panel) {
        let data = panel.getState();
        let name = panel._guiKey.replace("_", " ");
        this._buffer += this._md("### " + name);

	for(let i = 0; i < data[panel._guiKey].length; i++)
	    this._buffer += this._md("- " + data[panel._guiKey][i]);
    }

    handle(panel) {
        let name = panel.constructor.name.slice(5);
        if (name === "Checkboxes")
            this.handle_checkboxes(panel);
        if (name === "Questions" || name === "SpokenWords")
            this.handle_questions(panel);
    }

    save(filename) {
        this._finalise();

        this._utils.write(filename, this._buffer);
    }
}
