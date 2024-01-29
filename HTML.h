const char index_html[] PROGMEM = R"rawliteral(
<html>
    <style>
    input[type=text], [type=password]{
        width: 100%;
        padding: 12px 20px;
        margin: 8px 0;
        border: 1px solid #ccc;
        border-radius: 4px;
        box-sizing: border-box;
    }
    input[type=submit]{
        width: 100%;
        background-color: #597E52;
        color: white;
        padding: 14px 20px;
        margin: 8px 0;
        border: none;
        border-radius: 4px;
        cursor: pointer;
    }
    
    input[type=submit]:hover{
        background-color: #030637;
    }
    
    div{
        border-radius: 5px;
        background-color: #F1E4C3;
        padding: 20px
    }
    body{
        text-align: center;
        background-color: #B1C381;
        padding: 5px;
        margin: 0px;
        
    }
    h1{
        padding: 0px;
        margin: 0px;
        font-size: 22px;
        font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
        font-style: normal;
        color: #765827;
    }
    h2{
        padding-bottom: 10px;
        margin: 2px;
        font-size: 18px;
        font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
        font-weight: lighter;
        color: #765827;
    }
    p{
        padding-top: 10px;
        font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
        font-size: 10px;
    }
    </style>
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>SOBAT-KKN UNDIP 2024</title>
    </head>
    
    <body>
        <h1>SOBAT MIRING</h1>
        <h2>Sistem Otomasi Bank Sampah Lemah Miring</h2>
    </body>
    
    <div>
        <form action="/action_page">
            <label for="ssid">SSID</label>
            <input type="text" id="ssid" name="ssidNew" placeholder="SSID">
            
            <label for="password">Password</label>
            <input type="password" id="password" name="passNew" placeholder="Password">
            
            <input type="submit" value="Simpan">
        </form>
        
    </div>
    <p>Dibuat oleh :<br>TIM 1 KKN UNDIP - Desa Paseban<br>2024</p>
</html>
)rawliteral";


const char sukses_html[] PROGMEM = R"rawliteral(
<html>
  <style>
    div{
      position: fixed;
      top: 50%;
      left: 50%;
      margin-top: -100px;
      margin-left: -300px;
    }
  </style>
  <head>
    <title>Berhasil</title>
  </head>
  
  <body>
    <div>
      <h1>Pengaturan Berhasil Disimpan!</h1>
    </div>
  </body>
</html>

)rawliteral";
