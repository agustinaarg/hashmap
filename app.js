class pair {
    constructor(word, value){
        this.word = word;
        this.value = value;
    }
} 

  
let all_letters = [
    { letter: "a", 
      words: [],
    }, 
    { letter: "b", 
        words: [],
      }, 
      { letter: "c", 
        words: [],
      }, 
      { letter: "d", 
        words: [],
      }, 
      { letter: "e", 
        words: [],
      }, 
      { letter: "f", 
        words: [],
      }, 
      { letter: "g", 
        words: [],
      }, 
      { letter: "h", 
        words: [],
      }, 
      { letter: "i", 
        words: [],
      }, 
      { letter: "j", 
        words: [],
      }, 
      { letter: "k", 
        words: [],
      }, 
      { letter: "l", 
        words: [],
      }, 
      { letter: "m", 
        words: [],
      }, 
      { letter: "n", 
        words: [],
      }, 
      { letter: "o", 
        words: [],
      }, 
      { letter: "p", 
        words: [],
      }, 
      { letter: "q", 
        words: [],
      }, 
      { letter: "r", 
        words: [],
      }, 
      { letter: "s", 
        words: [],
      }, 
      { letter: "t", 
        words: [],
      }, 
               
      { letter: "u", 
        words: [],
      }, 
       { letter: "v", 
        words: [],
      }, 
      { letter: "w", 
        words: [],
      }, 
      { letter: "x", 
        words: [],
      }, 
      { letter: "y", 
        words: [],
      }, 
      { letter: "z", 
        words: [],
      }, 
                    
 ]

 let boton = document.getElementById('boton_ok');
 let new_w = document.getElementById('new_w');

boton.addEventListener('click', addi);

function addi(){
    let valore = new_w.value;
    console.log(valore);
    add(valore);
}

   
   function  add(w){
     if(search_word(w)){
          increment(w);
       } else{
           let first_letter = w.charAt(0);
           all_letters.forEach(element =>{
               if(element.letter == first_letter){
                   nueva = new pair(w, 1);
                   element.words.push(nueva); 
               }
           })
       }
     }
   

    function search_word(w){
       let first_letter = w.charAt(0);
       let res = false;
   
       all_letters.forEach(element =>{
           if(element.letter == first_letter){
               element.words.forEach(element =>{
                   if (element.word == w){
                       res = true; 
                   }
               })
           }
       })
   
       return res; 
     }
   
   
  
    function increment(w){
        let first_letter = w.charAt(0);

        all_letters.forEach(element =>{
            if(element.letter == first_letter){
                element.words.forEach(element =>{
                    if (element.word == w){
                        element.value += 1; 
                       // let eliminar = document.getElementsByClassName('lista');
                       // document.removeChild(eliminar);
                    }
                })
            }
        })
    }
    


Array.from(document.getElementsByClassName('clase_letra')).forEach((element) =>{
    element.addEventListener('click', (e) =>{
        let primer_letra = e.target.id;
       

        all_letters.forEach(ele =>{
            if(ele.letter == primer_letra){
                ele.words.forEach(ele2 =>{
                    let palabras = document.createElement("p");
                    palabras.innerText = `[${ele2.word}, ${ele2.value}]`;
                    palabras.classList.add('lista');
                    e.target.appendChild(palabras);
                })
                  
            }
        })

    })
})

let boton_maximo = document.getElementById('boton_max');

boton_maximo.addEventListener('click', find_maximum);

function find_maximum() {
    let maximum = 0; 
    let palabra_maxima; 

    all_letters.forEach(element =>{
        element.words.forEach(ele =>{
           if(ele.value > maximum){
            maximum = ele.value; 
            palabra_maxima = ele.word;
           }

        })
    })

    let maximo = document.createElement("p");
    maximo.innerText = palabra_maxima;
    let m = document.getElementById('num_maximo');
    m.appendChild(maximo);
  }





