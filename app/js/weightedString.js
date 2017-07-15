/** @module weightedString*/
'use strict';

module.exports = class weightedString {
     constructor() {
          this.weights = [];
          this.values = [];
     }

     push(value, weight) {
          this.weights.push(weight);
          this.values.push(value);
          this._order();
     }

     get(i) {
          return {
               value: this.values[i],
               weight: this.weights[i]
          };
     }

     setWeight(index, weight){
          if(index <= this.weights.length){
               this.weights[index] = weight;
               this._order();
          }
     }

     setValue(index, value){
          if(index <= this.weights.length){
               this.values[index] = values;
          }
     }

     find(value){
          for (var i = 0; i < size; i++) {
               if(this.values[i] === value)
                    return i;
          }

          return undefined;
     }

     _order() {
          var size = this.values.length;
          for (var i = 0; i < size - 1; i++) {
               for (var j = 0; j < size - i - 1; j++) {
                    if (this.weights[j] > this.weights[j + 1]) {
                         var tmp = this.weights[j];
                         this.weights[j] = this.weights[j + 1];
                         this.weights[j + 1] = tmp;

                         tmp = this.values[j];
                         this.values[j] = this.values[j + 1];
                         this.values[j + 1] = tmp;
                    }
               }
          }
     }

     _print() {
          var size = this.values.length;
          for (var i = 0; i < size; i++) {
               console.log(this.values[i]);
          }
     }
}
