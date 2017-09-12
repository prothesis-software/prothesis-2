const Component = require(path.join(ROOT, 'app/js/Component.js'));

module.exports = class OrderedItem extends Component {

    constructor(description, rank) {
        super();

        this._description = description;
        this._rank = rank;

        this._html = `
<ul class="collection">
  <li class="collection-item">

    <div style="float:left">
      <span>${this._rank}.</span>
      <a class="btn-floating btn-small waves-effect waves-light red">
      <i class="material-icons md-12">add</i></a>
      <a class="btn-floating btn-small waves-effect waves-light red">
      <i class="material-icons md-12">remove</i></a>
    </div>
    <span>${this._description}</span>
  </li>
</ul>
        `;

        this.getRootElement().innerHTML = this._html;
    }

};
