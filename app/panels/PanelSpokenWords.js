const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const QuestionContainer = require(path.join(ROOT, 'app/js/QuestionContainer.js'));

module.exports = class PanelSpokenWords extends Panel {

    constructor(guiKey) {
        super();
        this._guiKey = guiKey;

        const Utils = require(path.join(ROOT, 'app/js/utils.js'));

        let html = Utils.read(path.join(ROOT, 'app/panels/spokenWords.html'));
        this.getRootElement().innerHTML = html;
        this._titleElement = this.getRootElement().querySelector('#spoken_words_title');

        this._questionsContainer = new QuestionContainer();
        this.getRootElement().appendChild(this._questionsContainer.getRootElement());

    }

    loadGUI(state) {
        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
            return false;
        } else {
            let data = state[this._guiKey];

            if (data.hasOwnProperty('Title') && data.hasOwnProperty('Questions')) {
                this._titleElement.innerHTML = data.Title;

                for (let i = 0; i < data.Questions.length; i++) {
                    this._questionsContainer.addItem(data.Questions[i]);
                }
            }

        }
    }

    getState() {
        /*
            {
            Spoken_Words: [{Q: A},...],
        }
         */
        let data = {};
        data[this._guiKey] = this._questionsContainer.getState();
        return data;
    }

    setState(state) {

        if (!state.hasOwnProperty(this._guiKey)) {
            console.error(`Could not find ${this._guiKey} in ${state}`);
            return false;
        }

        let items = state[this._guiKey];

        for (let i = 0; i < items.length; i++) {
            if (items[i].hasOwnProperty('Title') && items[i].hasOwnProperty('Answer')) {
                this._questionsContainer.setAnswerByTitle(items[i].Title, items[i].Answer);
            } else {
                console.error('Bad object');
                console.error(items[i]);
                return false;
            }
        }

        return true;

    }

};
