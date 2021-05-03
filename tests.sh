#!/bin/bash

echo "Checking file abc.txt"
expec="DDAF35A193617ABACC417349AE20413112E6FA4E89A97EA20A9EEEE64B55D39A2192992A274FC1A836BA3C23A3FEEBBD454D4423643CE80E2A9AC94FA54CA49F"
output="$(./sha512 abc.txt)"
echo "Expected: " $expec
echo "Output: " $output
if [[ $output == $expec ]]; then 
    echo " Pass ✓"
else
    echo "Fail X"
fi

echo "Checking file empty.txt"
expec="CF83E1357EEFB8BDF1542850D66D8007D620E4050B5715DC83F4A921D36CE9CE47D0D13C5D85F2B0FF8318D2877EEC2F63B931BD47417A81A538327AF927DA3E"
output="$(./sha512 empty.txt)"
echo "Expected: " $expec
echo "Output: " $output
if [[ $output == $expec ]]; then 
    echo " Pass ✓"
else
    echo "Fail X"
fi 

echo "Checking file G_Number.txt"
expec="643798D56FF14D86E60916AF2D759043272D3BC49269FCCAB28AECCFB6DE483D2A6E3F1A0CC4615662E461EB6475A603CBA42041160D294BB48CF7BAF0A3DEFF"
output="$(./sha512 G_Number.txt)"
echo "Expected: " $expec
echo "Output: " $output
if [[ $output == $expec ]]; then 
    echo " Pass ✓"
else
    echo "Fail X"
fi 

echo "Checking file Hamlet.txt"
expec="D0761176B29D7E0231F5E4FC8BB1AEE46E7B7574E3A6E49B3BA6C42D689183474FD97C7697DC77F45331C9B590FF28F45D9421BF443EFCEFC10E39DE0B24CD35"
output="$(./sha512 Hamlet.txt)"
echo "Expected: " $expec
echo "Output: " $output
if [[ $output == $expec ]]; then 
    echo " Pass ✓"
else
    echo "Fail X"
fi 
