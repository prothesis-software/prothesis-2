const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const QuestionContainer = require(path.join(ROOT, 'app/js/QuestionContainer.js'));

module.exports = class PanelQuestions extends Panel {

    constructor(guiKey) {
        super();

        this._questionsContainer = new QuestionContainer();
        this._guiKey = guiKey;
        this.getRootElement().appendChild(this._questionsContainer.getRootElement());
    }

    // expects an array of questions
    loadGUI(state) {
        'use strict';

        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
        } else {

            let items = state[this._guiKey];

            for (let i = 0; i < items.length; i++) {

                this._questionsContainer.addItem(items[i]);
            }
        }
    }

    getState() {
        let data = {};
        data[this._guiKey] = this._questionsContainer.getState();
        console.log(data);
        return data;

    }

    setState(state) {
        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find "${this._guiKey}" in ${state}`);
            return false;
        }

        // Array of objects
        let items = state[this._guiKey];

        for (let i = 0; i < items.length; i++) {
            if (items[i].hasOwnProperty('Title') && items[i].hasOwnProperty('Answer')) {
                this._questionsContainer.setAnswerByTitle(items[i].Title, items[i].Answer);
            } else {
                console.error('Invalid object! ');
                console.error(items[i]);
                return false;
            }
        }
    }

};