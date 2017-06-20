# Prothesis-2

![HelloWorld](https://i.imgur.com/iREklaY.png)
![HelloWorld](https://i.imgur.com/W3CGVsL.png)

## Build Setup
``` bash
# clone the repository
git clone git@github.com:egeldenhuys/prothesis-2.git

# cd
cd prothesis-2

# make sure npm is up-to-date!
sudo npm install -g npm

# install dependencies
npm install

# this is how you use it in development
# server with hot reload at localhost:9080
npm run dev

# build electron app for production
npm run build

# lint all JS/Vue component files in `app/src`
npm run lint

# run webpack in production
npm run pack
```
More information can be found [here](https://simulatedgreg.gitbooks.io/electron-vue/content/en/npm_scripts.html).

## Troubleshooting
See the [wiki](https://github.com/egeldenhuys/prothesis-2/wiki) for information

## For the Windows plebs
If you run into errors during npm install about node-gyp, then you most likely do not have the proper build tools installed on your system. Build tools include items like Python and Visual Studio.

The first item we need to check is our npm version and ensure that it is not outdated. This can is accomplished using npm-windows-upgrade.

Once that is complete, we can then continue to setup the needed build tools. Using windows-build-tools, most of the dirty work is done for us. Installing this globally will in turn setup Visual C++ packages, Python, and more.

At this point things should successfully install, but if not then you will need a clean installation of Visual Studio. Please note that these are not direct problems with electron-vue itself. (Windows can be difficult sometimes ```¯\_(ツ)_/¯```)

---
Documentation about electron-vue project can be found [here](https://simulatedgreg.gitbooks.io/electron-vue/content/index.html).

## Stop molesting disks
To clean setup files and packages downloaded by npm run ./clean.sh; This will require you to rebuild the project as it removes dependancies as well as builds.
