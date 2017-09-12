const Component = require(path.join(ROOT, 'app/js/Component.js'));

module.exports = class OrderedItem extends Component {

    constructor(description, rank) {
        super();

        this._description = description;
        this._rank = rank;

        // Set HTML templates
        this._html_rank = `
        <li class="collection-item">
            <a id="move_up_${this._id}"  href="#!" style="float:left">
                <i class="material-icons">add_circle</i>
            </a>

            <a href="#!">
                <i id="move_down_${this._id}" class="material-icons" style="float:left">remove_circle</i>
            </a>

           <span id="rank_${this._id}">${this._rank}</span> ${this._description}
                <a href="#!" id="unsort_${this._id}" class="secondary-content">
                    <i class="material-icons">chevron_right</i>
                </a>
        </li>
        `;

        this._html_no_rank = `
        <li class="collection-item">
            <a id="add_${this._id}" href="#!" style="float:left">
                <i class="material-icons">chevron_left</i>
            </a>
            ${this._description}
        </li>
        `;

        // Attach correct template
        if (rank == -1) {
            this.getRootElement().innerHTML = this._html_no_rank;

            this._addLinkElement = this.getRootElement().querySelector(`#add_${this._id}`);
            this._addLinkElement.addEventListener('click', this._addOnClickHandler);
        } else {
            this.getRootElement().innerHTML = this._html_rank;

            this._rankElement = this.getRootElement().querySelector(`#rank_${this._id}`);

            // Attach event listeners
            this._removeLinkElement = this.getRootElement().querySelector(`#unsort_${this._id}`);
            this._removeLinkElement.addEventListener('click', this._unsortOnClickHandler);

            this._moveUpLinkElement = this.getRootElement().querySelector(`#move_up_${this._id}`);
            this._moveUpLinkElement.addEventListener('click', this._moveUpOnClickHandler);

            this._moveDownLinkElement = this.getRootElement().querySelector(`#move_down_${this._id}`);
            this._moveDownLinkElement.addEventListener('click', this._moveDownOnClickHandler);
        }

    }

    getDescription() {
        return this._description;
    }

    /*
    This function will be executed when the remove link is clicked
    */
    _unsortOnClickHandler(e) {
        'use strict';
        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        let comp = Component.getComponentById(id)

        comp._unsortEventHandler(comp);
    }

    _addOnClickHandler(e) {
        'use strict';
        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        let comp = Component.getComponentById(id)

        comp._addEventHandler(comp);
    }

    _moveUpOnClickHandler(e) {
        'use strict';
        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        let comp = Component.getComponentById(id)

        comp._moveUpEventHandler(comp);
    }

    _moveDownOnClickHandler(e) {
        'use strict';
        let tmpId = this.id.split('_');
        let id = tmpId[tmpId.length - 1];
        let comp = Component.getComponentById(id)

        comp._moveDownEventHandler(comp);
    }

    setRank(rank) {
        this._rank = rank;
        this._rankElement.innerHTML = rank;
    }


};
