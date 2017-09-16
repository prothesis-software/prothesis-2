const Component = require(path.join(ROOT, 'app/js/OrderedItem.js'));

let elem = document.getElementById('test_inject');
let comp = new Component();

elem.appendChild(comp.getRootElement());
