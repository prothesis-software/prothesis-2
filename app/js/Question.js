const Component = require(path.join(ROOT, 'app/js/Component.js'));

module.exports = class Question extends Component {

    constructor(title) {
        super();

        this._title = title;

        this._html = `<form class="col s12">
                          <div class="row">
                            <div class="input-field col s12">
                              <textarea id="textarea_${this.getId()}" class="materialize-textarea"></textarea>
                              <label for="textarea_${this.getId()}">${this._title}</label>
                            </div>
                          </div>
                        </form>`;

        this.getRootElement().innerHTML = this._html;
        this._textareaElement = this.getRootElement().querySelector(`#textarea_${this.getId()}`);
    }

    getTitle() {
        return this._title;
    }

    getAnswer() {
        return this._textareaElement.value;
    }

    setAnswer(str) {
        this._textareaElement.value = str;

        // https://github.com/Dogfalo/materialize/issues/180#issuecomment-256384139
        //Materialize.updateTextFields();

        // http://materializecss.com/forms.html
        $(`#${this._textareaElement.id}`).trigger('autoresize');


    }

};