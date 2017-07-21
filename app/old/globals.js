let path = require('path');

let tmpAppRoot = __dirname;
let tmpAppRootSplit = tmpAppRoot.split('/');
tmpAppRoot = tmpAppRootSplit.slice(0, tmpAppRootSplit.length - 3).join('/');

/*
  ROOT makes it easier to import libraries. See example below
*/
global.ROOT = path.resolve(tmpAppRoot);

/*
  userDataManager is used for interpanel Communication
*/

let DataManager = require(path.join(ROOT, 'app/js/DataManager.js'));
global.dataManager = new DataManager(path.join(ROOT, 'userData.md'));

// https://discuss.atom.io/t/ipc-send-from-main-process-to-renderer/16046/3
const {ipcRenderer} = require('electron');
ipcRenderer.on('quit', function(event , data){ dataManager.save();});
