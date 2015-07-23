#!/bin/bash
mkdir cur_release
cp Release/wxCrossGen.out cur_release/CrossGen
cp Release/big_cross_ru.txt cur_release/big_cross_ru.txt
cp Release/big_cross_eng.txt cur_release/big_cross_eng.txt
cd Translations
cp -r * ../cur_release