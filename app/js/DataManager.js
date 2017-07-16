module.exports = class DataManager {

    constructor(guiFolder, userDataFile) {
        this._guiFolder = guiFolder;
        this._userDataFile = userDataFile;
        this._panels = [];
    }

    loadGUI() {
        const FileSystem = require('fs');
        const Path = require('path');
        const utils = require(Path.join(ROOT, 'app/js/utils.js'));

        function readDirR(dir) {
            return FileSystem.statSync(dir).isDirectory() ? Array.prototype.concat(...FileSystem.readdirSync(dir).map(f => readDirR(Path.join(dir, f)))) : dir;
        }

        let files = readDirR(this._guiFolder);

        let data = {};

        for (let i = 0; i < files.length; i++) {
            if (files[i].endsWith('.json')) {
                let fileContents = utils.read(files[i]);

                let tmpObj = JSON.parse(fileContents);

                for (let key in tmpObj) {
                    data[key] = tmpObj[key];
                }
            }
        }

        for (let i = 0; i < this._panels.length; i++) {
            this._panels[i].loadGUI(data);
        }
    }


    loadUserData() {
        'use strict';

        const path = require('path');
        const utils = require(path.join(ROOT, 'app/js/utils.js'));

        let fileContents = utils.read(this._userDataFile);
        let dataObj = JSON.parse(fileContents);

        for (let i = 0; i < this._panels.length; i++) {
            this._panels[i].setState(dataObj);
        }

    }

    saveUserData() {
        let data = {};

        for (let i = 0; i < this._panels.length; i++) {
            let panelData = this._panels[i].getState();

            for (let key in panelData) {
                data[key] = panelData[key];
            }
        }
        const path = require('path');
        const utils = require(path.join(ROOT, 'app/js/utils.js'));

        utils.write(this._userDataFile, JSON.stringify(data, null, 2));
    }

    addPanel(panel) {
        this._panels.push(panel);
    }
};
