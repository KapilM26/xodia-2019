function detectmob() {
  if (
    navigator.userAgent.match(/Android/i) ||
    navigator.userAgent.match(/webOS/i) ||
    navigator.userAgent.match(/iPhone/i) ||
    navigator.userAgent.match(/iPad/i) ||
    navigator.userAgent.match(/iPod/i) ||
    navigator.userAgent.match(/BlackBerry/i) ||
    navigator.userAgent.match(/Windows Phone/i)
  ) {
    return true;
  } else {
    return false;
  }
}
//Declare and Initialize
var canvas = document.querySelector("canvas");
innerWidth = window.innerWidth;
innerHeight = window.innerHeight;
canvas.width = innerWidth;
canvas.height = innerHeight;

var firstclick = true;
var turn = true; //true=player1 false=player2
var messagesStatus = document.getElementById("status");
messagesStatus.innerHTML = "Tyragon's Turn<br>";
var t, u;
var w, r;
var p = [];
var p2 = [];
var c1 = 0;
var c2 = 0;
var p3, p4, p5, b, l, g;
var pushToken;
var count1;
var eliminatePosYDistance = 130;
var eliminatePosY1 = 105;
var eliminatePosY2 = 130;
var gameOver = false;
var undoButton = document.getElementById("undo");


var g, g1, g2;

var s;
var d;
if (detectmob()) {
  s = 200;
  d = 300;
  canvas.height = 300 + 260 + eliminatePosY2 + 30;
} else {
  s = 350;
  d = 300;
  canvas.height = innerHeight;
}

var eliminatePosX = s;
var eliminatePosX2 = s;

var c = canvas.getContext("2d");

class token {
  constructor(m, n, color) {
    this.m = m;
    this.n = n;
    this.color = color;
    this.val = 0;
  }
  draw() {
    let image = new Image();
    if (this.color === "black") {
      image = document.getElementById("imgp1");
    } else if (this.color === "red") {
      image = document.getElementById("imgp2");
    }
    c.drawImage(image, this.m - 24.5, this.n - 24.5, 49, 49);
    c.beginPath();
    c.arc(this.m, this.n, 20, 0, 2 * Math.PI);
    c.fillStyle = "rgba(255,255,255," + this.val.toString() + ")";
    c.fill();
  }
}

//Draw Board
init();

function init() {
  console.log(undoButton);
  create_board();

  var k = s;
  for (var i = 0; i < 4; i++) {
    p[i] = new token(k, d, "red");
    p[i].draw();
    k = k + 50;
  }
  k = s - 25;
  for (var i = 4; i < 9; i++) {
    p[i] = new token(k, d + 43.3, "red");
    p[i].draw();
    k = k + 50;
  }
  k = s + 50;
  for (var i = 9; i < 11; i++) {
    p[i] = new token(k, d + 86.6, "red");
    p[i].draw();
    k = k + 50;
  }

  k = s;
  for (var i = 0; i < 4; i++) {
    p2[i] = new token(k, d + 259.8, "black");
    p2[i].draw();
    k = k + 50;
  }
  k = s - 25;
  for (var i = 4; i < 9; i++) {
    p2[i] = new token(k, d + 216.5, "black");
    p2[i].draw();
    k = k + 50;
  }
  k = s + 50;
  for (var i = 9; i < 11; i++) {
    p2[i] = new token(k, d + 173.2, "black");
    p2[i].draw();
    k = k + 50;
  }
  animate();
}

function create_board() {
  c.moveTo(s + 175, d - 50);
  c.lineTo(s - 25, d - 50);
  c.lineTo(s - 125, d + 129.3);
  c.lineTo(s - 25, d + 309.8);
  c.lineTo(s + 175, d + 309.8);
  c.lineTo(s + 275, d + 129.3);
  c.lineTo(s + 175, d - 50);
  c.strokeStyle = "white";
  c.lineWidth = 2;
  c.stroke();

  mov = 25;
  c.font = "25px Arial";
  c.fillStyle = "#aaa";
  c.fillText("A", s - 90, d);
  c.fillText("B", s - 115, d + 43.3);
  c.fillText("C", s - 140, d + 86.6);
  c.fillText("D", s - 165, d + 139.9);
  c.fillText("E", s - 140, d + 193.2);
  c.fillText("F", s - 115, d + 236.5);
  c.fillText("G", s - 90, d + 279.8);
  c.fillText("1", s + mov, d + 349.8 - 8);
  c.fillText("2", s + 50 + mov, d + 349.8 - 8);
  c.fillText("3", s + 100 + mov, d + 349.8 - 8);
  c.fillText("4", s + 150 + mov, d + 340);
  c.fillText("5", s + 210, d + 289.8);
  c.fillText("6", s + 235, d + 246.5);
  c.fillText("7", s + 260, d + 203.2);

  //first row
  for (var i = 0; i < 4; i++) {
    c.beginPath();
    c.arc(s + 50 * i, d, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //second row
  for (var i = 0; i < 5; i++) {
    c.beginPath();
    c.arc(s - 25 + 50 * i, d + 43.3, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //third row
  for (var i = 0; i < 6; i++) {
    c.beginPath();
    c.arc(s - 50 + 50 * i, d + 86.6, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //fourth row
  for (var i = 0; i < 7; i++) {
    c.beginPath();
    c.arc(s - 75 + 50 * i, d + 129.9, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //fifth row
  for (var i = 0; i < 6; i++) {
    c.beginPath();
    c.arc(s - 50 + 50 * i, d + 173.2, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //sixth row
  for (var i = 0; i < 5; i++) {
    c.beginPath();
    c.arc(s - 25 + 50 * i, d + 216.5, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  //seventh row
  for (var i = 0; i < 4; i++) {
    c.beginPath();
    c.arc(s + 50 * i, d + 259.8, 20, 0, Math.PI * 2, false);
    c.strokeStyle = "white";
    c.stroke();
  }

  for (var i = 0; i < 4; i++) {
    c.beginPath();
    c.arc(s + i * 50, d - eliminatePosY1, 20, 0, Math.PI * 2);
    c.strokeStyle = "white";
    c.stroke();
    c.beginPath();
    c.arc(s + i * 50, d + 260 + eliminatePosY2, 20, 0, Math.PI * 2);
    c.strokeStyle = "white";
    c.stroke();
  }
}

function draw_tokens() {
  for (let i = 0; i < 11; i++) {
    p[i].draw();
  }
  for (let i = 0; i < 11; i++) {
    p2[i].draw();
  }
}

function animate() {
  requestAnimationFrame(animate);
  c.clearRect(0, 0, innerWidth, innerHeight);
  create_board();
  draw_tokens();
}

//Checking for selected token
function check(a, b) {
  for (var i = 0; i < 11; i++) {
    var s1 = p[i].m - a;
    var o1 = p[i].n - b;
    var v1 = Math.pow(s1, 2);
    var z1 = Math.pow(o1, 2);
    if (v1 + z1 <= 225) {
      var q = p[i];
    }
    var s2 = p2[i].m - a;
    var o2 = p2[i].n - b;
    var v2 = Math.pow(s2, 2);
    var z2 = Math.pow(o2, 2);
    if (v2 + z2 <= 225) {
      var q = p2[i];
    }
  }
  return q;
}

function showcoords(event) {
  var x =
    event.clientX +
    document.body.scrollLeft +
    document.documentElement.scrollLeft;
  var y =
    event.clientY +
    document.body.scrollTop +
    document.documentElement.scrollTop;
  console.log("Mouse Click Position: ", x, y);

  if (!gameOver) {
    if (firstclick === true) {
      t = check(x, y); //Get Selected Token
      if (t != undefined) {
        if ((turn && t.color === "red") || (!turn && t.color == "black")) {
          firstclick = false;
          //Highlight t
          console.log("Token 1 Selected: ", t);
          messagesStatus.innerHTML += "Token 1 Selected<br>";
          t.val = 0.3;
        }
      }
    } else {
      u = check(x, y);
      if (u != undefined) {
        if (
          (turn && u.color === "red" && t.color === "red") ||
          (!turn && u.color === "black" && t.color === "black")
        ) {
          firstclick = true;
          //Remove Highlight
          console.log("Token 2 Selected: ", u);
          messagesStatus.innerHTML += "Token 2 Selected<br>";
          move(t, u);

          //Score
          console.log("PLAYERS' SCORES");
          console.log("BLUE SCORE", c2);
          console.log("RED SCORE", c1);
          if (c2 >= 4) {
            alert("Blue Wins");
            gameOver = true;
          } else if (c1 >= 4) {
            alert("Red Wins");
            gameOver = true;
          }
          t.val = 0;
        }
      }
    }
  }
}

function getXUpperlimit(y) {
  //Returns X Upper Limit for a given Y
  if (Math.ceil(y) === Math.ceil(d) || Math.ceil(y) === Math.ceil(d + 259.8)) {
    return s + 150;
  } else if (
    Math.ceil(y) === Math.ceil(d + 43.3) ||
    Math.ceil(y) === Math.ceil(d + 216.5)
  ) {
    return s + 175;
  } else if (
    Math.ceil(y) === Math.ceil(d + 86.6) ||
    Math.ceil(y) === Math.ceil(d + 173.2)
  ) {
    return s + 200;
  } else if (Math.ceil(y) === Math.ceil(d + 129.9)) {
    return s + 225;
  } else {
    return s + 225;
  }
}

function getXLowerlimit(y) {
  //Returns X Lower Limit for a given y
  if (Math.ceil(y) === Math.ceil(d) || Math.ceil(y) === Math.ceil(d + 259.8)) {
    return s;
  } else if (
    Math.ceil(y) === Math.ceil(d + 43.3) ||
    Math.ceil(y) === Math.ceil(d + 216.5)
  ) {
    return s - 25;
  } else if (
    Math.ceil(y) === Math.ceil(d + 86.6) ||
    Math.ceil(y) === Math.ceil(d + 173.2)
  ) {
    return s - 50;
  } else if (Math.ceil(y) === Math.ceil(d + 129.9)) {
    return s - 75;
  } else {
    return s - 75;
  }
}

function printTurn(t) {
  if (t) {
    messagesStatus.innerHTML = "Tyragon's Turn<br>";
  } else {
    messagesStatus.innerHTML = "Abagon's Turn<br>";
  }
}

function move(t1, t2) {
  var count = 0;
  var pass;
  count1 = 0;
  var pass;
  l = undefined;

  if (t2.m === t1.m + 50 && Math.ceil(t1.n) === Math.ceil(t2.n)) {
    //Right Horizontal
    for (i = 0; i < 11; i++) {
      //Checking if there is a token in front of t2
      if (
        (p[i].m === t2.m + 50 && Math.ceil(p[i].n) === Math.ceil(t2.n)) ||
        (p2[i].m === t2.m + 50 && Math.ceil(p2[i].n) === Math.ceil(t2.n))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      //No token ahead of t2 => move t1,t2
      if (t2.m < getXUpperlimit(Math.ceil(t2.n))) {
        t1.m = t2.m;
        t2.m = t2.m + 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      //Check if token found can be pushed
      l = valid2(t1, t2, pass, "horizontalRight");
    }
    p3 = t1;
    p4 = t2;
    (p5 = l), (b = 1);
  } else if (t1.m === t2.m + 50 && Math.ceil(t1.n) === Math.ceil(t2.n)) {
    // Left Horizontal
    for (i = 0; i < 11; i++) {
      //Checking if there is a token in front of t2
      if (
        (p[i].m === t2.m - 50 && Math.ceil(p[i].n) === Math.ceil(t2.n)) ||
        (p2[i].m === t2.m - 50 && Math.ceil(p2[i].n) === Math.ceil(t2.n))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      //No token ahead of t2 => move t1,t2
      if (t2.m > getXLowerlimit(Math.ceil(t2.n))) {
        t1.m = t2.m;
        t2.m = t2.m - 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      //Check if token found can be pushed
      l = valid2(t1, t2, pass, "horizontalLeft");
    }
    p3 = t1;
    p4 = t2;
    (p5 = l), (b = 2);
  } else if (t2.m === t1.m + 25 && Math.ceil(t2.n) === Math.ceil(t1.n + 43.3)) {
    // Diagonal Down Right
    for (i = 0; i < 11; i++) {
      //Checking if there is a token in front of t2
      if (
        (p[i].m === t2.m + 25 &&
          Math.ceil(p[i].n) === Math.ceil(t2.n + 43.3)) ||
        (p2[i].m === t2.m + 25 && Math.ceil(p2[i].n) === Math.ceil(t2.n + 43.3))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      //No token ahead of t2 => move t1,t2
      if (
        (Math.ceil(t2.n) >= Math.ceil(d + 129.9) &&
          t2.m < getXUpperlimit(Math.ceil(t2.n)) &&
          Math.ceil(t2.n) < Math.ceil(d + 259.8)) ||
        Math.ceil(t2.n) < Math.ceil(d + 129.9)
      ) {
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = t2.m + 25;
        t2.n = t2.n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      l = valid2(t1, t2, pass, "diagonalDownRight");
    }
    p3 = t1;
    p4 = t2;
    (p5 = l), (b = 3);
  } else if (t2.m === t1.m - 25 && Math.ceil(t2.n) === Math.ceil(t1.n + 43.3)) {
    //Diagonal Down Left
    for (i = 0; i < 11; i++) {
      //Checking if there is a token in front of t2
      if (
        (p[i].m === t2.m - 25 &&
          Math.ceil(p[i].n) === Math.ceil(t2.n + 43.3)) ||
        (p2[i].m === t2.m - 25 && Math.ceil(p2[i].n) === Math.ceil(t2.n + 43.3))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      if (
        (Math.ceil(t2.n) >= Math.ceil(d + 129.9) &&
          t2.m > getXLowerlimit(Math.ceil(t2.n)) &&
          Math.ceil(t2.n) < Math.ceil(d + 259.8)) ||
        Math.ceil(t2.n) < Math.ceil(d + 129.9)
      ) {
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = t2.m - 25;
        t2.n = t2.n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      l = valid2(t1, t2, pass, "diagonalDownLeft");
    }
    p3 = t1;
    p4 = t2;
    p5 = l;
    b = 4;
  } else if (t2.m === t1.m + 25 && Math.ceil(t2.n) === Math.ceil(t1.n - 43.3)) {
    // Diagonal Up Right
    for (i = 0; i < 11; i++) {
      if (
        (p[i].m === t2.m + 25 &&
          Math.ceil(p[i].n) === Math.ceil(t2.n - 43.3)) ||
        (p2[i].m === t2.m + 25 && Math.ceil(p2[i].n) === Math.ceil(t2.n - 43.3))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      if (
        (Math.ceil(t2.n) <= Math.ceil(d + 129.9) &&
          t2.m < getXUpperlimit(Math.ceil(t2.n)) &&
          Math.ceil(t2.n) > Math.ceil(d)) ||
        Math.ceil(t2.n) > Math.ceil(d + 129.9)
      ) {
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = t2.m + 25;
        t2.n = t2.n - 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      l = valid2(t1, t2, pass, "diagonalUpRight");
    }
    p3 = t1;
    p4 = t2;
    (p5 = l), (b = 5);
  } else if (t1.m === t2.m + 25 && Math.ceil(t2.n) === Math.ceil(t1.n - 43.3)) {
    //Diagonal Up Left
    for (i = 0; i < 11; i++) {
      if (
        (p[i].m === t2.m - 25 &&
          Math.ceil(p[i].n) === Math.ceil(t2.n - 43.3)) ||
        (p2[i].m === t2.m - 25 && Math.ceil(p2[i].n) === Math.ceil(t2.n - 43.3))
      ) {
        count = 1;
        pass = i;
        break;
      }
    }
    if (count === 0) {
      if (
        (Math.ceil(t2.n) <= Math.ceil(d + 129.9) &&
          t2.m > getXLowerlimit(Math.ceil(t2.n)) &&
          Math.ceil(t2.n) > Math.ceil(d)) ||
        Math.ceil(t2.n) > Math.ceil(d + 129.9)
      ) {
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = t2.m - 25;
        t2.n = t2.n - 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      l = valid2(t1, t2, pass, "diagonalUpLeft");
    }
    p3 = t1;
    p4 = t2;
    (p5 = l), (b = 6);
  } else {
    console.log("Invalid Move! Please Try Again!");
    messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
  }
}

function confirm2(w, r) {
  //Checks if the position w,r is empty or not
  var v = 0;
  for (var i = 0; i < 11; i++) {
    if (
      (w === p[i].m && Math.ceil(r) === Math.ceil(p[i].n)) ||
      (p2[i].m === w && Math.ceil(p2[i].n) === Math.ceil(r))
    ) {
      v = 1;
      break;
    }
  }
  if (v === 0) {
    return 1;
  } else {
    return 0;
  }
}

function valid2(t1, t2, pushToken, moveDirection) {
  //if can eliminate
  //else if confirm
  //else invalid
  g = 0;
  if (turn) {
    if (
      moveDirection === "horizontalRight" &&
      t2.m + 50 === p2[pushToken].m &&
      Math.ceil(t2.n) === Math.ceil(p2[pushToken].n)
    ) {
      if (p2[pushToken].m === getXUpperlimit(p2[pushToken].n)) {
        if (Math.ceil(p2[pushToken].n) !== Math.ceil(d + 129.9)) {
          //Move and eliminate
          t1.m = t2.m;
          t2.m = t2.m + 50;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          messagesStatus.innerHTML += "Eliminated!<br>";
          g = 1;
          //if (p2[pushToken].n=== d - eliminatePosY2 && ) 
          //{

          //}

        } else {
          console.log("Invalid Move! Please Try Again! ");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        }
      } else if (confirm2(p2[pushToken].m + 50, p2[pushToken].n)) {
        //Move and push
        t1.m = t2.m;
        t2.m = p2[pushToken].m;
        p2[pushToken].m = p2[pushToken].m + 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p2[pushToken];
    } else if (
      moveDirection === "horizontalLeft" &&
      t2.m - 50 === p2[pushToken].m &&
      Math.ceil(t2.n) === Math.ceil(p2[pushToken].n)
    ) {
      if (p2[pushToken].m === getXLowerlimit(p2[pushToken].n)) {
        if (Math.ceil(p2[pushToken].n) !== Math.ceil(d + 129.9)) {
          //Move and eliminate
          t1.m = t2.m;
          t2.m = t2.m - 50;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        } else {
          console.log("Invalid Move! Please Try Again! ");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        }
      } else if (confirm2(p2[pushToken].m - 50, p2[pushToken].n)) {
        //Move and push
        t1.m = t2.m;
        t2.m = p2[pushToken].m;
        p2[pushToken].m = p2[pushToken].m - 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p2[pushToken];
    } else if (
      moveDirection === "diagonalDownRight" &&
      t2.m + 25 === p2[pushToken].m &&
      Math.ceil(t2.n + 43.3) === Math.ceil(p2[pushToken].n)
    ) {
      console.log("Here1");
      if (
        (p2[pushToken].m === getXUpperlimit(p2[pushToken].n) &&
          Math.ceil(p2[pushToken].n) >= Math.ceil(d + 129.9)) ||
        Math.ceil(p2[pushToken].n) === Math.ceil(d + 259.8)
      ) {
        console.log("Here2");
        if (
          p2[pushToken].m === s + 150 &&
          Math.ceil(p2[pushToken].n) === Math.ceil(d + 259.8)
        ) {
          console.log("Here3\nInvalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m + 25;
          t2.n = t2.n + 43.3;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
      } else if (confirm2(p2[pushToken].m + 25, p2[pushToken].n + 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p2[pushToken].m;
        t2.n = p2[pushToken].n;
        p2[pushToken].m = p2[pushToken].m + 25;
        p2[pushToken].n = p2[pushToken].n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p2[pushToken];
    } else if (
      moveDirection === "diagonalDownLeft" &&
      t2.m - 25 === p2[pushToken].m &&
      Math.ceil(t2.n + 43.3) === Math.ceil(p2[pushToken].n)
    ) {
      if (
        (p2[pushToken].m === getXLowerlimit(p2[pushToken].n) &&
          Math.ceil(p2[pushToken].n) >= Math.ceil(d + 129.9)) ||
        Math.ceil(p2[pushToken].n) === Math.ceil(d + 259.8)
      ) {
        if (
          p2[pushToken].m === s &&
          Math.ceil(p2[pushToken].n) === Math.ceil(d + 259.8)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m - 25;
          t2.n = t2.n + 43.3;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
      } else if (confirm2(p2[pushToken].m - 25, p2[pushToken].n + 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p2[pushToken].m;
        t2.n = p2[pushToken].n;
        p2[pushToken].m = p2[pushToken].m - 25;
        p2[pushToken].n = p2[pushToken].n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p2[pushToken];
    } else if (
      moveDirection === "diagonalUpRight" &&
      t2.m + 25 === p2[pushToken].m &&
      Math.ceil(t2.n - 43.3) === Math.ceil(p2[pushToken].n)
    ) {
      if (
        (p2[pushToken].m === getXUpperlimit(p2[pushToken].n) &&
          Math.ceil(p2[pushToken].n) <= Math.ceil(d + 129.9)) ||
        Math.ceil(p2[pushToken].n) === Math.ceil(d)
      ) {
        if (
          p2[pushToken].m === s + 150 &&
          Math.ceil(p2[pushToken].n) === Math.ceil(d)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m + 25;
          t2.n = t2.n - 43.3;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
      } else if (confirm2(p2[pushToken].m + 25, p2[pushToken].n - 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p2[pushToken].m;
        t2.n = p2[pushToken].n;
        p2[pushToken].m = p2[pushToken].m + 25;
        p2[pushToken].n = p2[pushToken].n - 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p2[pushToken];
    } else if (
      moveDirection === "diagonalUpLeft" &&
      t2.m - 25 === p2[pushToken].m &&
      Math.ceil(t2.n - 43.3) === Math.ceil(p2[pushToken].n)
    ) {
      if (
        (p2[pushToken].m === getXLowerlimit(p2[pushToken].n) &&
          Math.ceil(p2[pushToken].n) <= Math.ceil(d + 129.9)) ||
        Math.ceil(p2[pushToken].n) === Math.ceil(d)
      ) {
        if (
          p2[pushToken].m === s &&
          Math.ceil(p2[pushToken].n) === Math.ceil(d)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m - 25;
          t2.n = t2.n - 43.3;
          g1 = p2[pushToken].m;
          g2 = p2[pushToken].n
          p2[pushToken].m = eliminatePosX;
          p2[pushToken].n = d - eliminatePosY1;
          eliminatePosX += 50;
          c2++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
        return p2[pushToken];
      } else if (confirm2(p2[pushToken].m - 25, p2[pushToken].n - 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p2[pushToken].m;
        t2.n = p2[pushToken].n;
        p2[pushToken].m = p2[pushToken].m - 25;
        p2[pushToken].n = p2[pushToken].n - 43.3;
        turn = !turn;
        printTurn(turn);
        return p2[pushToken];
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      console.log("Invalid Move! Please Try Again!");
      messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
    }
  }




  else {
    if (
      moveDirection === "horizontalRight" &&
      t2.m + 50 === p[pushToken].m &&
      Math.ceil(t2.n) === Math.ceil(p[pushToken].n)
    ) {
      console.log("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd")
      console.log(Math.ceil(d + 129.9))
      if (p[pushToken].m === getXUpperlimit(p[pushToken].n)) {
        console.log(p[pushToken].n);
        if (Math.ceil(p[pushToken].n) !== Math.ceil(d + 129.9)) {
          //Move and eliminaonsole.
          t1.m = t2.m;
          t2.m = t2.m + 50;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated<br>";
        } else {
          console.log("Invalid Move! Please Try Again! ");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        }
      } else if (confirm2(p[pushToken].m + 50, p[pushToken].n)) {
        //Move and push
        t1.m = t2.m;
        t2.m = p[pushToken].m;
        p[pushToken].m = p[pushToken].m + 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p[pushToken];
    } else if (
      moveDirection === "horizontalLeft" &&
      t2.m - 50 === p[pushToken].m &&
      Math.ceil(t2.n) === Math.ceil(p[pushToken].n)
    ) {
      if (p[pushToken].m === getXLowerlimit(p[pushToken].n)) {
        if (Math.ceil(p[pushToken].n) !== Math.ceil(d + 129.9)) {
          //Move and eliminate
          t1.m = t2.m;
          t2.m = t2.m - 50;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        } else {
          console.log("Invalid Move! Please Try Again! ");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        }
      } else if (confirm2(p[pushToken].m - 50, p[pushToken].n)) {
        //Move and push
        t1.m = t2.m;
        t2.m = p[pushToken].m;
        p[pushToken].m = p[pushToken].m - 50;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p[pushToken];
    } else if (
      moveDirection === "diagonalDownRight" &&
      t2.m + 25 === p[pushToken].m &&
      Math.ceil(t2.n + 43.3) === Math.ceil(p[pushToken].n)
    ) {
      if (
        (p[pushToken].m === getXUpperlimit(p[pushToken].n) &&
          Math.ceil(p[pushToken].n) >= Math.ceil(d + 129.9)) ||
        Math.ceil(p[pushToken].n) === Math.ceil(d + 259.8)
      ) {
        if (
          p[pushToken].m === s + 150 &&
          Math.ceil(p[pushToken].n) === Math.ceil(d + 259.8)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m + 25;
          t2.n = t2.n + 43.3;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
      } else if (confirm2(p[pushToken].m + 25, p[pushToken].n + 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p[pushToken].m;
        t2.n = p[pushToken].n;
        p[pushToken].m = p[pushToken].m + 25;
        p[pushToken].n = p[pushToken].n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p[pushToken];
    } else if (
      moveDirection === "diagonalDownLeft" &&
      t2.m - 25 === p[pushToken].m &&
      Math.ceil(t2.n + 43.3) === Math.ceil(p[pushToken].n)
    ) {
      if (
        (p[pushToken].m === getXLowerlimit(p[pushToken].n) &&
          Math.ceil(p[pushToken].n) >= Math.ceil(d + 129.9)) ||
        Math.ceil(p[pushToken].n) === Math.ceil(d + 259.8)
      ) {
        if (
          p[pushToken].m === s &&
          Math.ceil(p[pushToken].n) === Math.ceil(d + 259.8)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m - 25;
          t2.n = t2.n + 43.3;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated!<br>";
        }
      } else if (confirm2(p[pushToken].m - 25, p[pushToken].n + 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p[pushToken].m;
        t2.n = p[pushToken].n;
        p[pushToken].m = p[pushToken].m - 25;
        p[pushToken].n = p[pushToken].n + 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("hhhInvalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p[pushToken];
    } else if (
      moveDirection === "diagonalUpRight" &&
      t2.m + 25 === p[pushToken].m &&
      Math.ceil(t2.n - 43.3) === Math.ceil(p[pushToken].n)
    ) {
      if (
        (p[pushToken].m === getXUpperlimit(p[pushToken].n) &&
          Math.ceil(p[pushToken].n) <= Math.ceil(d + 129.9)) ||
        Math.ceil(p[pushToken].n) === Math.ceil(d)
      ) {
        if (
          p[pushToken].m === s + 150 &&
          Math.ceil(p[pushToken].n) === Math.ceil(d)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m + 25;
          t2.n = t2.n - 43.3;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated<br>";
        }
      } else if (confirm2(p[pushToken].m + 25, p[pushToken].n - 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p[pushToken].m;
        t2.n = p[pushToken].n;
        p[pushToken].m = p[pushToken].m + 25;
        p[pushToken].n = p[pushToken].n - 43.3;
        turn = !turn;
        printTurn(turn);
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
      return p[pushToken];
    } else if (
      moveDirection === "diagonalUpLeft" &&
      t2.m - 25 === p[pushToken].m &&
      Math.ceil(t2.n - 43.3) === Math.ceil(p[pushToken].n)
    ) {
      if (
        (p[pushToken].m === getXLowerlimit(p[pushToken].n) &&
          Math.ceil(p[pushToken].n) <= Math.ceil(d + 129.9)) ||
        Math.ceil(p[pushToken].n) === Math.ceil(d)
      ) {
        if (
          p[pushToken].m === s &&
          Math.ceil(p[pushToken].n) === Math.ceil(d)
        ) {
          console.log("Invalid Move! Please Try Again!");
          messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
        } else {
          //Move and eliminate
          t1.m = t2.m;
          t1.n = t2.n;
          t2.m = t2.m - 25;
          t2.n = t2.n - 43.3;
          g1 = p[pushToken].m;
          g2 = p[pushToken].n;
          p[pushToken].m = eliminatePosX2;
          p[pushToken].n = d + 260 + eliminatePosY2;
          eliminatePosX2 += 50;
          c1++;
          turn = !turn;
          printTurn(turn);
          console.log("Eliminated");
          g = 1;
          messagesStatus.innerHTML += "Eliminated<br>";
        }
        return p[pushToken];
      } else if (confirm2(p[pushToken].m - 25, p[pushToken].n - 43.3)) {
        //Move and push
        t1.m = t2.m;
        t1.n = t2.n;
        t2.m = p[pushToken].m;
        t2.n = p[pushToken].n;
        p[pushToken].m = p[pushToken].m - 25;
        p[pushToken].n = p[pushToken].n - 43.3;
        turn = !turn;
        printTurn(turn);
        return p[pushToken];
      } else {
        console.log("Invalid Move! Please Try Again!");
        messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
      }
    } else {
      console.log("Invalid Move! Please Try Again!");
      messagesStatus.innerHTML += "Invalid Move! Please Try Again<br>";
    }
  }

  console.log(p2[pushToken]);
  console.log(p[pushToken]);
}

undoButton.onclick = function () {
  console.log(p5);
  console.log(g);
  console.log("Inside undo");
  if (count1 === 0) {
    turn = !turn;
    if (p5 == undefined) {
      if (b == 1) {
        p4.m = p3.m;
        p3.m = p3.m - 50;
      } else if (b == 2) {
        p4.m = p3.m;
        p3.m = p3.m + 50;
      } else if (b == 3) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n - 43.3;
      } else if (b == 4) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n - 43.3;
      } else if (b == 5) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n + 43.3;
      } else if (b == 6) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n + 43.3;
      }
      count1++;
    }

    else if (g == 1) {
      console.log("3rd case");
      if (b === 1) {
        p4.m = p3.m;
        p3.m = p3.m - 50;
        p5.m = g1;
        p5.n = g2;
      } else if (b === 2) {
        p4.m = p3.m;
        p3.m = p3.m + 50;
        p5.m = g1;
        p5.n = g2;
      } else if (b === 3) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n - 43.3;
        p5.m = g1;
        p5.n = g2;
      } else if (b === 4) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n - 43.3;
        p5.m = g1;
        p5.n = g2;
      } else if (b === 5) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n + 43.3;
        p5.m = g1;
        p5.n = g2;
      } else if (b === 6) {
        console.log("orngjkerbvjernvberjvberbernvuier");
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n + 43.3;
        p5.m = g1;
        p5.n = g2;
      }
      if (turn) {
        eliminatePosX -= 50;
        c2--;
      }
      else {
        eliminatePosX2 -= 50;
        c1--;
      }
      count1++;
    }

    else {
      console.log("2nd case");
      if (b === 1) {
        p4.m = p3.m;
        p3.m = p3.m - 50;
        p5.m = p5.m - 50;


      } else if (b === 2) {
        p4.m = p3.m;
        p3.m = p3.m + 50;
        p5.m = p5.m + 50;
      } else if (b === 3) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n - 43.3;
        p5.m = p5.m - 25;
        p5.n = p5.n - 43.3;
      } else if (b === 4) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n - 43.3;
        p5.m = p5.m + 25;
        p5.n = p5.n - 43.3;
      } else if (b === 5) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m - 25;
        p3.n = p3.n + 43.3;
        p5.m = p5.m - 25;
        p5.n = p5.n + 43.3;
      } else if (b === 6) {
        p4.m = p3.m;
        p4.n = p3.n;
        p3.m = p3.m + 25;
        p3.n = p3.n + 43.3;
        p5.m = p5.m + 25;
        p5.n = p5.n + 43.3;
      }
      count1++;
    }

  } else alert("UNDO ALLOWED ONLY ONCE!!");
};

//string input
var dict = {
  A: {
    "4": [s, d],
    "5": [50 + s, d],
    "6": [100 + s, d],
    "7": [150 + s, d]
  },
  B: {
    "3": [s - 25, 43.3 + d],
    "4": [25 + s, 43.3 + d],
    "5": [75 + s, 43.3 + d],
    "6": [125 + s, 43.3 + d],
    "7": [175 + s, 43.3 + d]
  },
  C: {
    "2": [s - 50, 86.6 + d],
    "3": [s, 86.6 + d],
    "4": [50 + s, 86.6 + d],
    "5": [100 + s, 86.6 + d],
    "6": [150 + s, 86.6 + d],
    "7": [200 + s, 86.6 + d]
  },
  D: {
    "1": [s - 75, 129.9 + d],
    "2": [s - 25, 129.9 + d],
    "3": [25 + s, 129.9 + d],
    "4": [75 + s, 129.9 + d],
    "5": [125 + s, 129.9 + d],
    "6": [175 + s, 129.9 + d],
    "7": [225 + s, 129.9 + d]
  },
  E: {
    "1": [s - 50, 173.2 + d],
    "2": [s, 173.2 + d],
    "3": [50 + s, 173.2 + d],
    "4": [100 + s, 173.2 + d],
    "5": [150 + s, 173.2 + d],
    "6": [200 + s, 173.2 + d]
  },
  F: {
    "1": [s - 25, 216.5 + d],
    "2": [25 + s, 216.5 + d],
    "3": [75 + s, 216.5 + d],
    "4": [125 + s, 216.5 + d],
    "5": [175 + s, 216.5 + d]
  },
  G: {
    "1": [s, 259.8 + d],
    "2": [50 + s, 259.8 + d],
    "3": [100 + s, 259.8 + d],
    "4": [150 + s, 259.8 + d]
  }
};
var str;
document.getElementById("stringbtn").onclick = function () {
  console.log("Hello");
  str = document.getElementById("stringip").value;
  document.getElementById("stringip").value = "";
  str = str.split(" ");
  cords1 = dict[str[0][0]][str[0][1]];
  x1 = cords1[0];
  y1 = cords1[1];

  cords2 = dict[str[1][0]][str[1][1]];
  x2 = cords2[0];
  y2 = cords2[1];

  t = check(x1, y1);
  u = check(x2, y2);

  console.log(
    "First token to be selected is " +
    "(" +
    x1 +
    "," +
    y1 +
    ")" +
    "Second token to be selected is " +
    x2 +
    "," +
    y2
  );

  move(t, u);
};
