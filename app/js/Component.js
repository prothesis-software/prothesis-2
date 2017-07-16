module.exports = class Component {

    constructor() {
        'use strict';

        // Add static member to Component Class
        if (!Component.hasOwnProperty("_idCounter")) {
            Component._idCounter = 0;
        }

        // Add static member to Component Class
        if (!Component.hasOwnProperty("_componentList")) {
            Component._componentList = [];
        }
        Component._componentList.push(this);

        // Create a root element and assign an id
        this._id = Component._idCounter++;

        this._rootElement = document.createElement('div');
        this._rootElement.setAttribute('id', 'root_' + this._id);
    }

    getId() {
        'use strict';
        return this._id;
    }

    static getComponentById(id) {
        'use strict';
        for (let i = 0; i < this._componentList.length; i++) {
            if (this._componentList[i].getId() == id) {
                return this._componentList[i];
            }
        }

        return null;
    }

    getRootElement() {
        'use strict';
        return this._rootElement;
    }

    _validate(types, values) {
        'use strict';
        let result = true;

        for (let i = 0; i < types.length; i++) {
            if (typeof values[i] !== types[i]) {
                console.error(`Invalid arguments passed to ${this.constructor.name} in position ${i}
    Expected ${types[i]}, receieved ${typeof values[i]} (${values[i]})`);
                result =  false;
            }
        }

        return result;
    }

    setState(state) {
        'use strict';
        console.error(`Not implemented in ${this.constructor.name}`);
    }

    getState(state) {
        'use strict';
        console.error(`Not implemented in ${this.constructor.name}`);
    }

};
