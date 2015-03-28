
var letters = 'acdegilmnoprstuw';

function dehash(hash) {
  var counter = 0;
  var result = '';
  while(true) {
    if((hash - counter) % 37 === 0) {
      result += letters[counter];
    }
  }
  counter++;

  return result;
};

console.log(dehash(956446786872726));
