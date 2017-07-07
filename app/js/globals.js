var path = require('path')

var tmpAppRoot = __dirname
var tmpAppRootSplit = tmpAppRoot.split('/')
tmpAppRoot = tmpAppRootSplit.slice(0, tmpAppRootSplit.length - 3).join('/')

/*
  ROOT makes it easier to import libraries. See example below
*/
global.ROOT = path.resolve(tmpAppRoot);

/*
  userDataManager is used for interpanel Communication
*/

var tmpDataMan = require(path.join(ROOT, 'app/js/dataManager.js'))
global.dataManager = new tmpDataMan(path.join(ROOT, 'userData.md'))

// https://discuss.atom.io/t/ipc-send-from-main-process-to-renderer/16046/3
const {ipcRenderer} = require('electron')
ipcRenderer.on('quit', function(event , data){ dataManager.save() });
