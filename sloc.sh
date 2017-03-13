#!/bin/sh

sloccount Connect Disconnect Info List Monitor Read Tests Version Write nImO
echo ---------------
echo subtract the following -
echo ---------------
sloccount nImO/swig_nImO_in nImO/swig_nImO_out_csharp nImO/swig_nImO_out_python odl/swig_odl_in
echo ---------------
echo Test only -
echo ---------------
sloccount Tests
