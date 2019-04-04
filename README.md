# shelfOpenerArduino
A small code base to control my stepper motor and surrounding electronics.

I have a projector integrated into a shelf. I am using a stepper motor to open the shelf.
Arduino is lissening for the 'On/Off' signal for the projector IR contorller, and opens/closes the shelf.

An example schematics is provided bellow. Note that I've used circuito.io to draw it but the pin setup is slightly different in my code.
<p>
<img src="https://github.com/mumas/shelfOpenerArduino/blob/master/schematics.png" align="left" height="400" width="400"/>
</p>

I used these components from amazon:
1. [IR repeater](https://www.amazon.com/gp/product/B07CWFDQGY/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
2. [Stepper motor](https://www.amazon.com/gp/product/B00PNEQKC0/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1)
3. [Actuator from 3d printer](https://www.amazon.com/gp/product/B0796RZZRL/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1) to do the real opening.
