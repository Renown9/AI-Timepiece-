var myCharts = require("../../../utils/wxcharts.js")//引入一个绘图的插件
var lineChart_pn = null
var app = getApp()

Page({
  data: {
  },
  onPullDownRefresh: function () {
    console.log('onPullDownRefresh', new Date())
  },
  onLoad1: function (option) {
    console.log(option.query)
    wx.redirectTo({
      url: '/pages/start/start'
    })
  },

  //把拿到的数据转换成绘图插件需要的输入格式
  convert: function () {
    var categories = [];
    var pnumber = [];

    var length = app.globalData.pnumber.datapoints.length
    for (var i = 0; i < length; i++) {
      categories.push(app.globalData.pnumber.datapoints[i].at.slice(11, 19));
      pnumber.push(app.globalData.pnumber.datapoints[i].value);
    }
    return {
      categories: categories,
      pnumber: pnumber
    }
  },

 

  onLoad: function () {
    var wheatherData = this.convert();

    //得到屏幕宽度
    var windowWidth = 320;
    try {
      var res = wx.getSystemInfoSync();
      windowWidth = res.windowWidth;
    } catch (e) {
      console.error('getSystemInfoSync failed!');
    }

    var wheatherData = this.convert();

    //新建图表
    lineChart_pn = new myCharts({
      canvasId: 'pnumber',
      type: 'column',
      categories: wheatherData.categories,
      animation: true,
      background: '#f5f5f5',
      series: [{
        name: '访问人数',
        data: wheatherData.pnumber,
        format: function (val, name) {
          return val.toFixed(2);
        }
      }],
      xAxis: {
        disableGrid: true
      },
      yAxis: {
        title: '人数（人）',
        format: function (val) {
          return val.toFixed(2);
        },
        min: 0
      },
      width: windowWidth,
      height: 300,
      dataLabel: false,
      dataPointShape: true,
      extra: {
        lineStyle: 'curve'
      }
    });
  },


})