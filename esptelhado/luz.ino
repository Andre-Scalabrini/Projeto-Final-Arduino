void controleluz(){
  if (manual == 0){
      analogWrite(pinoled, forcaluz);
  }else if(manual == 1){
      analogWrite(pinoled, forcamanual);
  }
}