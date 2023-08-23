import mqtt from'../../utils/mqtt.js';
const aliyunOpt = require('../../utils/aliyun/aliyun_connect.js');

let that = null;
Page({
    data:{    //声明数据 相当于全局定义

      //设置温度值和状态 
      temperature:"",
      state:"",
      sta1:0,
      sta2:0,
      
      sta1Prev: 0,
      sta2Prev: 0,
      sta1Prev_2: 0,
      sta2Prev_2: 0,
      time1:0,
      timer: null,
      time2: 0,
      timer2: null,

      a:"",
      b:"",
      c:"",
      mode:"",

      client:null,//记录重连的次数
      reconnectCounts:0,//MQTT连接的配置
      options:{
        protocolVersion: 4, //MQTT连接协议版本
        clean: false,
        reconnectPeriod: 1000, //1000毫秒，两次重新连接之间的间隔
        connectTimeout: 30 * 1000, //1000毫秒，两次重新连接之间的间隔
        resubscribe: true, //如果连接断开并重新连接，则会再次自动订阅已订阅的主题（默认true）
        clientId: '',
        password: '',
        username: '',
      },

      aliyunInfo: {
        // productKey: 'hr096uOcG77', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        // deviceName: 'connect_W', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        // deviceSecret: 'd34ee8aa513597022789107e65552fde', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        productKey: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        deviceName: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        deviceSecret: '', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        regionId: 'cn-shanghai', //阿里云连接的三元组 ，请自己替代为自己的产品信息!!
        pubTopic: '/hr096uOcG77/connect_W/user/topic', //发布消息的主题
        subTopic: '/hr096uOcG77/connect_W/user/topic', //订阅消息的主题
      },
    },

    onLoad:function(){
        this.data.a = wx.getStorageSync('a');
        console.log(this.data.a ); // 输出10
        this. data.b = wx.getStorageSync('b');
        console.log(this. data.b); // 输出10
        this.data.c = wx.getStorageSync('c');
        console.log(this.data.c); // 输出10

        setInterval(() => {
            // 当 t1 从 1 变成 0 时，开始计时
            if (this.data.sta1 === 0 && this.data.sta1Prev === 1) {
                
                this.startTimer();
            }
            // 当 t2 从 0 变成 1 时，停止计时
            if (this.data.sta2 === 1 && this.data.sta2Prev === 0) {
                this.stopTimer();
            }
            // 当 t2 从 1 变成 0 时，开始计时
            if (this.data.sta2 === 0 && this.data.sta2Prev === 1) {
                that.setData({
                    time2:0,
                  })
                this.startTimer2();
            }
            // 当 t1 从 0 变成 1 时，停止计时
            if (this.data.sta1 === 1 && this.data.sta1Prev === 0) {
              this.stopTimer2();
            }
            this.setData({
                sta1Prev: this.data.sta1,
                sta2Prev: this.data.sta2,
            });
          }, 1000);

        this.onconnect();
    },
    
   

    startTimer: function() {
        this.data.timer = setInterval(() => {
          this.setData({
            time1: this.data.time1 + 1,
          });
        }, 1000);
      },
    
      stopTimer: function() {
        that.setData({
            time1:0,
          })
        clearInterval(this.data.timer);
        this.data.timer = null;
      },
    
      startTimer2: function() {
        this.data.timer2 = setInterval(() => {
          this.setData({
            time2: this.data.time2 + 1,
          });
        }, 1000);
      },
    
      stopTimer2: function() {
        that.setData({
            time2:0,
          })
        clearInterval(this.data.timer2);
        this.data.timer2 = null;
      },

    inputCom1(e){
	    this.setData({
            a:e.detail.value
	    })
	    console.log(this.data.a);
    },
    inputCom2(e){
	    this.setData({
	        b: e.detail.value
	    })
	    console.log(this.data.b);
    },
    inputCom3(e){
	    this.setData({
	        c: e.detail.value
	    })
	    console.log(this.data.c);
    },
    inputCom4(e){
	    this.setData({
	        d: e.detail.value
	    })
	    console.log(this.data.d);
    },
    bandleChange(e){   // 1 获取单选框中的值
        this.setData({
            mode: e.detail.value
        })
        console.log(this.data.mode);
    },

    ontopic(){
        this.data.aliyunInfo.pubTopic=this.data.d;
        this.data.aliyunInfo.subTopic=this.data.d;
        this.topicconnect();
    },

   topicconnect(){   //订阅
       this.data.client.subscribe(this.data.aliyunInfo.subTopic,function(err){
      if(!err){
        console.log("订阅成功");
      };
      wx.showModal({
        content: "订阅成功",
        showCancel: false,
      })
    }) 
    },
    

    onconnect(){ 
        this.data.aliyunInfo.productKey= this.data.a;
        this.data.aliyunInfo.deviceName= this.data.b;
        this.data.aliyunInfo.deviceSecret= this.data.c;
        wx.setStorageSync('a', this.data.a);
        wx.setStorageSync('b', this.data.b);
        wx.setStorageSync('c', this.data.c);
        // console.log(this.data.aliyunInfo.productKey);
        // console.log(this.data.aliyunInfo.deviceName);
        // console.log(this.data.aliyunInfo.deviceSecret);
        this.loginAccount();
    },

    loginAccount(){  //监听下发数据
    that = this;
    let clientOpt = aliyunOpt.getAliyunIotMqttClient({
      productKey: that.data.aliyunInfo.productKey,
      deviceName: that.data.aliyunInfo.deviceName,
      deviceSecret: that.data.aliyunInfo.deviceSecret,
      regionId: that.data.aliyunInfo.regionId,
      port: that.data.aliyunInfo.port,
    });

    console.log("get data:" + JSON.stringify(clientOpt));
    let host = 'wxs://' + clientOpt.host;
    
    this.setData({
      'options.clientId': clientOpt.clientId,
      'options.password': clientOpt.password,
      'options.username': clientOpt.username,
    })
    console.log("this.data.options host:" + host);
    console.log("this.data.options data:" + JSON.stringify(this.data.options));

    //访问服务器
    this.data.client = mqtt.connect(host, this.data.options);

    this.data.client.on('connect', function (connack) {
      wx.showToast({
        title: '连接成功'
      })
      console.log("连接成功");
    })

    //接收消息监听   需要添加接受需要数据
    this.data.client.on("message", function (topic, payload) {
      console.log(" 收到 topic:" + topic + " , payload :" + payload);
      that.setData({
        //转换成JSON格式的数据进行读取   
        temperature:JSON.parse(payload).temperature,
        state:JSON.parse(payload).state,
        sta1:JSON.parse(payload).sta1,
        sta2:JSON.parse(payload).sta2,
        // time1:JSON.parse(payload).time1,
        // time2:JSON.parse(payload).time2,
      })
     /* wx.showModal({
        content: " 收到topic:[" + topic + "], payload :[" + payload + "]",
        showCancel: false,
      }); */
    }) 

    //服务器连接异常的回调
    that.data.client.on("error", function (error) {
      console.log(" 服务器 error 的回调" + error)

    })
    //服务器重连连接异常的回调
    that.data.client.on("reconnect", function () {
      console.log(" 服务器 reconnect的回调")

    })
    //服务器连接异常的回调
    that.data.client.on("offline", function (errr) {
      console.log(" 服务器offline的回调")
    })
  },
  
  ontempopen() {   //监听按钮数据
    console.log(this.data.sta1);
    if(this.data.sta1==1){
        that.setData({
            sta1:0,
          })
    that.sendCommond("tempopen", 1);
    }
  },
  onworkopen() {
    
    if(this.data.sta2==1){
        that.setData({
            sta2:0,
          })
    that.sendCommond("workopen", 1);
    }
  },
  onClicktemp() {
      if(this.data.mode==1){
        that.sendCommond("tempmin", 32);
        that.sendCommond("tempmax", 34);
      }else if(this.data.mode==2){
        that.sendCommond("tempmin", 34);
        that.sendCommond("tempmax", 36);
      }else if(this.data.mode==3){
        that.sendCommond("tempmin", 36);
        that.sendCommond("tempmax", 38);
      }
  },
  sendCommond(cmd, datad) {
    let sendData = {
      cmd: cmd,
      datad: datad,
      connect: "connect_A"
    }
    wx.showToast({
        title: '发送成功'
      });
    

//    this.data.client.subscribe(this.data.aliyunInfo.subTopic,function(err){
//       if(!err){
//         console.log("订阅成功");
//       };
//       wx.showModal({
//         content: "订阅成功",
//         showCancel: false,
//       })
//     })  
    

    //发布消息
    if (this.data.client && this.data.client.connected) {
      this.data.client.publish(this.data.aliyunInfo.pubTopic, JSON.stringify(sendData));
    //   console.log("************************")
      console.log(this.data.aliyunInfo.pubTopic)
      console.log(JSON.stringify(sendData))
    } else {
      wx.showToast({
        title: '请先连接服务器',
        icon: 'none',
        duration: 2000
      })
    }
  }
})