/*
 * data.js
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

function Data() {
    this.data = {};
    this.inited = false;
    this.getInterval = setInterval(this.getDataFromRemote.bind(this), 5000);
    this.total = {};
    this.protocols = {};
    this.p_index = [];
    this.maxHistory = 30;
    this.subscribeCbk = [];
}
// prototype: share the same memory between Objs
Data.prototype = {
    constructor: Data,
    init: function () {
        this.inited = true;
    },
    // get the realtime data from back end
    getDataFromRemote: function () {
        var thisSec = $.ajax('/cgi/get_data', {
            type: 'GET',
            success: (res) => {
                var jsData = JSON.parse(res);
                for (var k in jsData) {
                    if ("protocols" === k) {
                        // records for protocols
                        var self = this;
                        var processed = [];
                        jsData[k].forEach(function (protocol) {
                            // each obj is a dictionary
                            var name = protocol.name;
                            if (undefined === self.protocols[name]) {
                                self.protocols[name] = {};
                                self.p_index.push(name);
                            }
                            var pro_data = self.protocols[name];
                            for (key in protocol) {
                                if ('name' === key) continue;
                                if (undefined === pro_data[key]) pro_data[key] = new Array(self.maxHistory);
                                pro_data[key].shift();
                                pro_data[key].push(protocol[key]);
                            }
                            processed[name] = 1;
                        })
                        for (proto_name in self.protocols) {
                            if (processed[proto_name]) continue;
                            var pro_data = self.protocols[proto_name];
                            for (key in pro_data) {
                                pro_data[key].shift();
                                pro_data[key].push(null);
                            }
                        }
                    }
                    else if ("total" === k) {
                        // records for total
                        for (var key in jsData[k]) {
                            // jsData['total'] is a dictionary
                            this.total[key] = jsData[k][key]
                        }
                    }
                    else {
                        // records for realtime data
                        if (undefined === this.data[k]) this.data[k] = new Array(this.maxHistory);
                        this.data[k].shift();
                        this.data[k].push(jsData[k]);
                    }
                }
                self.newDataInform();
            }
        })
    },
    getDataAttr: function (key) {
        if (undefined === this.data[key]) this.data[key] = new Array(this.maxHistory);
        return this.data[key].filter((v) => { return v });
    },
    getDataAttrWithNull: function (key) {
        if (undefined === this.data[key]) this.data[key] = new Array(this.maxHistory);
        return this.data[key];
    },
    getProtocalAttrWithNull: function (p, k) {
        return this.protocols[p][k];
    },
    newDataInform: function () {
        this.subscribeCbk.forEach((v) => v());
    }
}
