const Component = require(path.join(ROOT, 'app/js/Component.js'));

/**
 * Checkbox GUI Component
 * @type {Checkbox}
 */
module.exports = class Checkbox extends Component {

    /**
     * Creates a new Checkbox
     * @param  {string} description
     * @param  {string} tooltip
     * @param  {boolean} checked
     * @return {Checkbox}
     */
    constructor(description, tooltip, checked) {
        'use strict';
        super();
        this._validate(['string', 'string', 'boolean'], [description, tooltip, checked]);

        this._description = description;
        this._tooltip = tooltip;
        this._checked = checked;


        this._html = `
            <input type="checkbox" class="filled-in" id="checkbox_${this._id}"/>
            <label for="checkbox_${this._id}" class="tooltipped"
            data-position="top" data-delay="50"
            data-tooltip="${this._tooltip}">
                <span class="black-text" id="label_${this._id}">${this._description}</span>
            </label>`;

        this.getRootElement().innerHTML = this._html;

        this._checkboxElement = this.getRootElement().querySelector(`#checkbox_${this._id}`);

        this._checkboxElement.checked = this._checked;
        this._checkboxElement.addEventListener('change', this._onChangeHandler);
    }

    // Attached to the checkbox!
    _onChangeHandler(e) {
        'use strict';
        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        Component.getComponentById(id).setCheckState(this.checked);
    }

    /**
     * Set the state of the checkbox
     * @param {boolean} checked
     */
    setCheckState(checked) {
        'use strict';
        this._checked = checked;
        this._checkboxElement.checked = checked;

    }

    /**
     * Get the check state of the box
     * @return {boolean}
     */
    getCheckState() {
        'use strict';
        return this._checked;
    }

    /**
     * Get the description of the box
     * @return {string}
     */
    getDescription() {
        'use strict';
        return this._description;
    }

};