const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const CheckboxContainer = require(path.join(ROOT, 'app/js/CheckboxContainer.js'));

module.exports = class PanelCheckboxes extends Panel {

    constructor(guiKey) {
        'use strict';
        super();

        this._guiKey = guiKey;
        this._checkboxContainer = new CheckboxContainer();
        this.getRootElement().appendChild(this._checkboxContainer.getRootElement());
    }

    loadGUI(state) {
        'use strict';
        /*
        Roles : [{Description: "A",
                    "Tooltip": "B"}]
         */

         if (!state.hasOwnProperty(this._guiKey)) {
             console.error(`Could not find ${this._guiKey} in ${state}`);
         } else {

             let items = state[this._guiKey];

             for (let i = 0; i < items.length; i++) {

                 if (!items[i].hasOwnProperty('Description')) {
                     console.error(`Could not find "Description" in ${items[i]}`);
                 }

                 if (!items[i].hasOwnProperty('Tooltip')) {
                     console.error(`Could not find "Tooltip" in ${items[i]}`);
                 }

                 this._checkboxContainer.addItem(items[i].Description, items[i].Tooltip, false);
             }
         }
    }

    setState(state) {
        'use strict';
        /*
            {Roles: ["A", "B"]}
         */

         if (!state.hasOwnProperty(this._guiKey)) {
             console.error(`Could not find "${this._guiKey}" in ${state}`);
         }

         let items = state[this._guiKey];
         this._checkboxContainer.setCheckedItems(items);

    }

    getState() {
        'use strict';
        let items = this._checkboxContainer.getCheckedItems();

        let result = {};
        result[this._guiKey] = items;

        return result;
    }
};
