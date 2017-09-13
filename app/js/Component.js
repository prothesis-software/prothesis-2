/**
 * The base object for GUI elements that have a HTML component
 * @type {Component}
 */
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
        this._rootElement.setAttribute('style', 'padding: 5px');
    }

    /**
     * Returns the id of the component
     * @return {int}
     */
    getId() {
        'use strict';
        return this._id;
    }

    /**
     * Returns the component with the given id
     * @param  {int} id ID of the component to find
     * @return {component}
     */
    static getComponentById(id) {
        'use strict';
        for (let i = 0; i < this._componentList.length; i++) {
            if (this._componentList[i].getId() == id) {
                return this._componentList[i];
            }
        }

        return null;
    }

    /**
     * Returns the root element of the component
     * @return {Element} HTML element
     */
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

    /**
     * Sets the state according the the given JSON object
     * @param {Object} state JSON Object
     * @example
     * myComp.setState({ Roles: ["Manager", "Leader"] } );
     */
    setState(state) {
        'use strict';
        console.error(`Not implemented in ${this.constructor.name}`);
    }

    /**
     * Returns the state of the object in JSON
     * @return {Object}
     */
    getState() {
        'use strict';
        console.error(`Not implemented in ${this.constructor.name}`);
    }

};
