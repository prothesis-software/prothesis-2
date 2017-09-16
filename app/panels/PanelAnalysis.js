const Panel = require(path.join(ROOT, 'app/js/Panel.js'));

module.exports = class PanelAnalysis extends Panel {

    /*
    A demo function for fancy features
    */
    doSpecialStuff() {

        let elem = document.getElementById('woo_flashing_html');

        if (elem !== null) {
            if (this.someSpecialVar) {
                document.getElementById('woo_flashing_html').style.backgroundColor = "red";

            } else {
                document.getElementById('woo_flashing_html').style.backgroundColor = "green";
            }
        }

        this.someSpecialVar = !this.someSpecialVar;

        setInterval(this.doSpecialStuff, 500);
    }

    constructor(guiKey) {
        super();
        this._guiKey = guiKey;

        const Utils = require(path.join(ROOT, 'app/js/utils.js'));

        let html = Utils.read(path.join(ROOT, 'app/panels/analysis.html'));
        this.getRootElement().innerHTML = html;

        this.someSpecialVar = 1;
        this.doSpecialStuff();
    }

    loadGUI(state) {
        console.error("loadGUI() Not implemented in PanelAnalysis.js");

        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
            return false;
        } else {
            let data = state[this._guiKey];
            // More code here...
        }
    }

    getState() {
        let data = {};
        console.error("getState() Not implemented in PanelAnalysis.js");
        // More code here...
        return data;
    }

    setState(state) {
        console.error("setState() Not implemented in PanelAnalysis.js")

        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
            return false;
        }

        let items = state[this._guiKey];

        // More code here...

        return true;

    }


};
