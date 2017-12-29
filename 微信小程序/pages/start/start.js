// start.js
var app = getApp()
Page({

  /**
   * 页面的初始数据
   */
  data: {

    at: '\n' + '\n' + '\n',
    value: '\n' + '\n',
    Array:[{at:"",value: "",}],
    opacity: 0.4,
    disabled: true,
    threshold: 0,
    rule: 'up',
    object:{
      at: "",
      value: ""
    },

    items: [
      { name: 'up', value: '高于此温度将报警', checked: 'ture' },
      { name: 'down', value: '低于此温度将报警' },
    ]

  },


  getDataFromOneNet: function () {

    //从oneNET请求我们的Wi-Fi气象站的数据
    const requestTask = wx.request({
      url: 'https://api.heclouds.com/devices/20457297/datapoints?datastream_id=Number&limit=10',
      header: {
        'content-type': 'application/json',
        'api-key': 'NBUrYowJXKKzHjyI=HzUKWnv5BU='
      },
      success: function (res) {
        //console.log(res.data)
        //拿到数据后保存到全局数据
        app.globalData.pnumber = res.data.data.datastreams[0]
        console.log(app.globalData.pnumber)
        //跳转到天气页面，根据拿到的数据绘图
        wx.navigateTo({
          url: '../wifi_station/tianqi/tianqi',
        })

      },

      fail: function (res) {
        console.log("fail!!!")
      },

      complete: function (res) {
        console.log("end")
      }
    })
  },
  RequestData: function () {
    var that = this;
    const requestTask = wx.request({
      url: 'https://api.heclouds.com/devices/20457297/datapoints?datastream_id=Number&limit=1',
      header: {
        'content-type': 'application/json',
        'api-key': 'NBUrYowJXKKzHjyI=HzUKWnv5BU='
      },
      success: function (res) {
        app.globalData.pnumber = res.data.data.datastreams[0]
        console.log(app.globalData.pnumber)
        that.setData({ at:  '\n'+app.globalData.pnumber.datapoints[0].at + '\n'});
        that.setData({ value: '\n' + app.globalData.pnumber.datapoints[0].value +'\n'});
        //console.log(res.data.data.datastreams[0]);
        wx.setNavigationBarColor({
          frontColor: '#ffffff',
          backgroundColor: '#FFC125',
          animation: {
            duration: 400,
            timingFunc: 'easeIn'
          }
        })
      },
      fail: function () {
        // fail
      },
      complete: function () {
        // complete
      }
    })
  },
 
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})