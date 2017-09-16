const Component = require(path.join(ROOT, 'app/js/Component.js'));

/**
 * DropDownQuestion GUI Component
 * @type {DropDownQuestion}
 */
module.exports = class DropDownQuestion extends Component {

    constructor(title, options) {
        'use strict';
        super();
        this._validate(['string'], [title]);

        this._title = title;
        this._options = options;
        this._selected = "";

        /*
        <select>
          <option value="" disabled selected>Choose your option</option>
          <option value="1">Option 1</option>
          <option value="2">Option 2</option>
          <option value="3">Option 3</option>
        </select>
        <label>Materialize Select</label>
        */

        // class="browser-default" does not appear to work with dynamically added select elements
        this._html = `<div class="row"><div class="input-field col s12 m6 l3">
        <select id="select_${this._id}"><option value="" disabled selected>Choose</option>`;

        for (var i = 0; i < this._options.length; i++) {
          this._html += '<option value="' + this._options[i] + '">' + this._options[i] + '</option>';
        }

        this._html += '</select></div></div>';

        this.getRootElement().innerHTML = this._html;

        this._selectElement = this.getRootElement().querySelector(`#select_${this._id}`);

        this._initSelect();
    }

    // This function will be executed every x time units untill
    // we successfully fixed the materializecss
    // Repeat until element has been added to the DOM
    _initSelect() {
        let elem = document.getElementById(`select_${this._id}`);

        if (elem != null) {

            $(elem).material_select();
            $(elem).on('change', this._onChangeHandler);

       } else {
            setTimeout(this._initSelect.bind(this), 500);
        }
    }

    // Attached to the checkbox!
    _onChangeHandler(e) {
        'use strict';

        console.log($('#'+ this.id).val());

        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        Component.getComponentById(id).setValueState($('#'+ this.id).val());

    }

    /**
     * Set the state of the selction
     * @param {string} sel
     */
    setValueState(sel) {
        'use strict';

        this._selected = sel;
        this._selectElement.value = sel;
    }

    /**
     * Get the check state of the box
     * @return {string}
     */
    getSelected() {
        'use strict';
        return this._selected;
    }

    /**
     * Get the options of the box
     * @return {string}
     */
    getOptions() {
        'use strict';
        return this._options;
    }

    getTitle() {
        return this._title;
    }

};
