const Component = require(path.join(ROOT, 'app/js/Component.js'));

/**
 * The base Panel object
 * @type {Panel}
 */
module.exports = class Panel extends Component {

    /**
     * Create a new Panel
     * @return {Panel}
     */
    constructor() {
        super();
    }

    /**
     * Set the GUI given a JSON object
     * @param  {object} state JSON object
     * @return {undefined}
     */
    loadGUI(state) {
        console.error(`Not implemented in ${this.constructor.name}`);
    }

    /**
     * Set the state of the panel given the user data
     * @param {object} state JSON object
     */
    setState(state) {
        console.error(`Not implemented in ${this.constructor.name}`);
    }

    /**
     * Get the state in JSON form object
     * @return {object}
     */
    getState() {
        console.error(`Not implemented in ${this.constructor.name}`);
    }
};