const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const OrderedItemContainer = require(path.join(ROOT, 'app/js/OrderedItemContainer.js'));


module.exports = class PanelPriorities extends Panel {

    constructor(guiKey) {
        super();
        this._guiKey = guiKey;

        const Utils = require(path.join(ROOT, 'app/js/utils.js'));

        let html = Utils.read(path.join(ROOT, 'app/panels/priorities.html'));
        this.getRootElement().innerHTML = html;

        this._orderedItemContainer = new OrderedItemContainer();

        this.getRootElement().appendChild(this._orderedItemContainer.getRootElement());

        // NOTE: What hacks are this?
        this._orderedItemContainer.setUnsortedElement($(this.getRootElement()).find('#priorities_unsorted').get(0));
        this._orderedItemContainer.setSortedElement($(this.getRootElement()).find('#priorities_sorted').get(0));

        global.kek = this._orderedItemContainer;
    }

    loadGUI(state) {
        'use strict';
        /*
        Priorities : ["A", "B"]
         */

         if (!state.hasOwnProperty(this._guiKey)) {
             console.error(`Could not find ${this._guiKey} in ${state}`);
         } else {

             let items = state[this._guiKey];

             for (let i = 0; i < items.length; i++) {

                 this._orderedItemContainer.addItem(items[i], -1);
             }
         }
    }

    getState() {
        let data = {};

        data[this._guiKey] = this._orderedItemContainer.getState();

        return data;
    }

    setState(state) {


        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
            return false;
        }

        let items = state[this._guiKey];

        for (let i = 0; i < items.length; i++) {
            let item = this._orderedItemContainer.getItemByDescription(items[i]);
            this._orderedItemContainer.addItemHandler(item);
        }

        return true;

    }

};
