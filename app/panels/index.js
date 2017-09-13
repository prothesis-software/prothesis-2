
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


function injectPanel(panelJsPath, hostElementID, guiKey) {
    // Create the panel
    // Add it to the DataManager
    // Inject the panel

    let MasterPanel = require(path.join(ROOT, panelJsPath));
    let panel = new MasterPanel(guiKey);
    document.getElementById(hostElementID).appendChild(panel.getRootElement());
    dataManager.addPanel(panel);

}

const PANEL_PATH = 'app/panels';
const ASS_PATH = 'app/panels/assessments';
const JS_PATH = 'app/js';

injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_roles', 'Roles');
injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_skills', 'Skills');
injectPanel(JS_PATH + '/PanelCheckboxes.js', 'tab_people_orientation', 'People_Orientation');
injectPanel(JS_PATH + '/PanelQuestions.js', 'tab_dreams', 'Dreams');
injectPanel(JS_PATH + '/PanelQuestions.js', 'tab_passions', 'Passions');
injectPanel(JS_PATH + '/PanelQuestions.js', 'tab_people_id', 'People_ID');
injectPanel(JS_PATH + '/PanelQuestions.js', 'tab_values', 'Values');
injectPanel(PANEL_PATH + '/PanelSpokenWords.js', 'tab_spoken_words', 'Spoken_Words');
injectPanel(PANEL_PATH + '/PanelAnalysis.js', 'analysis', 'Analysis');

dataManager.loadGUI();
dataManager.loadUserData();

let rep = require(path.join(ROOT, 'app/js/reportHtmlGenerator.js'));
let re = new rep(path.join(ROOT, "userData.json"));
re.load();
re.save(path.join(ROOT, "test.pdf"));
require(path.join(ROOT, 'app/js/test.js'));
