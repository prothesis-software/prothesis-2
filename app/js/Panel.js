const Component = require(path.join(ROOT, 'app/js/Component.js'));

module.exports = class Panel extends Component {

    constructor() {
        super();
    }

    loadGUI(state) {
        console.error(`Not implemented in ${this.constructor.name}`);
    }
};
