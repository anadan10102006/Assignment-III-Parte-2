function totalMovement(path) {

    let total = 0;

    for(let i = 1; i < path.length; i++) {

        total += Math.abs(path[i] - path[i - 1]);
    }

    return total;
}

function createSVG(tag) {

    return document.createElementNS(
        "http://www.w3.org/2000/svg",
        tag
    );
}

function drawAxes(svg, width, height, padding, maxSteps) {

    // X AXIS

    const xAxis = createSVG("line");

    xAxis.setAttribute("x1", padding);
    xAxis.setAttribute("y1", height - padding);

    xAxis.setAttribute("x2", width - padding);
    xAxis.setAttribute("y2", height - padding);

    xAxis.setAttribute("stroke", "#444");
    xAxis.setAttribute("stroke-width", "2");

    svg.appendChild(xAxis);

    // Y AXIS

    const yAxis = createSVG("line");

    yAxis.setAttribute("x1", padding);
    yAxis.setAttribute("y1", padding);

    yAxis.setAttribute("x2", padding);
    yAxis.setAttribute("y2", height - padding);

    yAxis.setAttribute("stroke", "#444");
    yAxis.setAttribute("stroke-width", "2");

    svg.appendChild(yAxis);

    // Y LABELS + GRID

    for(let i = 0; i <= 5; i++) {

        const value =
            Math.round((MAX_CYLINDER / 5) * i);

        const y =
            height - padding -
            ((value / MAX_CYLINDER) * (height - 2 * padding));

        // GRID

        const grid = createSVG("line");

        grid.setAttribute("x1", padding);
        grid.setAttribute("y1", y);

        grid.setAttribute("x2", width - padding);
        grid.setAttribute("y2", y);

        grid.setAttribute("stroke", "#e5e7eb");

        svg.appendChild(grid);

        // LABEL

        const text = createSVG("text");

        text.setAttribute("x", padding - 10);

        text.setAttribute("y", y + 5);

        text.setAttribute("text-anchor", "end");

        text.setAttribute("font-size", "14");

        text.textContent = value;

        svg.appendChild(text);
    }

    // X LABELS + GRID

    for(let i = 0; i <= 10; i++) {

        const step =
            Math.round((maxSteps / 10) * i);

        const x =
            padding +
            (step / maxSteps) * (width - 2 * padding);

        // GRID

        const grid = createSVG("line");

        grid.setAttribute("x1", x);
        grid.setAttribute("y1", padding);

        grid.setAttribute("x2", x);
        grid.setAttribute("y2", height - padding);

        grid.setAttribute("stroke", "#f0f0f0");

        svg.appendChild(grid);

        // LABEL

        const text = createSVG("text");

        text.setAttribute("x", x);

        text.setAttribute("y", height - padding + 25);

        text.setAttribute("text-anchor", "middle");

        text.setAttribute("font-size", "14");

        text.textContent = step;

        svg.appendChild(text);
    }
}

function drawPath(
    svg,
    path,
    color,
    width,
    height,
    padding
) {

    const usableWidth =
        width - 2 * padding;

    const usableHeight =
        height - 2 * padding;

    const stepX =
        usableWidth / (path.length - 1);

    let points = [];

    for(let i = 0; i < path.length; i++) {

        const x =
            padding + i * stepX;

        const y =
            height - padding -
            (path[i] / MAX_CYLINDER) * usableHeight;

        points.push(`${x},${y}`);
    }

    const polyline = createSVG("polyline");

    polyline.setAttribute(
        "points",
        points.join(" ")
    );

    polyline.setAttribute("fill", "none");

    polyline.setAttribute("stroke", color);

    polyline.setAttribute("stroke-width", "2");

    svg.appendChild(polyline);

    // Dibujar puntos solo si hay pocos

    if(path.length < 80) {

        for(let i = 0; i < path.length; i++) {

            const x =
                padding + i * stepX;

            const y =
                height - padding -
                (path[i] / MAX_CYLINDER) * usableHeight;

            const circle = createSVG("circle");

            circle.setAttribute("cx", x);

            circle.setAttribute("cy", y);

            circle.setAttribute("r", "4");

            circle.setAttribute("fill", color);

            svg.appendChild(circle);
        }
    }
}

function createChart(
    svgId,
    paths,
    colors
) {

    const svg =
        document.getElementById(svgId);

    const width = 15000;

    const height = 450;

    const padding = 60;

    svg.innerHTML = "";

    svg.setAttribute("width", width);

    svg.setAttribute("height", height);

    const maxSteps =
        Math.max(
            ...paths.map(p => p.length)
        );

    drawAxes(
        svg,
        width,
        height,
        padding,
        maxSteps
    );

    for(let i = 0; i < paths.length; i++) {

        drawPath(
            svg,
            paths[i],
            colors[i],
            width,
            height,
            padding
        );
    }
}

function createBarChart() {

    const svg =
        document.getElementById("barChart");

    svg.innerHTML = "";

    const totals = [

        totalMovement(PATH_FCFS),

        totalMovement(PATH_SCAN),

        totalMovement(PATH_CSCAN)
    ];

    const labels = [

        "FCFS",

        "SCAN",

        "C-SCAN"
    ];

    const colors = [

        "#2563eb",

        "#d97706",

        "#059669"
    ];

    const width = 700;

    const height = 450;

    const padding = 60;

    svg.setAttribute("width", width);

    svg.setAttribute("height", height);

    const max =
        Math.max(...totals);

    // AXES

    const xAxis = createSVG("line");

    xAxis.setAttribute("x1", padding);
    xAxis.setAttribute("y1", height - padding);

    xAxis.setAttribute("x2", width - padding);
    xAxis.setAttribute("y2", height - padding);

    xAxis.setAttribute("stroke", "#444");

    svg.appendChild(xAxis);

    const yAxis = createSVG("line");

    yAxis.setAttribute("x1", padding);
    yAxis.setAttribute("y1", padding);

    yAxis.setAttribute("x2", padding);
    yAxis.setAttribute("y2", height - padding);

    yAxis.setAttribute("stroke", "#444");

    svg.appendChild(yAxis);

    for(let i = 0; i < totals.length; i++) {

        const barHeight =
            (totals[i] / max) * 260;

        const x =
            120 + i * 180;

        const y =
            340 - barHeight;

        // BAR

        const rect =
            createSVG("rect");

        rect.setAttribute("x", x);

        rect.setAttribute("y", y);

        rect.setAttribute("width", 100);

        rect.setAttribute("height", barHeight);

        rect.setAttribute("fill", colors[i]);

        rect.setAttribute("rx", "8");

        svg.appendChild(rect);

        // LABEL

        const label =
            createSVG("text");

        label.setAttribute("x", x + 50);

        label.setAttribute("y", 370);

        label.setAttribute("text-anchor", "middle");

        label.setAttribute("font-size", "15");

        label.setAttribute("font-weight", "600");

        label.textContent = labels[i];

        svg.appendChild(label);

        // VALUE

        const value =
            createSVG("text");

        value.setAttribute("x", x + 50);

        value.setAttribute("y", y - 10);

        value.setAttribute("text-anchor", "middle");

        value.setAttribute("font-size", "14");

        value.setAttribute("font-weight", "700");

        value.textContent = totals[i];

        svg.appendChild(value);
    }
}

// ===============================
// COMBINED GRAPH
// ===============================

createChart(
    "movementChart",
    [
        PATH_FCFS,
        PATH_SCAN,
        PATH_CSCAN
    ],
    [
        "#2563eb",
        "#d97706",
        "#059669"
    ]
);

// ===============================
// FCFS
// ===============================

createChart(
    "fcfsChart",
    [
        PATH_FCFS
    ],
    [
        "#2563eb"
    ]
);

// ===============================
// SCAN
// ===============================

createChart(
    "scanChart",
    [
        PATH_SCAN
    ],
    [
        "#d97706"
    ]
);

// ===============================
// C-SCAN
// ===============================

createChart(
    "cscanChart",
    [
        PATH_CSCAN
    ],
    [
        "#059669"
    ]
);

// ===============================
// BAR CHART
// ===============================

createBarChart();