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


document.getElementById('createTableBtn').addEventListener('click', function () {

    const a = parseFloat(document.getElementById('lowerLimit').value);
    const b = parseFloat(document.getElementById('upperLimit').value);
    n = parseInt(document.getElementById('intervals').value);
    l = parseInt(document.getElementById('multiplier').value);

    if(isNaN(a) || isNaN(b)){
        return;
    }
    if(isNaN(n) || l <= 0){
        n = 1;
        l = 1;
    }
    else if(isNaN(l)){
        l = 1;
    }else{
        n *= l;
    }
    let colums = 7
    if(n == 1){
        colums = 8;
    }

    const exactValue = exactIntegral(a, b);

    var values = [[n, exactValue, integrateUsingQuadrature(a, b, n, leftRectangle), integrateUsingQuadrature(a, b, n, rightRectangle), integrateUsingQuadrature(a, b, n, midRectangle), 
        integrateUsingQuadrature(a, b, n, trapezoid), integrateUsingQuadrature(a, b, n, simpson), integrateUsingQuadrature(a, b, n, threeEighths)],
        ['', 0, Math.abs(integrateUsingQuadrature(a, b, n, leftRectangle) - exactValue), Math.abs(integrateUsingQuadrature(a, b, n, rightRectangle) - exactValue), Math.abs(integrateUsingQuadrature(a, b, n, midRectangle) - exactValue),
         Math.abs(integrateUsingQuadrature(a, b, n, trapezoid) - exactValue), Math.abs(integrateUsingQuadrature(a, b, n, simpson) - exactValue), Math.abs(integrateUsingQuadrature(a, b, n, threeEighths) - exactValue)]]

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
            td.textContent = values[i-1][j-1];
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