const Component = require(path.join(ROOT, 'app/js/Component.js'));
const Checkbox = require(path.join(ROOT, 'app/js/Checkbox.js'));

module.exports = class CheckboxContainer extends Component {

    constructor() {
        super();

        this._items = [];
    }

    addItem(description, tooltip, checked) {
        'use strict';

        let tmpCheckbox = new Checkbox(description, tooltip, checked);

        tmpCheckbox.getRootElement().setAttribute('class', 'col s4 panel-div');

        this._items.push(tmpCheckbox);

        this.getRootElement().appendChild(tmpCheckbox.getRootElement());
    }

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

    getItemByDescription(desc) {
        'use strict';
        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].getDescription() === desc) {
                return this._items[i];
            }
        }

        return null;
    }

    setCheckedItems(items) {
        'use strict';
        for (let i = 0; i < items.length; i++) {
            let tmpCheckbox = this.getItemByDescription(items[i]);
            tmpCheckbox.setCheckState(true);
        }
    }
};
