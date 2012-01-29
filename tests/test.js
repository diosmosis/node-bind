var test = require('../build/test_ext/test_ext');

var obj = new test.MyType(1, 2);

console.log("thing1: " + obj.thing1);
console.log("thing2: " + obj.thing2);
console.log("obj: " + obj.toString());

console.log("");
obj.thing1 = 23;
obj.thing2 = 34;

console.log("thing1: " + obj.thing1);
console.log("thing2: " + obj.thing2);
console.log("obj: " + obj.toString());

obj.doSomethingElse(function(){
  console.log("haaaa--HAAA!");
  console.log("it worked.");
});
