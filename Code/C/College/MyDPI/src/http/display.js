/*
 * display.js
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

function Display(chart, data, details) {
    this.chart = chart;
    this.data = data;
    this.details = details;
}

Display.prototype = {
    constructor: Display,
    start: function () {
        if (!this.chart.inited) {
            console.error("Chart doesn't init");
            return;
        }
        if (!this.data.inited) {
            console.error("Dataset doesn't init");
            return;
        }
        if (this.details) {
            this.p_index = this.data.p_index;
            this.p_num = this.p_index.length;
            this.chart.rmDataSet(0);
        }
    },
    show: function () {
        if (this.details) ;
        else {
            this.chart.setDataSet(0, this.data.getDataAttrWithNull('ip bytes'));
        }
        this.data.subscribeCbk.push(() => { this.update() });

    },
    update: function () {
        if (!this.details) {
            this.chart.update();
        }
        else {
            if (1 || this.p_index.length !== this.p_num) {
                // need to update
                for (var i = 0; i < this.p_index.length; i++) {
                    this.chart.setDataSet(i, this.data.getProtocalAttrWithNull(this.p_index[i], 'packets'), this.p_index[i]);
                }
                this.p_num = this.p_index.length;
            }
            this.chart.update();
        }
    }
}