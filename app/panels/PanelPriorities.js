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

    }

    loadGUI(state) {

    }

    getState() {

    }

    setState(state) {


    }

};
