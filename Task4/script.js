function f(x) {
    return x * x;
}

function exactIntegral(a, b) {
    return (b ** 3 - a ** 3) / 3;
}

function integrateUsingQuadrature(a, b, n, quadratureFunction) {
    const h = (b - a) / n;
    let sum = 0;

    for (let i = 0; i < n; i++) {
        const xi = a + i * h;
        sum += quadratureFunction(xi, h);
    }

    return sum*h;
}

function leftRectangle(xi, h) {
    return f(xi);
}

function rightRectangle(xi, h) {
    return f(xi + h);
}

function midRectangle(xi, h) {
    return f(xi + h / 2);
}

function trapezoid(xi, h) {
    return (f(xi) + f(xi + h)) / 2;
}

function simpson(xi, h) {
    return (f(xi) + 4 * f(xi + h / 2) + f(xi + h)) / 6;
}

function threeEighths(xi, h) {
    return (f(xi) + 3 * f(xi + h / 3) + 3 * f(xi + 2 * h / 3) + f(xi + h)) / 8;
}

function calculateIntegral() {
    const a = parseFloat(document.getElementById('lowerLimit').value);
    const b = parseFloat(document.getElementById('upperLimit').value);
    const n = parseInt(document.getElementById('intervals').value);
    
    const exactValue = exactIntegral(a, b);

    const output = document.getElementById('output');
    output.innerHTML = `<p>Точное значение интеграла: ${exactValue}</p>`;

    output.innerHTML += `<p>Левый прямоугольник: ${integrateUsingQuadrature(a, b, n, leftRectangle)}</p>`;
    output.innerHTML += `<p>Правый прямоугольник: ${integrateUsingQuadrature(a, b, n, rightRectangle)}</p>`;
    output.innerHTML += `<p>Средний прямоугольник: ${integrateUsingQuadrature(a, b, n, midRectangle)}</p>`;
    output.innerHTML += `<p>Трапеция: ${integrateUsingQuadrature(a, b, n, trapezoid)}</p>`;
    output.innerHTML += `<p>Симпсон: ${integrateUsingQuadrature(a, b, n, simpson)}</p>`;
    output.innerHTML += `<p>3/8: ${integrateUsingQuadrature(a, b, n, threeEighths)}</p>`;

    output.innerHTML += `<p>Погрешность левого прямоугольника: ${Math.abs(integrateUsingQuadrature(a, b, n, leftRectangle) - exactValue)}</p>`;
    output.innerHTML += `<p>Погрешность правого прямоугольника: ${Math.abs(integrateUsingQuadrature(a, b, n, rightRectangle) - exactValue)}</p>`;
    output.innerHTML += `<p>Погрешность среднего прямоугольника: ${Math.abs(integrateUsingQuadrature(a, b, n, midRectangle) - exactValue)}</p>`;
    output.innerHTML += `<p>Погрешность трапеции: ${Math.abs(integrateUsingQuadrature(a, b, n, trapezoid) - exactValue)}</p>`;
    output.innerHTML += `<p>Погрешность Симпсона: ${Math.abs(integrateUsingQuadrature(a, b, n, simpson) - exactValue)}</p>`;
    output.innerHTML += `<p>Погрешность 3/8: ${Math.abs(integrateUsingQuadrature(a, b, n, threeEighths) - exactValue)}</p>`;
}