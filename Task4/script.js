// function f(x) {
//     return x * x;
//3x^2+2x+2
// }

function integral(k){
    return k * k * k + 2 * k * k + 7 * k;
}

function exactIntegral(a, b) {
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
    let mult = (l^(d+1)* val1- val2)/(l^(d+1)-1);
    return mult;
}
function fillArray(a, b, n, func, arr){
    
    let quadFuncs = [leftRectangle, rightRectangle, midRectangle, trapezoid, simpson, threeEighths]
    for(let i = 0; i < quadFuncs.length; i++){
        arr[0].push(integrateUsingQuadrature(a, b, n, quadFuncs[i], func));
    }
    for(let j = 0; j < quadFuncs.length; j++){
        arr[1].push(Math.abs(arr[0][j + 2] - arr[0][1]));
    }
}



document.getElementById('createTableBtn').addEventListener('click', function () {
    
    var userInput = document.getElementById('func').value;
    var func = new Function('x', 'return ' + userInput);

    // const f = '2 * x^2 + 3 * x';
    // const res = math.evaluate('integral(${fu}, x, 0, 1)');

    //var integ = new Function('x', 'return ' + expr);


    const a = parseFloat(document.getElementById('lowerLimit').value);
    const b = parseFloat(document.getElementById('upperLimit').value);
    n = parseInt(document.getElementById('intervals').value);
    l = parseInt(document.getElementById('multiplier').value);

    if(isNaN(a) || isNaN(b)){
        return;
    }

    const exactValue = exactIntegral(a, b);

    if(isNaN(n) || l <= 0){
        n = 1;
        l = 1;
    }
    else if(isNaN(l)){
        l = 1;
    }else{
        let compose = n*l;
    }
    let colums = 7
    if(n == 1){
        colums = 8;
    }

    var valtest = [[n, exactValue], ['', 0]];
    fillArray(a, b, n, func, valtest);
    
    // Создаем элемент таблицы
    var table = document.createElement('table');
    table.classList.add('table');
    
    var rows = ['Точное значение', 'Погрешность']
    
    var tbody = document.createElement('tbody');
    for (var i = 1; i <= 2; i++) {
        var row = document.createElement('tr');
        
        var thRow = document.createElement('th');
        thRow.scope = 'row';
        thRow.textContent = rows[i-1];
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