const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const QuestionContainer = require(path.join(ROOT, 'app/js/QuestionContainer.js'));
const NumericalQuestionsContainer = require(path.join(ROOT, 'app/js/Containers/NumericalQuestionsContainer.js'));
const EmailQuestionsContainer = require(path.join(ROOT, 'app/js/Containers/EmailQuestionsContainer.js'));

module.exports = class PanelDetails extends Panel {

    constructor(guiKey) {
        super();

        this._questionsContainer = new QuestionContainer();
        this._numericalQuestionsContainer = new NumericalQuestionsContainer();
        this._emailquestionsContainer = new EmailQuestionsContainer();

        this._guiKey = guiKey;

        this.getRootElement().appendChild(this._questionsContainer.getRootElement());
        this.getRootElement().appendChild(this._numericalQuestionsContainer.getRootElement());
        this.getRootElement().appendChild(this._emailquestionsContainer.getRootElement());
    }

    // expects an array of questions
    loadGUI(state) {
        'use strict';
        /*
        Roles : [{Description: "A",
                    "Tooltip": "B"}]
         */
         /*
         {
           "Details":[
                   {"Questions":["Name", "Surname"]},
                   {"NumericalQuesitons": ["Age"]},
                   {"EmailQuesiton": ["Email"]}
           ]
         }
         */
         if (!state.hasOwnProperty(this._guiKey)) {
             console.error(`Could not find ${this._guiKey} in ${state}`);
         } else {

             let items = state[this._guiKey];

             for (let i = 0; i < items.length; i++) {
                 if (items[i].hasOwnProperty('Questions')) {
                     for (let x = 0; x < items[i].Questions.length; x++) {
                       this._questionsContainer.addItem(items[i].Questions[x]);
                     }

                 }

                 if (items[i].hasOwnProperty('NumericalQuestions')) {
                       for (let x = 0; x < items[i].NumericalQuestions.length; x++) {
                         this._numericalQuestionsContainer.addItem(items[i].NumericalQuestions[x]);
                       }
                 }

                 if (items[i].hasOwnProperty('EmailQuestions')) {
                       for (let x = 0; x < items[i].EmailQuestions.length; x++) {
                         this._emailquestionsContainer.addItem(items[i].EmailQuestions[x]);
                       }
                 }
             }
         }
    }

    getState() {
        let data = {};

        data[this._guiKey] = [
          {Questions: this._questionsContainer.getState()},
          {NumericalQuestions: this._numericalQuestionsContainer.getState()},
          {EmailQuestions: this._emailquestionsContainer.getState()}
        ];

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

          if (items[i].hasOwnProperty('Questions')) {
              for (let x = 0; x < items[i].Questions.length; x++) {
                this._questionsContainer.setAnswerByTitle(items[i].Questions[x].Title, items[i].Questions[x].Answer);
              }
          }


          if (items[i].hasOwnProperty('NumericalQuestions')) {
            for (let x = 0; x < items[i].NumericalQuestions.length; x++) {
              this._numericalQuestionsContainer.setAnswerByTitle(items[i].NumericalQuestions[x].Title, items[i].NumericalQuestions[x].Answer);
            }
          }

          if (items[i].hasOwnProperty('EmailQuestions')) {
            for (let x = 0; x < items[i].EmailQuestions.length; x++) {
              this._emailquestionsContainer.setAnswerByTitle(items[i].EmailQuestions[x].Title, items[i].EmailQuestions[x].Answer);
            }
          }

            /*if (items[i].hasOwnProperty('Title') && items[i].hasOwnProperty('Answer')) {
                this._questionsContainer.setAnswerByTitle(items[i].Title, items[i].Answer);
            } else {
                console.error('Invalid object! ');
                console.error(items[i]);
                return false;
            }*/
        }
    }

};
