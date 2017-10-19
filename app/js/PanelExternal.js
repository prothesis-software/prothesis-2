const Panel = require(path.join(ROOT, 'app/js/Panel.js'));
const BasicQuestionContainer = require(path.join(ROOT, 'app/js/Containers/BasicQuestionContainer.js'));
const MBTIContainer = require(path.join(ROOT, 'app/js/Containers/MBTIContainer.js'));

module.exports = class PanelExternal extends Panel {

    constructor(guiKey) {
        super();

        this._questionsContainer = new BasicQuestionContainer();
        this._questionsContainer.getRootElement().innerHTML += '<p class="flow-text">Enter your Life Keys</p>';
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
                 if (items[i].hasOwnProperty('MBTIQuestions')) {
                     for (let x = 0; x < items[i].MBTIQuestions.length; x++) {
                         this._MBTIContainer.addItem(items[i].MBTIQuestions[x].Name, items[i].MBTIQuestions[x].Values);
                      }
                 }
             }
         }
    }

    getState() {
        let data = {};

        data[this._guiKey] = [
          {BasicQuestions: this._questionsContainer.getState()},
          {MBTIQuestions: this._MBTIContainer.getState()}
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

          if (items[i].hasOwnProperty('BasicQuestions')) {
              for (let x = 0; x < items[i].BasicQuestions.length; x++) {
                this._questionsContainer.setAnswerByTitle(items[i].BasicQuestions[x].Title, items[i].BasicQuestions[x].Answer);
              }
          }
          if (items[i].hasOwnProperty('MBTIQuestions')) {
              for (let x = 0; x < items[i].MBTIQuestions.length; x++) {
                this._MBTIContainer.setAnswerByTitle(items[i].MBTIQuestions[x].Title, items[i].MBTIQuestions[x].Answer);
              }
          }
        }
    }

};
