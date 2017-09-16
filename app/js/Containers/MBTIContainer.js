const Component = require(path.join(ROOT, 'app/js/Component.js'));
const DropDownQuestion = require(path.join(ROOT, 'app/js/Questions/DropDownQuestion.js'));

module.exports = class MBTIContainer extends Component {

    constructor() {
        super();
        this.getRootElement().innerHTML += '<p class="flow-text">MBTI Selection</p>';
        this._items = [];
    }

    addItem(title, options) {
        'use strict';

        let tmpQuestion = new DropDownQuestion(title,options);
        this._items.push(tmpQuestion);
        this.getRootElement().appendChild(tmpQuestion.getRootElement());
    }

    getItems() {
        return this._items;
    }

    setAnswerByTitle(title, answer) {

        for (let i = 0; i < this._items.length; i++) {
            if (this._items[i].getTitle() === title) {
                this._items[i].setValueState(answer);
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
            tmpObj.Answer = this._items[i].getSelected();

            data.push(tmpObj);
        }

        return data;
    }

};
