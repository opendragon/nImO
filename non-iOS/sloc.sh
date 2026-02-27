#!/bin/sh

echo ---------------
echo Main code
echo ---------------
sloccount ../examples ../GUI ../Launcher ../nImO ../ProgrammableServices ../Registry ../Signals ../Tests ../Tools ../Wiring
echo ---------------
echo Subtract the following -
echo ---------------
sloccount ../nImO/swig_nImO_in ../nImO/swig_nImO_out_python
echo ---------------
echo Tests
echo ---------------
sloccount ../Tests
