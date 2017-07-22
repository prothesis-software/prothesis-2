/** @module reportHtmlGenerator */

module.exports = class reportHtmlGenerator{
	constructor(){
		this._buffer = "";
	}

	addHtml(buff){
		this._buffer += buff;
	}

	clear(){
		this._buffer = "";
	}

	loadDreams(){
		return undefined;
	}

	loadPassions(){
		return undefined;
	}

	loadPeople(){
		return undefined;
	}

	loadPeopleOrientation(){
		return undefined;
	}

	loadRoles(){
		return undefined;
	}

	loadSkills(){
		return undefined;
	}

	loadSpokenWords(){
		return undefined;
	}

	loadValues(){
		return undefined;
	}
}
