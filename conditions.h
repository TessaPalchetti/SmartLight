String conditions_html_page(String timestamp, String visibility, String distance, int flag){ 
String img_light = "";


switch (flag) {
    case 1:
        img_light = "https://drive.google.com/file/d/177kFCTz_bhclHp1Q6_pZu9AE8Ok12yyM/view?usp=sharing";
         break;
    case 2:
        img_light = "https://drive.google.com/file/d/1COMTZBs84oW44J6y6O8nMhIk5ck5R-sp/view?usp=sharing";
        break;
   default:
        img_light = "https://drive.google.com/file/d/1I2_nQM5XWdJD3hNL3xbJMp-Y-2zbQuAP/view?usp=sharing";
        break;
  }
  return R"==(

<html>

<head>
<title> Faro Intelligente </title>


 <style>
  *{
   font-family:'Arial';
  }
  
  html{
   margin:0px;
   padding:0pc;
  }
  
  body{
   background-color: Cornsilk;
   margin:0px;
   padding:0pc;
  }


  header{
   background-color:Ivory;
   height: 170px;
    }

  h1{
  font-family:'Impact';
  text-align: center;
  letter-spacing:6px;
  font-size: 70px;
  color:DarkTurquoise;
  padding:10px;
  top:20px;
  } 

  h2{
   font-family:'Arial';
   letter-spacing:2px;
   font-size:45px;
   color:DarkTurquoise;
   margin:0px;
   padding:0px;
  }

   
  p{
  background-color:Ivory;
  text-align:center;
  width:98%;
  font-size:19px;
  }


  aside{
   width:40%;
   position :absolute;
   bottom:80px;
   right:0px;
  }


  section{
  position:section;
  }


 #faro{
  float:right;
  height:350px;
  margin-right:70px;
  margin-top:10px;
  }

  
  article{
  width:90%;
  text-align:center;
  border:solid 3px DarkTurquoise;
  background-color:Ivory;
  position:absolute;
  top:320px;
  bottom:250px;
  margin-left:50px;
  padding:10px;
  border-radius: 10px 10px 10px 10px;
  }

  
  .boxHour{
  width:25%;
  border: solid 3px DarkTurquoise;
  background-color:Ivory;
  position:absolute;
  top:520px;
  bottom:20px;
  margin-left:80px;
  padding:10px;
  border-radius: 10px 10px 10px 10px;
  }

  h3{
  font-family:'Arial';
  text-align: center;
  letter-spacing:3px;
  font-size: 45px;
  color:DarkTurquoise;
  margin:0px;
  padding:0px;
  } 

  .text-boxHour{
   text-align:center;
   font-family:'Arial';
   font-size:35px;
   margin:0px;
   padding:0px;
  }
  
  .boxVis{
  width:25%;
  border: solid 3px DarkTurquoise;
  background-color:Ivory;
  position:absolute;
  top:520px;
  bottom:20px;
  margin-left:550px;
  padding:10px;
  border-radius: 10px 10px 10px 10px;
  }

  h4{
  font-family:'Arial';
  text-align: center;
  letter-spacing:3px;
  font-size: 45px;
  color:DarkTurquoise;
  margin:0px;
  padding:0px;
  } 

  .text-boxVis{
   text-align:center;
   font-family:'Arial';
   font-size:35px;
   margin:0px;
   padding:0px;
  }
  

  .boxDist{
  width:25%;
  border: solid 3px DarkTurquoise;
  background-color:Ivory;
  position:absolute;
  top:520px;
  bottom:20px;
  margin-left:1020px;
  padding:10px;
  border-radius: 10px 10px 10px 10px;
  }

  h5{
  font-family:'Arial';
  text-align: center;
  letter-spacing:3px;
  font-size: 45px;
  color:DarkTurquoise;
  margin:0px;
  padding:0px;
  } 

  .text-boxDist{
   text-align:center;
   font-family:'Arial';
   font-size:35px;
   margin:0px;
   padding:0px;
  }



   nav{
   margin-right:0px;
   padding-right:0px;
   }


  .vertical-menu {
  width: 400px;
  }

  .vertical-menu a {
  background-color: FloralWhite;
  color: black;
  display: block;
  padding: 12px;
  text-decoration: none;
  }
 
 .vertical-menu a:hover {
  background-color: DarkTurquoise;
 }

 .vertical-menu a.active {
  background-color: DarkTurquoise;
  color: white;
  }
 
 </style>


<body> 
<header>
 
 <h1>Faro intelligente <img id="faro" src=img_light>  </h1>
 
</header>

<section>
 
 <div class="vertical-menu">
  
  <a href="index.htm" class="active">Home</a>
  <a href="conditions.htm">Condizioni meteo</a>
 </div>



 <article>
  <h2> Condizioni meteo e visibilit?? </h2>
 <p> A seconda dell'ora in cui ci troviamo e delle condizioni di visibilit??, la luce emessa dal faro sar?? diversa in modo da garantirne sempre l'efficacia. </p>
 </article>

<div class="boxHour">
 <h3> Ora <br></br></h3>
 <p class="text-boxHour">)==" + String(timestamp) +R"==(</p>
</div>

<div class="boxVis">
 <h4> Visibilit??<br></br> </h4>
 <p class="text-boxVis">)==" + String(visibility) +R"==(</p>
</div>

<div class="boxDist">
 <h5> Luce <br></br> </h5>
 <p class="text-boxDist">  )==" + String(distance) +R"==(</p>
</div>




</section>



</body>

</html>
    )==";
}
