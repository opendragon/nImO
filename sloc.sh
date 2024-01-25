#!/bin/sh

echo ---------------
echo Main code
echo ---------------
sloccount examples Launcher nImO Registry Tests Tools Wiring
echo ---------------
echo Subtract the following -
echo ---------------
sloccount nImO/swig_nImO_in nImO/swig_nImO_out_csharp nImO/swig_nImO_out_python
echo ---------------
echo Tests
echo ---------------
sloccount Tests
