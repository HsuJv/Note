/*
 * myChart.js
 * Copyright (C) 2019-2019 by jovi Hsu(jv.hsu@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

function toF_E(num) {
    var exp = 0;
    if (isNaN(num)) return null;
    else num = parseInt(num);
    if (1 <= num && 10 > num) return num;
    if (0 == num) return num;
    var isNag = num < 0;
    if (isNag) num = -num;
    while (num >= 10) {
        num /= 10;
        exp += 1;
    }
    while (num < 1) {
        num *= 10;
        exp += 1;
    }
    var base = (isNag ? "-" : "") + String(num);

    return base.slice(0, 3) + 'e' + exp;
}

function MyChart(ctx, config) {
    this.inited = false;
    this.ctx = ctx;
    this.chart = new Chart(ctx, config);
    // used for details
    this.origin_datasets = [];
    this.origin_args = $.extend(true, {}, config.data.datasets[0]);
    this.origin_config = $.extend(true, {}, config);
}
MyChart.prototype = {
    constructor: MyChart,
    init: function () {
        this.inited = true;
    },
    getChartAttr: function (key) {
        return this.chart[key];
    },
    setChartAttr: function (key, value) {
        this.chart[key] = value;
    },
    newDataSet: function (index, value, name) {
        // initial a dataset
        var config = $.extend(true, {}, this.origin_args);
        config.backgroundColor = config.backgroundColor[index % config.backgroundColor.length];
        config.borderColor = config.borderColor[index % config.borderColor.length];
        config.label = name;
        config.data = value;
        return config;
    },
    rmDataSet: function (index) {
        this.chart.config.data.datasets.splice(index, 1);
    },
    setDataSet: function (index, value, name) {
        // if (index > 1) return;
        var Ds = this.chart.config.data;
        if (null == Ds.datasets[index]) {
            this.origin_datasets[index] = this.newDataSet(index, value, name);
            if (index === Ds.datasets.length) {
                var cur_config = $.extend(true, {}, this.origin_config);
                cur_config.data.datasets = $.extend(true, [], this.origin_datasets);
                this.chart.destroy();
                this.chart = new Chart(this.ctx, cur_config);
            }
        }
        else Ds.datasets[index].data = value;
    },
    update: function (value) {
        this.chart.update();
        this.showValue.apply(this.chart);
    },
    showValue: function () {
        var chartInstance = this.chart,
            ctx = chartInstance.ctx;
        ctx.textAlign = 'center';
        ctx.textBaseline = 'bottom';
        this.data.datasets.forEach(function (dataset, i) {
            var meta = chartInstance.controller.getDatasetMeta(i);
            meta.data.forEach(function (bar, index) {
                var data = dataset.data[index];
                ctx.fillText(toF_E(data), bar._model.x, bar._model.y - 5);
            });
        });

    }
}