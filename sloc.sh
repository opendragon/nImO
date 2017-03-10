#!/bin/sh

sloccount Connect Disconnect Info List Monitor Read Tests Version Write nImO odl
echo ---------------
echo subtract the following -
echo ---------------
sloccount nImO/swig_nImO_in nImO/swig_nImO_out_csharp nImO/swig_nImO_out_python odl/swig_odl_in odl/swig_odl_out_csharp odl/swig_odl_out_python
echo ---------------
echo Test only -
echo ---------------
sloccount Tests
