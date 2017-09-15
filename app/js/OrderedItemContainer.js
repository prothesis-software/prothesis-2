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
      this._state = [];

  }

  addItem(description, rank) {
    let tmpItem = new OrderedItem(description, rank);
    this._items.push(tmpItem);

    // Set the event handlers
    // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Function/bind
    // https://stackoverflow.com/questions/710542/jquery-javascript-this-pointer-confusion
    tmpItem._unsortEventHandler = this.unsortItemHandler.bind(this);
    tmpItem._addEventHandler = this.addItemHandler.bind(this);
    tmpItem._moveUpEventHandler = this.moveUpEventHandler.bind(this);
    tmpItem._moveDownEventHandler = this.moveDownEventHandler.bind(this);

    if (tmpItem._rank == -1) {
        this._unsortedElement.appendChild(tmpItem.getRootElement());
    } else {
        this._sortedElement.appendChild(tmpItem.getRootElement());

    }

    this.refreshOrder();
  }

  addItemHandler(orderedItem) {
      this.addItem(orderedItem.getDescription(), 99999);

      this._unsortedElement.removeChild(orderedItem.getRootElement());
      this.removeIdFromItems(orderedItem.getId());

      this.refreshOrder();

  }

  getItemByDescription(desc) {
      for (let i = 0; i < this._items.length; i++) {
          if (this._items[i].getDescription() == desc) {
              return this._items[i];
          }
      }
  }

  moveUpEventHandler(orderedItem) {
      // HACK: uses jquery
      $(orderedItem.getRootElement()).insertBefore(orderedItem.getRootElement().previousElementSibling);
      this.refreshOrder();
  }

  moveDownEventHandler(orderedItem) {
      // HACK: uses jquery
      $(orderedItem.getRootElement()).insertAfter(orderedItem.getRootElement().nextElementSibling);
      this.refreshOrder();
  }

  /*
  Move the item with the id to the unsorted side
  */
  unsortItemHandler(orderedItem) {
      // Add the new element to the DOM
      this.addItem(orderedItem.getDescription(), -1);

      this._sortedElement.removeChild(orderedItem.getRootElement());
      this.removeIdFromItems(orderedItem.getId());

      this.refreshOrder();
  }

  removeIdFromItems(id) {
      for (let i = 0; i < this._items.length; i++) {
          if (this._items[i].getId() == id) {

              if (i == this._items.length - 1) {
                  this._items.pop();
              } else {
                  for (let j = i; j < this._items.length - 1; j++) {
                      this._items[j] = this._items[j + 1]
                  }
                  this._items.pop();
                  break;
              }
          }
      }

  }

  setUnsortedElement(elem) {
      this._unsortedElement = elem;
  }

  setSortedElement(elem) {
      this._sortedElement = elem;
  }

  getRanked() {
      return this.refreshOrder();
  }

  refreshOrder() {

      let ranked = [];

      for (let i = 0; i < this._items.length; i++) {
          // Find first sorted element
          if (this._items[i]._rank != -1) {
              // DOM SPACE
              // Traverse to top
              let tmpElem = null;
              let curElem = this._items[i].getRootElement()

              while (curElem != null) {
                  tmpElem = curElem;
                  curElem = curElem.previousElementSibling;
              }
              // Start ranking from the top
              curElem = tmpElem;

              let j = 1;
              while (curElem != null) {
                  let tmpComp = Component.getComponentByElement(curElem);
                  tmpComp.setRank(j);
                  j++;
                  ranked.push(tmpComp.getDescription());

                  curElem = curElem.nextElementSibling;
              }

              break;
          }
      }

      this._state = ranked;
      return ranked;
  }

  getState() {
      return this.getRanked();
  }

}
