
let path = require('path');

// Import frm globals.js
{
    let tmpAppRoot = __dirname;
    let tmpAppRootSplit = tmpAppRoot.split('/');
    tmpAppRoot = tmpAppRootSplit.slice(0, tmpAppRootSplit.length - 2).join('/');

    global.ROOT = path.resolve(tmpAppRoot);

    let DataManager = require(path.join(ROOT, 'app/js/DataManager.js'));
    global.dataManager = new DataManager(path.join(ROOT, 'gui'), path.join(ROOT, 'userData.json'));

    // https://discuss.atom.io/t/ipc-send-from-main-process-to-renderer/16046/3
    const {ipcRenderer} = require('electron');
    ipcRenderer.on('quit', function(event , data){ dataManager.saveUserData(); });
}

function injectPage(hostElementID, HTMLFilePath) {
    let path = require('path');

    let utils = require(path.join(ROOT, 'app/js/utils.js'));

    let element = document.getElementById(hostElementID);
    let data = utils.read(HTMLFilePath);

    element.innerHTML = data;
}


function injectPanel(panelJsPath, hostElementID, guiKey) {
    // Create the panel
    // Add it to the DataManager
    // Inject the panel

    let MasterPanel = require(path.join(ROOT, panelJsPath));
    let panel = new MasterPanel(guiKey);
    //injectPage(hostElementID, path.join(ROOT, htmlPath));
    document.getElementById(hostElementID).appendChild(panel.getRootElement());
    dataManager.addPanel(panel);

}

const ASS_PATH = 'app/panels/assessments';
const JS_PATH = 'app/js';

injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_roles', 'Roles');
injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_skills', 'Skills');
injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_people_orientation', 'People_Orientation');

dataManager.loadGUI();
dataManager.loadUserData();
