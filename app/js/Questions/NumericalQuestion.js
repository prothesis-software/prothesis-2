const Component = require(path.join(ROOT, 'app/js/Component.js'));

module.exports = class NumericalQuestion extends Component {

    constructor(title) {
        super();

        this._title = title;

        this._html = `<form class="col s12">
                          <div class="row">
                            <div class="input-field col s12">
                              <input id="numerical_input_${this.getId()}" type="number" class="validate">
                              <label for="numerical_input_${this.getId()}">${this._title}</label>
                            </div>
                          </div>
                        </form>`;

          this.getRootElement().innerHTML = this._html;
          this._numerical_input_Element = this.getRootElement().querySelector(`#numerical_input_${this.getId()}`);
      }

      getTitle() {
          return this._title;
      }

      getAnswer() {
          return this._numerical_input_Element.value;
      }

      setAnswer(str) {
          this._numerical_input_Element.value = str;

          // https://github.com/Dogfalo/materialize/issues/180#issuecomment-256384139
          //Materialize.updateTextFields();

          // http://materializecss.com/forms.html
          $(`#${this._numerical_input_Element.id}`).trigger('autoresize');


      }

};
