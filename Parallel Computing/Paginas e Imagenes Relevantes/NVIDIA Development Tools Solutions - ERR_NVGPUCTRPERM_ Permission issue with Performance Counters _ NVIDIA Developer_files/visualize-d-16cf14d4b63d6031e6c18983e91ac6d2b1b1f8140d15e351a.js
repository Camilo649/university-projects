/**
 * Wrap the text element into lines that fit within the given width.
 */
function wrap(text, width, lineHeight) {
  text.each(function () {
    var self = d3.select(this);
    var words = self.text().split(/\s+/).reverse();
    var word;
    var line = [];
    var x = self.attr("x");
    var tspan = self.text(null).append("tspan").attr("x", x).attr("dy", lineHeight + "em");

    while (word = words.pop()) {
      line.push(word);
      tspan.text(line.join(" "));
      if (tspan.node().getComputedTextLength() > width) {
        line.pop();
        tspan.text(line.join(" "));
        line = [word];
        tspan = text.append("tspan").attr("x", x).attr("dy", lineHeight + "em").text(word);
      }
    }
  });
}


/**
 * Animate in the chart -- first axes, then bars, then inner/outer bar labels.
 *
 * @param chart - A javascript object with attributes "svg", "x", and "data".
 *   "svg" should be a d3 selection of the chart svg
 *   "x" should be the scale function for the x axis
 *   "data" for the bar data if bar labels are present
 * @param barAnimationDuration - The duration in ms of bar animations.
 * @param animationDelay - The delay in ms to offset bar animations.
 */
function animate(chart, barAnimationDuration, animationDelay) {
  var bars = chart.svg.selectAll(".bar");
  var barLabels = chart.svg.selectAll(".bar-label, .outer-bar-label");

  bars.attr("width", 0);

  if (barLabels) {
    barLabels.style("opacity", 0);
  }

  // Fade in chart.
  chart.svg.selectAll("g")
    .style("opacity", 0)
    .transition()
    .duration(1000)
    .style("opacity", 1);

  // Animate in bars.
  bars.transition()
    .duration(barAnimationDuration)
    .delay(function (d, i) {
      return 1000 + animationDelay * i;
    })
    .attr("width", function (d) { return chart.x(d.value); });

  // Fade in intra-bar labels.
  if (barLabels) {
    barLabels.transition()
      .duration(1000)
      .delay(function (d, i) { return 1000 + animationDelay * chart.data.length; })
      .style("opacity", 1);
  }
}


function drawYAxis(g, y, tickPadding, lineHeight, yAxisLabelClass) {

  g.append("g")
    .attr("class", "y axis y-axis-label")
    .call(d3.axisLeft(y).tickSize(0).tickPadding(tickPadding));

  var yAxisLabels = g.selectAll(".y .tick text");

  if (yAxisLabelClass) {
    yAxisLabels.attr("class", yAxisLabelClass);
  }

  yAxisLabels.each(function (t) {
    var lines = t.split("\n");

    if (lines.length == 2) {
      var x = -tickPadding;
      var offset = "-.4em";
      if (yAxisLabelClass == "title-subtitle") {
        offset = "-.2em";
      }

      self = d3.select(this);
      self.text(null);
      self.append("tspan")
        .attr("x", x)
        .attr("dy", offset)
        .text(lines[0]);
      self.append("tspan")
        .attr("x", x)
        .attr("dy", lineHeight + "em")
        .text(lines[1]);
    }
  });
}

/**
 * Add a legend of squares and labels to the provided d3 selected div.
 *
 * @param legend - A d3 selection of the div to add the legend to.
 * @param data - One row per legend entry, each with values
 *   "label" and "class".
 * @param milestone - Optional, an object with a "color" value for a
 *   milestone line in the chart, will be added as the last legend entry.
 */
function addLegend(legend, data, milestone, greenScale, numGreens) {
  // Copy data before modifying.
  data = data.slice();
  if (milestone) {
    data.push({"label": milestone.label, "class": "milestone-square"});
  }
  var keys = data.map(function (l) { return l.label; });

  var color = d3.scaleOrdinal()
    .range(data.map(function (l) { return l.class; }))
    .domain(keys);

  // Add a div for each legend entry.
  var legendEntry = legend.selectAll("div")
    .data(data)
    .enter()
    .append("div").attr("class", "legend-entry");

  // Add the square for each legend entry.
  legendEntry.append("div")
    .attr("class", function (l) { return "legend-square " + color(l.label); })
    .style("background-color", function (l, i) {
      if (color(l.label) == "green") {
        return greenScale(i / numGreens);
      }
    });

  // Add the text for each legend entry.
  legendEntry.append("div")
    .attr("class", "legend-text")
    .html(function (d) { return d.label; });

  if (milestone) {
    var milestoneSquare = legend.select(".milestone-square")
    var boundingRect = milestoneSquare.node().getBoundingClientRect();
    var svg = milestoneSquare.append("svg");
    svg.attr("width", boundingRect.width);
    svg.attr("height", boundingRect.height);
    svg.append("g")
      .append("line")
      .attr("class", "milestone " + milestone.class)
      .attr("x1", 0)
      .attr("x2", boundingRect.width)
      .attr("y1", 1)
      .attr("y2", 1);
  }
}

/**
 * Add a simple horizontal bar chart to the provided svg element.
 *
 * @param svg - A d3 selection of the svg to add the chart to.
 * @param data - One row per horizontal bar, each with attributes
 *   "label", "value", and "class".
 *   E.g. For a two-bar chart comparing Quadro P5000 to CPU:
 *     [
 *       {"label": "Quadro P5000", "value": 7.3, "class": "green"},
 *       {"label": "CPU", "value": 1, "class": "blue"}
 *     ]
 * @param ticks - The ticks to show on the x-axis, each with attributes
 *   "tickLabel", "value", and "class".
 *   E.g. For 3 ticks, with the middle tick hidden for mobile:
 *     [
 *       {"tickLabel": "0", "value": 0, "class": ""},
 *       {"tickLabel": "1X", "value": 1, "class": "mobile-hide"},
 *       {"tickLabel": "2X", "value": 2, "class": ""}
 *     ]
 * @param xAxisLabel - The label to show under the x axis.
 * @param yAxisLabelClass - Passing an option to this parameter turns on
 *   special styling for the y-axis, which is useful when the labels
 *   for the bars in the y-axis spill over to two lines. Labels will
 *   be split into lines on "\n", extra padding will be added between
 *   bars, and font will be smaller to accommodate the extra line.
 *   Supported options:
 *     "" - For default styling, leaving labels as single lines.
 *     "two-lines" - Both lines will be slightly smaller in font than default.
 *     "title-subtitle" - Second line will be smaller than first line.
 * @param isDark - true to enable styling for dark background, otherwise false.
 */
function createHorizontalBarChart(svg, data, barPadding, ticks, xAxisLabel, yAxisLabel, yAxisLabelClass, isDark) {
  var barAnimationDuration = 1000;
  var animationDelay = 200;

  var chart = drawHorizontalBarChart(svg, data, barPadding, ticks, xAxisLabel, yAxisLabel, yAxisLabelClass, isDark);

  // If the chart should be immediately visible, begin animation.
  var rendered = false;
  if (svg.node().getBoundingClientRect().top - window.innerHeight <= 0) {
    rendered = true;
    animate(chart, barAnimationDuration, animationDelay);
  }

  // Begin animation the first time the chart scrolls into view.
  window.addEventListener("scroll", function () {
    if (!rendered && svg.node().getBoundingClientRect().top - window.innerHeight <= 0) {
      rendered = true;
      animate(chart, barAnimationDuration, animationDelay);
    }
  });

  // Redraw whenever the browser window is resized.
  var viewPortDimensionsHandler = function () {
    svg.selectAll("*").remove();
    drawHorizontalBarChart(svg, data, barPadding, ticks, xAxisLabel, yAxisLabel, yAxisLabelClass, isDark);
  };
  window.addEventListener("resize", viewPortDimensionsHandler);
  window.addEventListener("orientationchange", viewPortDimensionsHandler);
}

function drawHorizontalBarChart(svg, data, barPadding, ticks, xAxisLabel, yAxisLabel, yAxisLabelClass, isDark) {
  // Right margin leaves room for last tick label.
  var margin = {
    top: 0,
    right: 20,
    bottom: 0,
    left: yAxisLabel ?100 : 30
  };
  var barHeight = 20;
  if (yAxisLabelClass == "two-lines" || yAxisLabelClass == "title-subtitle") {
    barPadding = 10;
  }

  var tickPadding = barPadding;
  var lineHeight = 1.1;  // ems.

  // The graph's width is set to fit within its parent container.
  var svgWidth = svg.node().parentNode.getBoundingClientRect().width;
  svg.attr("width", svgWidth);

  if (isDark) {
    svg.attr("class", yAxisLabelClass + " dark");
  }
  else {
    svg.attr("class", yAxisLabelClass);
  }

  // The graph's height is a function of the number of bars.
  var height = (barHeight * data.length + barPadding * (data.length + 1));

  var g = svg.append("g").attr("class", "graph");

  var y = d3.scaleBand().range([0, height]);
  y.domain(data.map(function (d) { return d.axisLabel; }))
    .padding(0.2);

  // Draw the y axis to know how much space to leave for it,
  // then immediately delete it. Redrawing it last ensures
  // the correct ordering of layers for display.
  drawYAxis(g, y, tickPadding, lineHeight, yAxisLabelClass);
  var yAxisWidth = svg.select(".y").node().getBoundingClientRect().width;
  svg.select("g.y.axis").remove();

  var width = svgWidth - margin.left - yAxisWidth - margin.right;
  g.attr("transform", "translate(" + (yAxisWidth + margin.left) + "," + margin.top + ")");

  var x = d3.scaleLinear().range([0, width]);
  var min = d3.min(ticks, function(d) { return d.value; });
  var max = d3.max(ticks, function(d) { return d.value; });
  x.domain([min, max]);
  var xAxis = d3.axisBottom(x)
    .tickValues(ticks.map(function(tick) { return tick.value; }))
    .tickFormat(function(d, i) { return ticks[i].tickLabel; })
    .tickSizeInner([-height])
    .tickSizeOuter(0)
    .tickPadding(tickPadding);

  g.append("g")
    .attr("class", "x axis tick-label")
    .attr("transform", "translate(0," + height + ")")
    .call(xAxis);

  svg.selectAll(".x .tick").each(function(t, i) {
    d3.select(this).attr("class", ticks[i].class);
  });

  var greenBegin = "#76b900";
  var greenEnd = "#c8e399";
  if (isDark) {
    greenEnd = "#3b5d00";
  }
  var greenScale = d3.interpolateLab(greenBegin, greenEnd);

  var numGreens = 0;
  for (var i = 0; i < data.length; i++) {
    if (data[i].class == "green") {
      numGreens++;
    }
  }

  var bars = g.selectAll(".bar")
    .data(data).enter().append("g")
    .attr("transform", function(d, i) { return "translate(0," + y(d.axisLabel) + ")"; });

  bars.append("rect")
    .attr("class", function(d) { return "bar " + d.class; })
    .attr("fill", function(d, i) {
      if (d.class == "green") {
        return greenScale(i/numGreens);
      }
    })
    .attr("x", 0)
    .attr("height", barHeight)
    .attr("width", function(d) { return Math.abs(x(d.value)); });

  // Add labels on bars
  var barLabels = bars.append("text")
    .attr("class", "bar-label")
    .attr("x", function(d) { return x(d.value) - 6; })
    .attr("y", barHeight / 2)
    .attr("dy", ".35em")
    .text(function(d) { return d.barLabel; });

  barLabels.each(function() {
    if (this.getBoundingClientRect().left < yAxisWidth + 380)
    {
      var labelWidth = this.getBoundingClientRect().width;
      var bar = d3.select(this.parentNode).select(".bar");
      var barWidth = bar.node().getBoundingClientRect().width;
      if (labelWidth + 13 > width - barWidth) {
        this.remove();
      } else {
        d3.select(this)
          .attr("transform", "translate(" + 12 + ",0)")
          .attr("class","outer-bar-label")
          .style("text-anchor", "start");
      }
    }
  });

  var xAxisHeight = svg.select(".x.axis.tick-label").node().getBoundingClientRect().height;

  // Add a label to the x axis.
  if (xAxisLabel) {
    g.append("text")
      .attr("x", width / 2)
      .attr("y", xAxisHeight + 5)
      .attr("class", "axis-label")
      .attr("alignment-baseline", "hanging")
      .text(xAxisLabel)
      .call(wrap, width, lineHeight);
  }

  if (yAxisLabel) {
    const yLabelGroup = svg.append("text")
      .attr("class", "axis-label")
      .attr("transform", "rotate(-90)")
      .attr("x", -(height / 2)) // Centering the label along the y-axis
      .attr("y", -140) // Adjust this value to move the label left or right
      .attr("text-anchor", "middle")
      .style("font-weight", "bold")
      .style("fill", isDark ? "#fff" : "#000")
      .text(yAxisLabel);
  }
  
  drawYAxis(g, y, tickPadding, lineHeight, yAxisLabelClass);

  var svgHeight = margin.top + margin.bottom + svg.select(".graph").node().getBoundingClientRect().height;
  svg.attr("height", svgHeight);

  return {
    svg: svg,
    data: data,
    x: x,
  };
}

/**
 * Add a grouped horizontal bar chart to the provided svg element.
 *
 * @param chartContainer - A d3 selection of the svg to add the chart to.
 * @param barData - One row per horizontal bar, each with attributes
 *   "label", "values".
 * @param legendData - One row per horizontal bar, each with attributes
 *   "label" and "class".
 *   E.g. For a two-bar chart comparing Quadro P5000 to CPU:
 *     [
 *       {"label": "Quadro P5000", "class": "green"},
 *       {"label": "CPU", "class": "green"}
 *     ]
 * @param ticks - The ticks to show on the x-axis, each with attributes
 *   "tickLabel", "value", and "class".
 *   E.g. For 3 ticks, with the middle tick hidden for mobile:
 *     [
 *       {"tickLabel": "0", "value": 0, "class": ""},
 *       {"tickLabel": "1X", "value": 1, "class": "mobile-hide"},
 *       {"tickLabel": "2X", "value": 2, "class": ""}
 *     ]
 * @param milestone - Optional, an object with a "color" and "value"
 *   for a milestone line in the chart. Set null for no milestone.
 * @param xAxisLabel - The label to show under the x axis.
 * @param isDark - true to enable styling for dark background, otherwise false.
 */
function createGroupedHorizontalBarChart(chartContainer, barData, barPadding, legendData, ticks, milestone, xAxisLabel, yAxisLabel, isDark) {
  var barAnimationDuration = 800;
  var animationDelay = 30;

  var chart = drawHorizontalGroupedBarChart(chartContainer, barData, barPadding, legendData, ticks, milestone, xAxisLabel, yAxisLabel, isDark);

  // If the chart should be immediately visible, begin animation.
  var rendered = false;
  if (chartContainer.node().getBoundingClientRect().top - window.innerHeight <= 0) {
    rendered = true;
    animate(chart, barAnimationDuration, animationDelay);
  }

  // Begin animation the first time the chart scrolls into view.
  window.addEventListener("scroll", function () {
    if (!rendered && chartContainer.node().getBoundingClientRect().top - window.innerHeight <= 0) {
      rendered = true;
      animate(chart, barAnimationDuration, animationDelay);
    }
  });

  // Redraw whenever the browser window is resized.
  var viewPortDimensionsHandler = function () {
    chartContainer.selectAll("*").remove();
    drawHorizontalGroupedBarChart(chartContainer, barData, barPadding, legendData, ticks, milestone, xAxisLabel, yAxisLabel, isDark);
  };

  window.addEventListener("resize", viewPortDimensionsHandler);
  window.addEventListener("orientationchange", viewPortDimensionsHandler);
}

function drawHorizontalGroupedBarChart(svg, barData, barPadding, legendData, ticks, milestone, xAxisLabel, yAxisLabel, isDark) {
  // Right margin leaves room for last tick label.
  var margin = {top: 0, right: 20, bottom: 0, left: 40};
  var barHeight = 10;
  var groupPadding = 10;
  var tickPadding = barPadding;
  var lineHeight = 1.1;
  var keys = legendData.map(function(l) { return l.label; });
  var legendDiv = svg.node().parentNode.querySelector('.legend');
  var legend = d3.select(legendDiv);

  var greenBegin = "#76b900";
  var greenEnd = "#c8e399";
  if (isDark) {
    greenEnd = "#3b5d00";
  }
  var greenScale = d3.interpolateLab(greenBegin, greenEnd);

  var numGreens = 0;
  for (var i in legendData) {
    if (legendData[i].class == "green") {
      numGreens++;
    }
  }

  // The graph's width is set to fit within its parent container.
  var svgWidth = svg.node().parentNode.getBoundingClientRect().width;
  svg.attr("width", svgWidth);

  if (isDark) {
    svg.attr("class", "dark");
    legend.attr("class", "legend dark");
  }
  else {
    legend.attr("class", "legend");
  }

  // The graph's height is a function of the number of bars.
  var height = (barHeight * legendData.length * barData.length
    + groupPadding * (barData.length + 1)
    + barPadding * (legendData.length - 1) * barData.length);

  var g = svg.append("g").attr("class", "graph");

  // Map groups to graph height.
  var y0 = d3.scaleBand().range([0, height]).padding(0.3);
  y0.domain(barData.map(function(d) { return d.label; }));

  // Map bars to group height.
  var y1 = d3.scaleBand().padding(0.2);
  y1.domain(keys).range([0, y0.bandwidth()]);

  // Draw the y axis to know how much space to leave for it,
  // then immediately delete it. Redrawing it last ensures
  // the correct ordering of layers for display.
  drawYAxis(g, y0, tickPadding, lineHeight, null);
  var yAxisWidth = svg.select(".y").node().getBoundingClientRect().width;
  svg.select("g.y.axis").remove();

  var width = svgWidth - margin.left - yAxisWidth - margin.right;
  g.attr("transform", "translate(" + (yAxisWidth + margin.left) + "," + margin.top + ")");

  var x = d3.scaleLinear().range([0, width]);
  x.domain([0, d3.max(ticks, function(d) { return d.value; })]);
  var xAxis = d3.axisBottom(x)
    .tickValues(ticks.map(function(tick) { return tick.value; }))
    .tickFormat(function(d, i) { return ticks[i].tickLabel; })
    .tickSizeInner([-height])
    .tickSizeOuter(0)
    .tickPadding(tickPadding);

  g.append("g")
    .attr("class", "x axis tick-label")
    .attr("transform", "translate(0," + height + ")")
    .call(xAxis);

  var z = d3.scaleOrdinal()
    .range(legendData.map(function(l) { return l.class; }))
    .domain(keys);

  // Add a label to the x axis.
  var xAxisHeight = svg.select(".x.axis.tick-label").node().getBoundingClientRect().height;

  // Add a label to the x axis.
  if (xAxisLabel) {
    g.append("text")
      .attr("x", width / 2)
      .attr("y", xAxisHeight + 5)
      .attr("class", "axis-label")
      .attr("alignment-baseline", "hanging")
      .text(xAxisLabel)
      .call(wrap, width, lineHeight);
  }

  g.append("g")
    .selectAll("g")
    .data(barData)
    .enter().append("g")
    .attr("transform", function(d) { return "translate(0," + y0(d.label) + ")"; })
    .selectAll("rect")
    .data(function(d) { return keys.map(function(key, i) { return {key: key, value: d.values[i]}; }); })
    .enter().append("rect")
    .attr("class", function(d) { return z(d.key) + " bar"; })
    .attr("y", function(d, i) { return y1(d.key) })
    .attr("x", function(d) { return 0; })
    .attr("height", barHeight)
    .attr("fill", function(d, i) {
      if (z(d.key) == "green") {
        return greenScale(i / numGreens);
      }
    })
    .attr("width", function(d) { return Math.abs(x(d.value)); });

  g.append("text")
  .attr("class", "axis-label")
  .attr("transform", "rotate(-90)")
  .attr("x", -height / 2)
  .attr("y", -140)
  .attr("text-anchor", "middle")
  .text(yAxisLabel);

  // Add milestone line.
  if (milestone) {
    // It appears D3 adds .5 to ticks to get crispEdges for Safari
    // (see https://github.com/d3/d3-axis/issues/8)
    var milestoneX = x(milestone.value) + .5;
    g.append("line")
      .attr("class", "milestone " + milestone.class)
      .attr("x1", milestoneX)
      .attr("x2", milestoneX)
      .attr("y1", 0)
      .attr("y2", height);
  }

  addLegend(legend, legendData, milestone, greenScale, numGreens);
  drawYAxis(g, y0, tickPadding, lineHeight, null);

  var svgHeight = margin.top + margin.bottom + svg.select(".graph").node().getBoundingClientRect().height;
  svg.attr("height", svgHeight);

  return {
    svg: svg,
    x: x,
  };
};
