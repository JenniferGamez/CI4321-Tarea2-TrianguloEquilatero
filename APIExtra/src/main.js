let sideLength = 200; // longitud de los lados del triangulo
let height;
let margin = 50;

function setup() {
    createCanvas(windowWidth, windowHeight);
    calculateTriangleHeight();
}

function draw() {
    // Valor Hexadecimal (#1b1e2b) a RGB - FONDO
    // Rojo (R): 1b en hexadecimal = 27 en decimal = 27
    // Verde (G): 1e en hexadecimal = 30 en decimal = 30
    // Azul (B): 2b en hexadecimal = 43 en decimal = 43 
    background(27, 30, 43); // Color de fondo

    // Calcular los vertices del triangulo para centrarlo
    let topVertex = createVector(width / 2, height / 2 - height / 2 + margin);
    let leftVertex = createVector(width / 2 - sideLength / 2, height / 2 + height / 2 + margin);
    let rightVertex = createVector(width / 2 + sideLength / 2, height / 2 + height / 2 + margin);

    // Color
    let red = color(255, 0, 0);
    let green = color(0, 255, 0);
    let blue = color(0, 0, 255);

    // Degradado interno en el triangulo 
    for (let y = topVertex.y; y <= leftVertex.y; y++) {
        let inter = map(y, topVertex.y, leftVertex.y, 0, 1);
        let c1 = lerpColor(red, green, inter); // De rojo a verde
        let c2 = lerpColor(red, blue, inter); // De rojo a azul

        // Calcular la posicion de los extremos de la linea
        let x1 = lerp(topVertex.x, leftVertex.x, map(y, topVertex.y, leftVertex.y, 0, 1));
        let x2 = lerp(topVertex.x, rightVertex.x, map(y, topVertex.y, rightVertex.y, 0, 1));

        // Dibujar las lineas con el color interpolado
        for (let x = x1; x <= x2; x++) {
            let inter2 = map(x, x1, x2, 0, 1);
            let c = lerpColor(c1, c2, inter2);
            stroke(c);
            line(x, y, x, y);
        }
    }

    // Dibujar el contorno del triangulo
    stroke(0);
    strokeWeight(1);
    noFill();
    triangle(topVertex.x, topVertex.y, leftVertex.x, leftVertex.y, rightVertex.x, rightVertex.y);
}

// Funcion para calcular la altura del triangulo con el Teorema de Pitagora
function calculateTriangleHeight() {
    height = sqrt((sideLength ** 2) - ((sideLength / 2) ** 2));
}

// Ajustar el tamaño al cambiar la ventana
function windowResized() {
    resizeCanvas(windowWidth, windowHeight);
    calculateTriangleHeight();
}
