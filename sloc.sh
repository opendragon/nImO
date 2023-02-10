#!/bin/sh

echo ---------------
echo Main code
echo ---------------
sloccount examples Launcher nImO Registry Tests Tools
echo ---------------
echo Subtract the following -
echo ---------------
sloccount nImO/swig_nImO_in nImO/swig_nImO_out_csharp nImO/swig_nImO_out_python odl/swig_odl_in
echo ---------------
echo Tests
echo ---------------
sloccount Tests
