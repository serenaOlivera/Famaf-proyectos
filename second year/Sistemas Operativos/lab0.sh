
#Ejercicio 1
grep model /proc/cpuinfo | head -2

#Ejercicio 2
grep processor /proc/cpuinfo | wc -l


#Ejercicio 3
wget -O - https://raw.githubusercontent.com/dariomalchiodi/superhero-datascience/master/content/data/heroes.csv | awk -F ';' '{print $2}' | tr -d '' | tr '[:upper:]' '[:lower:]' | sed '/^$/d'

#Ejercicio 4
{ awk '{print $1, $2, $3, $5}' weather_cordoba.in | sort -k4,4nr | head -n 1 | awk '{print "Maxima: " $1"-"$2"-"$3}'; awk '{print $1, $2, $3, $6}' weather_cordoba.in | sort -k4,4n | head -n 1 | awk '{print "Minima: " $1"-"$2"-"$3}'; }

#Ejercicio 5
awk '{print $1, $2, $3, $4, $5, $6}' atpplayers.in | sort -k3,3n

#Ejercicio 6
awk '{diff=$7 - $8; print $0, diff}' superliga.in | sort -k2,2nr -k9,9nr

#Ejercicio 7
ip link | grep ether

#Ejercicio 8
#Inciso a
 mkdir serie && cd serie && for i in {1..10}; do touch fma_S01E$(printf "%02d" $i)_es.srt; done

 #Inciso b
for episode in *_es.srt; do mv "$episode" "${episode/_es/}"; done
