echo -e "-------------\nLABORATORIO 0\n-------------"

echo -e "\nEjercicio 1)"
cat /proc/cpuinfo | grep "model name"

echo -e "\nEjercicio 2)"
cat /proc/cpuinfo | grep "model name" | wc -l

echo -e "\nEjercicio 3)"
wget https://www.gutenberg.org/files/11/11-0.txt && sed -i 's/Alice/Camilo/g' 11-0.txt && mv 11-0.txt Camilo_in_wonderland.txt

echo -e "\nEjercicio 4)"
cat archivos\ de\ datos/weather_cordoba.in | sort -k 5 -n | tail -n 1 | awk '{print "Date Top Max Temp: " $3"/"$2"/"$1}'
cat archivos\ de\ datos/weather_cordoba.in | sort -k 5 -n | head -n 1 | awk '{print "Date Lower Max Temp: " $3"/"$2"/"$1}'

echo -e "\nEjercicio 5)"
cat archivos\ de\ datos/atpplayers.in | sort -k 3 -n

echo -e "\nEjercicio 6)"
cat archivos\ de\ datos/superliga.in | awk '{print $0, $7-$8}' | sort -k 2 -k 9 -n

echo -e "\nEjercicio 7)"
ip l | grep -i "ether" | awk '{print $1" "$2}'

echo -e "\nEjercicio 8a)"
mkdir Naruto && cd Naruto && touch ¡Entra\!_¡Naruto_Uzumaki\!_S01E01_es.srt ¡Soy_Konohamaru\!_S01E02_es.srt ¡Enemigos_declarados\!_Sasuke_y_Sakura_S01E03_es.srt ¡Pruebas\!_Ejercicio_de_supervivencia_S01E04_es.srt ¿Reprobamos\?_La_conclusión_de_Kakashi_S01E05_es.srt ¡Misión_importante\!_¡Súper_salida_a_la_Tierra_de_las_Olas\!_S01E06_es.srt ¡El_asesino_de_la_niebla\!_S01E07_es.srt Un_compromiso_con_el_dolor_S01E08_es.srt Kakashi,_el_del_Sharingan_S01E09_es.srt El_bosque_de_chakra_S01E10_es.srt && ls

echo -e "\nEjercicio 8b)"
for i in *_es.srt; do mv "$i" "${i%_es.srt}.srt"; done && ls && cd ..

echo -e "\n[OPCIONAL] 1a)"
ffmpeg -i Video\ de\ prueba\ \(original\).mkv  -ss 00:00 -to 00:35 -y "Video de prueba (recortado).mkv"

echo -e "\n[OPCIONAL] 1b)"
ffmpeg -i Audio\ de\ prueba\ \(original\).mp3  -i y2mate.com\ -\ Strike\ the\ Earth\ Plains\ of\ Passage\ Shovel\ Knight\ OST.mp3 -filter_complex amerge -y "Audio de prueba (pista de sonido incluida).mp3"

