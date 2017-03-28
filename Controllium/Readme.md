# Controllium


[![N|Solid](http://asgardlab.netne.net/play_github.png)](https://play.google.com/store/apps/details?id=com.daedalusstone.sigma.controllium)   [![N|Solid](http://asgardlab.netne.net/github_instagram_icon.png)](https://www.instagram.com/artur31415926/)



##### DEVELOPED BY | Artur Ferreira Moreira
##### DATE:           MARCH, 28 OF 2017
##### EMAIL:          artur31415926@gmail.com
##### WEBPAGE:        asgardlab.netne.net/

## v1.0:
### [ENG-USA]
This library was developed to work with the Android app "Controllium", with wich,
you can control your ESP8266 projects using your Android device.

Through the library you can attach any of the ui elements to the arduino hardware pins
acordingly to theirs funcionalities.

Look at the examples to understand how the library works.

Any Ideas or criticism, email me.

Have fun!

### [PT-BR]
Esta biblioteca foi desenvolvida para trabalhar com o aplicativo Android "Controllium", com o qual,
Você pode controlar seus projetos de ESP8266 usando seu dispositivo Android.

Através da biblioteca você pode anexar qualquer um dos elementos ui para os pinos de hardware arduino
De acordo com suas funcionalidades.

Veja os exemplos para entender como funciona a biblioteca.

Quaisquer idéias ou críticas, e-mail me.

Divirta-se!
        
        
# How It Works?

First you have to instantiate an `Controllium` object by passing the name of the device (ii should be unique)
  
```java
    Controllium controllium("DEVICE_NAME");
```

After you connected to a wifi or initialized a AP, you begin the udp server

```java
	controllium.BeginUdpServer(UDP_DEFAULT_PORT);
```

Then within the `setup`() function you add a device to the controllium object

```java
    ControlliumDevice gpio0("Gpio 0", DEVICE_TYPE_BUTTON, "0");//DEVICE_NAME, TYPE, INITIAL_VALUE 
    controllium.AddDevice(gpio0);
```

In the `loop`() you need to call the update function.
It returns a Boolean, wich is true if new data was received.

```java
	controllium.Update(200);
```


To get the value of a device, you can call `GetDevice` and pass the device name that you used to create earlier

```java
   controllium.GetDevice("Gpio 0")->GetDoubleValue();
```

To set the value of a device, you can call `GetDevice` and pass the device name that you used to create earlier as well

```java
   controllium.GetDevice("LED_1")->SetValue(1);
```

Please take a loop at the examples, and have fun! :D 


[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
