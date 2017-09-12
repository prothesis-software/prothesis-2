const Component = require(path.join(ROOT, 'app/js/Component.js'));
const OrderedItem = require(path.join(ROOT, 'app/js/OrderedItem.js'));

/**
 * A collection of {OrderedItem}
 */

module.exports = class OrderedItemContainer extends Component {

  constructor() {
      super();

      this._items = [];
      this._sortedElement = null;
      this._unsortedElement = null;
  }

  addItem(description) {
    let tmpItem = new OrderedItem(description);
    this._items.push(tmpItem);
    this._unsortedElement.appendChild(tmpItem.getRootElement());

  }

  setSortedElementById(elemID) {
      this._sortedElement = document.getElementById(elemID);
  }

  setUnsortedElementById(elemID) {
      this._unsortedElement = document.getElementById(elemID);
      console.log(document.getElementById(elemID));
  }

  setUnsortedElement(elem) {
      this._unsortedElement = elem;
      console.log(elem);
  }

}
