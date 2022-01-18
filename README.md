<h1 align="center"> desklab Arduino Library </h1>
<p align="center">
<img align="center" src="https://www.ardu-badge.com/badge/desklab.svg?">
<br>
<a href="./README_DE.md">zur deutschen Version dieser Datei</a>
</p>

`desklab` is an Arduino library implementing methods for the use of desklab (www.desk-lab.de) devices. It is availabe via the Arduino Library Manager and easy to use with the Arduino IDE. Originally designed to be used with desklab devices and their specific hardware it could also be used in any other preferred toolchain to build software for many boards based on Atmel-AVR-Microcontrollers.

#### Hardware Compatibility
  - `desklab Photometer V2`
  - `desklab Photometer V3`

### Development & Contribution
Contributions in the form of reporting issues or submitting pull requests are welcome! Please use the available tools as described here to ensure your changes of the code could be merged. As this library addresses a special group of users (students/teachers) and must retain compatibility to the devices developed by desklab (some of which may not be public yet), there may be some additional requirements, which can not be covered by automated tests. Therefore you should not hesitate to contact us via <orga@desk-lab.de> or by opening an issue, if you are planning to contribute to this project, such that we could discuss the best way to go forward. Submitted code changes are understood to be under the same MIT License that covers the project. 

##### Arduino Lint
Install `arduino-lint` by following the instructions in the [official arduino-lint documentation](https://arduino.github.io/arduino-lint/latest/installation/). Please use the linter with the same options as our CI workflow:

```bash
# Launch linting 
arduino-lint --library-manager update --compliance strict
```

##### Unit-Tests & compilation of examples
A set of unit-tests is located in the `/test`-folder. If you are adding some logic to the library which could be unit-tested, make sure to cover this with some additional tests. To be able to launch the tests locally you have to install the `arduino-ci` ruby gem by:

```bash
# Install test requirements: 
gem install bundler
bundler config set --local path vendor/bundle  # optional
bundler install
```

While we are using the `arduino/compile-sketches`-action in our CI workflow, you could also start the compilation of all examples with the same command as launching the tests. If you only want to run the tests, you can add the option `--skip-examples-compilation`:

```bash
# Run the tests and compile examples
bundle exec arduino_ci.rb

# Run the tests 
bundle exec arduino_ci.rb --skip-examples-compilation
```

#### Docs

**MkDocs** is used to build the documentation. You can install it inside a new `conda` environment with:

```bash
conda create -n desklab-arduino lib python=3.9
pip install -r requirements.txt
```

To build the docs execute the following commands:

```bash
conda activate desklab-arduino-lib
mkdocs build
```

The docs are served through GitHub Pages at [support.desk-lab.de/desklab-arduino-lib](https://support.desk-lab.de/desklab-arduino-lib/build/html/index.html).

### License

The `desklab` library is licensed under the [MIT License](https://opensource.org/licenses/MIT):

> Copyright 2018-2022 desklab gUG (haftungsbeschränkt) <orga@desk-lab.de>  
>
> Permission is hereby granted, free of charge, to any person obtaining a  
> copy of this software and associated documentation files  
> (the "Software"), to deal in the Software without restriction, including  
> without limitation the rights to use, copy, modify, merge, publish,  
> distribute, sublicense, and/or sell copies of the Software, and to  
> permit persons to whom the Software is furnished to do so, subject to  
> the following conditions:  
> 
> The above copyright notice and this permission notice shall be included  
> in all copies or substantial portions of the Software.  
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,  
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF  
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  
> IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR  
> ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  
> CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION  
> WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE  
