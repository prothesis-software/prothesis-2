const Component = require(path.join(ROOT, 'app/js/Component.js'));
const Checkbox = require(path.join(ROOT, 'app/js/Checkbox.js'));

/**
 * A collection of {Checkbox}
 * @type {CheckboxContainer}
 */
module.exports = class CheckboxContainer extends Component {

    constructor() {
        super();

        this._items = [];
    }

    /**
     * Add a checkbox to the container
     * @param {string} description Description of the textbox
     * @param {string} tooltip     Tooltip for the textbox
     * @param {boolean} checked     Boolean indicating if the box is checked
     */
    addItem(description, tooltip, checked) {
        'use strict';

        let tmpCheckbox = new Checkbox(description, tooltip, checked);

        tmpCheckbox.getRootElement().setAttribute('class', 'col s4 panel-div');

        this._items.push(tmpCheckbox);

        this.getRootElement().appendChild(tmpCheckbox.getRootElement());
    }

    /**
     * Returns an array of descriptions for boxes that have been checked
     * @return {string[]}
     */
    getCheckedItems() {
        'use strict';
        let result = [];

        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].getCheckState()) {
                    result.push(this._items[i].getDescription());
            }
        }

        return result;
    }

    /**
     * Returns the Checkbox with the matching description
     * @param  {string} desc Checkbox description
     * @return {Checkbox}      Matching checkbox
     */
    getItemByDescription(desc) {
        'use strict';
        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].getDescription() === desc) {
                return this._items[i];
            }
        }

        return null;
    }

    /**
     * Set all items that have a matching description to checked
     * @param {string[]} items Array of checkbox descriptions
     */
    setCheckedItems(items) {
        'use strict';
        for (let i = 0; i < items.length; i++) {
            let tmpCheckbox = this.getItemByDescription(items[i]);
            tmpCheckbox.setCheckState(true);
        }
    }
};
