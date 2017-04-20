# Web of Things (WoT)

The Web of Things (WoT) is a term used to describe approaches, software architectural styles and programming patterns that allow real-world objects to be part of the World Wide Web. For the sake of simplicity, we will assume that each thing can be accessed via [HTTP](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) at a specific [URL](https://en.wikipedia.org/wiki/URL). 

![](/assets/web_of_things1.jpg) 

In this example there are three things: red, green and blu. Each thing, according to the WoT,  can be accessed via HTTP to a specific URL: http://the_red_thing, http://the_green_thing and http://the_blu_thing. 

Each thing offers some resources (i.e. sensors and/or actuators). Also such resources can be accessed via a specific URL as detailed  in the figure.

Possibly, an HTTP server (http://the_server), interacts with the things, in order to provide more complex services to the end-users. As an example ``if the square in the_red_thing is made of four edges, then colour the triangle in the_green_thing``. 

In order to simulate such complex environment, we will use [node-red](https://nodered.org/) as shown in the following picture

![](/assets/node-red-ex1.png) 

In this example the [simulated thing](/code/simulated_thing.nrd) tab in node-red, simulates the simulated_thing. In this tab, there are two flows, one for the temperature sensor, named temperature1, and one for the switch actuator, named switch1.

The access to the sensor/actuator is via HTTP GET method. In particular, given that the addree of the node-red server is http://192.168.56.100:1880

* HTTP GET on the URL http://192.168.56.100:1880/temperature1 reads the temperature on temperature1 sensor
* HTTP GET on the URL http://192.168.56.100:1880/switch1?value=ON switches on the switch1 actuator
* HTTP GET on the URL http://192.168.56.100:1880/switch1?value=OFF switches off the switch1 actuator

The code in temperature1 simply returna a random value between 0 and 60 

```js
msg.payload=60*Math.random();
return msg;
```

The code in switch1 is slightly more complex because it has to handle GET parameters. 

```js
if (msg.req.query.value=="ON")
    {
        msg.payload = " I switch on the switch";
        return msg;
    }
if (msg.req.query.value=="OFF")
    {
        msg.payload = " I switch off the switch";
        
    }
else
    {
        msg.payload = "I do not know this command";
    }
return msg;
```

Finally assume that the server, implemented in the [simulated server](/code/simulated_server.nrd) tab in node-red has to read the temperature value from the simulated thing and switch on/off the switch1 according to a given threshold on temperature1.

When accessed at http://192.168.56.100:1880/service1 the server connects to the temperature1 sensor an get the temperature. 

The switch node make the decision on the basis of the value of the msg.payload that delivers the current value of the temperature. If the msg.payload < 30 then a msg.payload exits from branch 1 otherwise from branch 2.

![](/assets/switch.png) 

Now from branch1 (temp < 30) we switch on the switch1 using the GET method implemented before, namely  HTTP GET on the URL http://192.168.56.100:1880/switch1?value=ON otherwise in branch2 we switch it off with  HTTP GET on the URL http://192.168.56.100:1880/switch1?value=OFF

#Exercise

![](/assets/exercise2.png) 
