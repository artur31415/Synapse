# AndroidShield


[![N|Solid](https://lh6.googleusercontent.com/nghcDz1dVVIfXUAfhIW66x-EGfSA8o5MXUvq0ZCX0XEW6KiOtNM-B_n3rp9f7jgr2gQ8bsyZaOfDEmk=w1366-h678)](https://play.google.com/store/apps/details?id=com.blackbode.sigma.bluetoothshieldsimpleio)   [![N|Solid](https://lh4.googleusercontent.com/W-Le1cqMnig1JuaAnGIZS1Tyzq7WZq7Nj2YnvEYch2e8S8FR7q3nWAFz-l1QpkOs2VRfqaIp-mQpM10=w1366-h678)](https://www.instagram.com/artur31415926/)



##### DEVELOPED BY | Artur Ferreira Moreira
##### DATE:           APRIL, 18 OF 2016
##### EMAIL:          artur31415926@gmail.com
##### WEBPAGE:        asgardlab.netne.net/

## v1.0:
### [ENG-USA]
This library was developed to work with the android app "Bluetooth Shield Arduino".
The app features.

  - lcd screen
  - 5 buttons
  - 5 leds
  - 2 scrollbars
  - 2 progressbars

Through the library you can attach any of the ui elements to the arduino hardware pins acordingly to theirs funcionalities.
Look at the examples to understand how the library works.

### [PT-BR]
Essa biblioteca foi desenvolvida para funcionar com o aplicativo android "Bluetooth Shield Arduino".
O app possui.
  - tela lcd
  - 5 botões
  - 5 leds
  - 2 crollbars 
  - 2 progressbars
  

Atraves da biblioteca você pode linkar qualquer elementdo da interface do app aos pinos do hardware do arduino de acordo com as suas funcionalidades.
Olhe os exemplos para entender como a bilioteca funciona.
        
        
# How It Works?

First you have to instantiate an `AndroidShield` object by passing the pins for the virtual serial used within the library
  
```java
    AndroidShield shield(10, 11); //RX_PIN, TX_PIN
```

Then within the `loop`() function you add

```java
    shield.updateLoop(200); //ms 
```

This is the main update loop of the library.


To access the buttons send from the App, you use

```java
   shield.buttonRead(index);
```

Which can be put directly to a pin

```java
   digitalWrite(pin, shield.buttonRead(index));
```


You can attach a button from the App to a digital pin on Arduino. On the `setup`() function, you do

```java
   shield.buttonAttach(buttonIndex, ArduinoPin);
```

You can as well attach a scrollbar on the App to a pwm on Arduino, so that when the scrollbar value changes, it change the pwm. You can do it by

```java
   shield.scrollbarAttach(scrollbarIndex, ArduinoPin);
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
