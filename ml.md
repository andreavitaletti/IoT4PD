#Very basic statistics and machine learning 

Statistics and machine learning, can be quite complex topics. However, we largely discussed the importance of stats and machine learning in IoT, and in this section we will do some very basic experiments to show the concept. 

We will use the js library [Simple Statistics](http://simplestatistics.org/). Unfortunately, that library has not been implemented in a suitable node. Thus we have 1) to install the library as detailed [here](node_red.md), 2) use such library as described in the following:

![Smart Object](/assets/stats.png  "Basic Node Red Flow")

We have basically 3 flow:

## Generating data

Each time the generate data button (is an inject node) is pushed, it triggers the function test, that contains the follwoing code

```js
var count = context.get('count') || 0;
count += 1;
context.set('count',count);

msg.payload=[count,count+3];

return msg;
```

The output of such function is something like [1,4],[2,5],..,[n,n+3]

Such data are stored in a file named data.txt

## Clear data

This is used to erase the data file

## Compute stats

the content of the file data.txt is read and provided as input to the function 

```js
var ST = context.global.get('st');
//msg.payload = ST.linearRegression([[0, 0], [1, 1]]); // => { m: 1, b: 0 }

var vec = msg.payload.split("\n");
//var vec = ["[0, 1]", "[1, 2]", "[2, 4]"]

var data = [];
for (var i = 0; i < vec.length-1; i++) {
    var array_elem = JSON.parse(vec[i]);
    data.push(array_elem);
}

console.log(data);

msg.payload=ST.linearRegression(data);
return msg;
```
