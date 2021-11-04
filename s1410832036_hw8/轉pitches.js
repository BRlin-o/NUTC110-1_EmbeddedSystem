var arr = ["NOTE_C",
"NOTE_D",
"NOTE_E",
"NOTE_F",
"NOTE_G",
"NOTE_A",
"NOTE_B"]
var n = 7
var str = "";
str += `{\n`;
for (var i=0;i<n;++i){
	str+=`{`;
	for(var j=0;j<arr.length;++j){
		str+=`${arr[j]}${i+1},`;
	}
	str+=`},\n`;
}
str+=`}`
console.log(str)