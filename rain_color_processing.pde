import processing.serial.*; 
Serial port;
boolean inicio = false;

void setup(){
  size(640,480);
  frameRate(144);
  
  
  port = new Serial(this, "COM3",250000);
  port.bufferUntil('\n');
  background(255);
}

void draw(){
  background(255);
  delay(2000);
  String inString = port.readStringUntil('\n');
  
  if(inString != null){
   int[] values = int(split(inString,","));
   
    if (values.length < 6){
    textSize(30);
    fill(50);
    text("iniciando, espere",180,240);
    delay(300);
    }
    else{
    int red = ((255*values[1]/values[0]));
    int green = ((255*values[3]/values[2]));
    int blue = ((255*values[5]/values[4]));
    
    fill(red,green,blue);
    rect(190,50,400,380);
    
    textSize(30);
    fill(50);
    text("R = "+red,40,102);

    textSize(30);
    fill(50);
    text("G = "+green,40,238);
    
    textSize(30);
    fill(50);
    text("B = "+blue,40,374);
    }
  }
}