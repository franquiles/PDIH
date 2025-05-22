library(tuneR)
library(seewave)
library(audio)


setwd("/Users/franc/Desktop/Cuarto - 2ºCuatri/Perifericos/PDIH/p5")

#Ej1
nombre <- readWave("nombreFrancisco.wav")
apellido <- readWave("apellidoQuiles.wav")

#Ej2
plot(extractWave(nombre, from = 1, to = length(nombre@left)))
plot(extractWave(apellido, from = 1, to = length(apellido@left)))

#Ej3
str(nombre)
str(apellido)

listen(nombre)
listen(apellido)

#Ej4
sonido_unido <- pastew(apellido, nombre, output = "Wave")
#Ej5
plot(extractWave(sonido_unido, from = 1, to = length(sonido_unido@left)))
listen(sonido_unido)

#Ej6
writeWave(sonido_unido, "basico.wav")


#Ej7
filtrado <- bwfilter(sonido_unido, f = sonido_unido@samp.rate,
                     from = 10000, to = 20000,
                     bandpass = FALSE, output = "Wave")

writeWave(filtrado, "filtrado.wav")
listen(filtrado)

plot(extractWave(filtrado, from = 1, to = length(filtrado@left)))


# Ej8
basico <- readWave("basico.wav")
eco <- echo(basico, 
            f = basico@samp.rate, 
            amp = c(0.8, 0.4, 0.2),      
            delay = c(1, 2, 3),          
            output = "Wave")

writeWave(eco, "eco.wav")

alreves <- revw(eco, output = "Wave")

writeWave(alreves, "alreves.wav")

plot(extractWave(eco, from = 1, to = length(eco@left)))

plot(extractWave(alreves, from = 1, to = length(alreves@left)))


listen(eco)
listen(alreves)

