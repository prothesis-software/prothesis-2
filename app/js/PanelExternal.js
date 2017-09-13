const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const BasicQuestionContainer = require(path.join(ROOT, 'app/js/Containers/BasicQuestionContainer.js'));
const MBTIContainer = require(path.join(ROOT, 'app/js/Containers/MBTIContainer.js'));

module.exports = class PanelExternal extends Panel {

    constructor(guiKey) {
        super();

        this._questionsContainer = new BasicQuestionContainer();
        this._questionsContainer.getRootElement().innerHTML += "Life Keys";
        this._MBTIContainer = new MBTIContainer();

        this._guiKey = guiKey;

        this.getRootElement().appendChild(this._questionsContainer.getRootElement());
        this.getRootElement().appendChild(this._MBTIContainer.getRootElement());
    }

    // expects an array of questions
    loadGUI(state) {
        'use strict';

        /*
        {
          "External":[
                  {"MBTI": [
                    {"Combination1":["I", "E"]},
                    {"Combination2":["S", "N"]},
                    {"Combination3":["T", "F"]},
                    {"Combination4":["J", "P"]}
                  ]},
                  {"BasicQuestions":["Life Key 1", "Life Key 2", "Life Key 3"]}
          ]
        }
        */

         if (!state.hasOwnProperty(this._guiKey)) {
             console.error(`Could not find ${this._guiKey} in ${state}`);
         } else {

             let items = state[this._guiKey];

             for (let i = 0; i < items.length; i++) {
                 if (items[i].hasOwnProperty('BasicQuestions')) {
                     for (let x = 0; x < items[i].BasicQuestions.length; x++) {
                       this._questionsContainer.addItem(items[i].BasicQuestions[x]);
                     }
                 }
                 if (items[i].hasOwnProperty('MBTI')) {
                     for (let x = 0; x < items[i].MBTI.length; x++) {
                         //console.log(items[i].MBTI[x].Values);
                         this._MBTIContainer.addItem(items[i].MBTI[x].Name, items[i].MBTI[x].Values);
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
