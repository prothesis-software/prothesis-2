const Component = require(path.join(ROOT, 'app/js/Component.js'));
const NumericalQuestion = require(path.join(ROOT, 'app/js/Questions/NumericalQuestion.js'));

module.exports = class NumericalQuestionsContainer extends Component {

    constructor() {
        super();

        this._items = [];
    }

    addItem(title) {
        'use strict';

        let tmpQuestion = new NumericalQuestion(title);
        this._items.push(tmpQuestion);
        this.getRootElement().appendChild(tmpQuestion.getRootElement());
    }

    getItems() {
        return this._items;
    }

    setAnswerByTitle(title, answer) {

        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].getTitle() === title) {
                this._items[i].setAnswer(answer);
                return true;
            }
        }

        return false;
    }

    getState() {
        let data = [];

        for (let i = 0; i < this._items.length; i++) {
            let tmpObj = {};
            tmpObj.Title = this._items[i].getTitle();
            tmpObj.Answer = this._items[i].getAnswer();

            data.push(tmpObj);
        }

        return data;
    }

};
