//Reference: https://webgl2fundamentals.org/webgl/lessons/webgl-fundamentals.html
"use strict";

// Vertex shader source
//A vertex shader's job is to compute vertex positions. 
var vertexShaderSource = `#version 300 es

// #version 300 es tells to use GLSL ES 3.00
// an attribute is an input (in) to a vertex shader.
// It will receive data from a buffer
in vec4 a_position;

// all shaders have a main function
void main() {

    // gl_Position is a variable of a vertex shader
    gl_Position = a_position;
}
`;
//A fragment shader's job is to compute a color for each 
//pixel of the primitive currently being drawn.
var fragmentShaderSource = `#version 300 es

// Set "medium precision" for fragment shader
precision mediump float;

// Declare output for the fragment shader
out vec4 outColor;

void main() {
    // Set output color 
    outColor = vec4(1, 0, 0.5, 0.2);
}
`;
//VS and FS are two functions that run on the GPU of the machine
//and together they are called a program.
function createShader(gl, type, source) {
    var shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
    if (success) {
        return shader;
    }
    console.log(gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
    return undefined;
}

function createProgram(gl, vertexShader, fragmentShader) {
    var program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);
    gl.linkProgram(program);
    var success = gl.getProgramParameter(program, gl.LINK_STATUS);
    if (success) {
        return program;
    }
    console.log(gl.getProgramInfoLog(program));
    gl.deleteProgram(program);
    return undefined;
}

function main() 
{
    // Get WebGL context
    var canvas = document.getElementById("c");
    var gl = canvas.getContext("webgl2");
    if (!gl) 
    {
        return;
    }

    // Create shaders
    var vertexShader = createShader(
        gl, gl.VERTEX_SHADER, vertexShaderSource);
    var fragmentShader = createShader(
        gl, gl.FRAGMENT_SHADER, fragmentShaderSource);

    // Link the shaders into a program
    var program = createProgram(gl, vertexShader, fragmentShader);

    // Specify where the vertex data needs to go
    var positionAttributeLocation = gl.getAttribLocation(program, "a_position");

    // Create a buffer and bind it to ARRAY buffer
    var positionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

    var positions = [
        0, 0,
        0, 0.5,
        0.7, 0,
    ];
    gl.bufferData(gl.ARRAY_BUFFER, 
        new Float32Array(positions), gl.STATIC_DRAW);

    // Create a vertex array object (attribute state)
    var vao = gl.createVertexArray();

    // Make it current 
    gl.bindVertexArray(vao);

    // Turn on the attribute
    gl.enableVertexAttribArray(positionAttributeLocation);

    // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
    
    var size = 2;          // 2 components per iteration
    var type = gl.FLOAT;   // data type is float
    var normalize = false; // don't normalize the data
    var stride = 0;        // 0 = size * sizeof(type) to get next position
    var offset = 0;        // offset in the buffer
    
    gl.vertexAttribPointer(
        positionAttributeLocation, size, type, normalize, stride, offset);

    webglUtils.resizeCanvasToDisplaySize(gl.canvas);

    // Tell WebGL how to convert from clip space to pixels
    gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

    // Clear the canvas
    gl.clearColor(0, 0, 0, 0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    // Tell it to use our program (pair of shaders)
    gl.useProgram(program);

    // Bind the attribute/buffer set we want.
    gl.bindVertexArray(vao);

    // draw
    var primitiveType = gl.TRIANGLES;
    var offset = 0;
    var count = 3;
    //vertex shader will be exxecuted 3 times.
    gl.drawArrays(primitiveType, offset, count);
    //gl.drawArrays executes the shaders on the GPU
}

main();
