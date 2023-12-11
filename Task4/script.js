// function f(x) {
//     return x * x;
//3x^2+2x+2
// }

// Функция для вычисления значения производной порядка n методом конечных разностей
function numericalDerivative(x, func) {
    const h = 1e-6;
    return (func(x + h) - func(x - h)) / (2 * h);
}

// Функция для нахождения максимального значения производной порядка n на заданном отрезке
function findMaxDerivativeOnInterval(f, a, b, order, h = 0.002) {

    let maxDerivative = Number.NEGATIVE_INFINITY;
    let currentDerivative;
    for (let x = a; x <= b; x += h) {
        let tmp = x;
        for(let i = 0; i < order; i++){
            currentDerivative = numericalDerivative(tmp, f);
            tmp = currentDerivative;
        }
       
        
        if (currentDerivative > maxDerivative) {
            maxDerivative = currentDerivative;
        }
    }

    return maxDerivative;
}

function exactIntegral(a, b, integral) {
    return (integral(b) - integral(a));
}

function integrateUsingQuadrature(a, b, n, quadratureFunction, f) {
    const h = (b - a) / n;
    let sum = 0;

    for (let i = 0; i < n; i++) {
        const xi = a + i * h;
        sum += quadratureFunction(xi, h, f);
    }

    return sum*h;
}

function leftRectangle(xi, h, f) {
    return f(xi);
}

function rightRectangle(xi, h, f) {
    return f(xi + h);
}

function midRectangle(xi, h, f) {
    return f(xi + h / 2);
}

function trapezoid(xi, h, f) {
    return (f(xi) + f(xi + h)) / 2;
}

function simpson(xi, h, f) {
    return (f(xi) + 4 * f(xi + h / 2) + f(xi + h)) / 6;
}

function threeEighths(xi, h, f) {
    
    return (f(xi) + 3 * f(xi + h / 3) + 3 * f(xi + 2 * h / 3) + f(xi + h)) / 8;
}

function runge(val1, val2, d, l){
    //left right 0, mid trap = 1, simps = 3
    let mult = (l ** (d+1) * val1- val2)/(l ** (d+1)-1);
    return mult;
}

function fillErrorRate(arr, it){
    for(let j = 0; j < 6; j++){
        arr[it].push(Math.abs(arr[it-1][j + 2] - arr[0][1]));
    }
}

function fillArray(a, b, n, func, arr){
    
    let quadFuncs = [leftRectangle, rightRectangle, midRectangle, trapezoid, simpson, threeEighths]
    for(let i = 0; i < quadFuncs.length; i++){
        arr[0].push(integrateUsingQuadrature(a, b, n, quadFuncs[i], func));
    }
    
}

function fillRunge(arr1, arr2){
    for(let i = 2; i < 8; i++){
        var ast = [0, 0, 1, 1, 3, 0];
        arr1[2].push(runge(arr1[0][i], arr2[0][i], ast[i-2], l));
    }
    
    fillErrorRate(arr1, 3);

}
function fillTheory(arr, a, b, m, f){
    let h = (b-a)/m;
    const cAst = [1/2, 1/2, 1/24, 1/12, 1/2880];
    var ast = [1, 1, 2, 2, 3];
    for(let i = 2; i < cAst.length+2; i++){
        arr[2].push(cAst[i-2]*findMaxDerivativeOnInterval(f, a, b, ast[i-2])*(b-a)*(h ** (ast[i-2])));
    }
}



document.getElementById('createTableBtn').addEventListener('click', function () {
    
    var userInput = document.getElementById('func').value;
    var func = new Function('x', 'return ' + userInput);

    var userIntegral = document.getElementById('integral').value;
    var integral = new Function('x', 'return ' + userIntegral);


    const a = parseFloat(document.getElementById('lowerLimit').value);
    const b = parseFloat(document.getElementById('upperLimit').value);
    n = parseInt(document.getElementById('intervals').value);
    l = parseInt(document.getElementById('multiplier').value);

    if(isNaN(a) || isNaN(b)){
        return;
    }

    const exactValue = exactIntegral(a, b, integral);

    let rows = 2;
    let colums = 7;
    let dev = false;
    let theory = false;

    var rowsval = ['Точное значение', 'Погрешность'];

    if(isNaN(n) || l <= 0){
        n = 1;
        l = 1;
    }
    else if(isNaN(l)){
        l = 1;
        theory = true;
        rows = 3;
        rowsval.push('Теоретическая погрешность');
    
    }else{
        dev = true;
        rows = 4;
        let compose = n*l;
        var composeVal = [[compose, exactValue], ['', 0], ['', ''], ['', 0]];
        fillArray(a, b, compose, func, composeVal);
        fillErrorRate(composeVal, 1);
        rowsval.push('Уточненные значения по Рунге');
        rowsval.push('Погрешность Рунге');
    }
    
    if(n == 1){
        colums = 8;
    }

    var valtest = [[n, exactValue], ['', 0]];
    fillArray(a, b, n, func, valtest);
    fillErrorRate(valtest, 1);

    if(theory){
        valtest.push(['', 0]);
        fillTheory(valtest, a, b, n, func);
    }

    if(dev){
        fillRunge(composeVal, valtest);
        valtest = composeVal;
    }
   
    
    
    // Создаем элемент таблицы
    var table = document.createElement('table');
    table.classList.add('table');
    
    
    var tbody = document.createElement('tbody');
    for (var i = 1; i <= rows; i++) {
        var row = document.createElement('tr');
        
        var thRow = document.createElement('th');
        thRow.scope = 'row';
        thRow.textContent = rowsval[i-1];
        row.appendChild(thRow);

        for (var j = 1; j <= colums; j++) {
            var td = document.createElement('td');
            td.textContent = valtest[i-1][j-1];
            row.appendChild(td);
        }
        tbody.appendChild(row);
    }
    table.appendChild(tbody);

    // Создаем строку заголовка
    var thead = document.createElement('thead');
    var headerRow = document.createElement('tr');
    var headers = ['','Итоговое значение n', 'Точное значение интеграла', 'Левый прямоугольник', 'Правый прямоугольник', 'Средний прямоугольник', 'Трапеция', 'Симпсон', '3/8'];

    if(n != 1){
        headers.pop();
    }
    
    headers.forEach(function (headerText) {
      var th = document.createElement('th');
      th.textContent = headerText;
      headerRow.appendChild(th);
    });
  
    thead.appendChild(headerRow);
    table.appendChild(thead);
  
    // Очищаем содержимое контейнера и добавляем таблицу
    var tableContainer = document.getElementById('tableContainer');
    tableContainer.innerHTML = '';
    tableContainer.appendChild(table);
  });