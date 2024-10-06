import * as THREE from 'three';

// Crear escena
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x1b1e2b)

// Crear camara
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );
// Posicionar la camara
camera.position.z = 4;

// Crear renderizador
const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

// Ajustar tamaño al cambiar el tamaño de la ventana
window.addEventListener('resize', () => {
    const width = window.innerWidth;
    const height = window.innerHeight;
    renderer.setSize(width, height);
    camera.aspect = width / height;
    camera.updateProjectionMatrix();
});

// Crear un triangulo equilatero
const geometry = new THREE.BufferGeometry();

const sideLength = 2; // longitud de los lados del triangulo
const height = Math.sqrt((sideLength ** 2) - ((sideLength / 2) ** 2)); // Teorema de Pitagora

const vertices = new Float32Array([
    0.0, height / 2, 0.0,  // Vertice superior 
    -sideLength / 2, -height / 2, 0.0,  // Vertice inferior izquierdo
    sideLength / 2, -height / 2, 0.0   // Vertice inferior derecho
]);

// Asignar los vertices a la geometria
geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3));

// Colores para cada vertice, normalizado
const colors = new Float32Array([
    1, 0, 0,  // Rojo en el vertice superior (ff0000)
    0, 1, 0,  // Verde en el vertice inferior izquierdo (00ff00)
    0, 0, 1   // Azul en el vertice inferior derecho (0000ff)
]);

// Asociar los colores con el trinagulo
geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));

// Crear material para el triangulo
const material = new THREE.MeshBasicMaterial({ vertexColors: true });

// Crear el triangulo(malla)
const triangle = new THREE.Mesh(geometry, material);
scene.add(triangle);


// Renderizar el triangulo
function animate() {
	renderer.render( scene, camera );
}
renderer.setAnimationLoop( animate );