- Implementar repartir experiencia/buscapelea como opciones de menú.
- Implementar animación de subir de nivel no usada.
- Arreglar formas/evos +3 en Pokédex.
- Indicar que: * No es posible el uso de la mochila en batalla.
               * Para capturar, basta con tener Pokéballs, y para seleccionarla, mantener pulsado B a la vez que R.
- Crear ataques como Tornado, Vendaval...
- L/R icons en storage.
- Crear huevos personalizados en pokédex.
- Intentar crear animaciones de entrenadores.
- Insertar gráfico de tabla de tipos + características de tipos como opción.
- Añadir características especiales a cada tipo.
- Balance:  *480 - 40
            *500 - 45
            *520 - 50
            *540 - 55
            *560 - 60
            *580 - 65
            *600 - 70
            *620 - 75
            *640 - 80
- Testear Generador.
- Destruir icono Pokémon al darle a huir.
- Implementar la opción de rendirse contra entrenadores.
- Crear bomba ácida.
- Crear bg basado en moxie boosted.
- Darle puño furia a Mankey al nivel 31.
- Hacer glaciación un surf con probabilidad de helar.
- Crear ataque Agua helada (Escaldar pero que congele). Milotic, Lapras, Dewgong.
- Falta balancear Parálisis, Dormido, Confuso, Enamorado, Envenenado (y gravemente envenenado), Retroceso.
- Testear Parásito, Nueve Colas, Humedad relativa, Globo.
- Testear Mimetismo, Percusionista.
- Lucky Punch objeto característico de Hitmonchan (hacer que lo lleve equipado).
- Testear Impenetrable.
- Indicar que Breaking Swipe tiene boost de Dinocola.
- Indicar que Poison Sting, Smart Strike tienen boost de Cornamenta.
- Campo magnético
- Indicar que Rey del mar es una copia de Costar + Oportunista.
- Indicar y comprobar que Ditto ya no está en el juego, pero que la mayoría de Pokémon que antes no podían criar, ahora sí lo hacen: Los Pokémon legendarios son género neutro y se les ha añadido grupos huevo acordes, para criar solo hay que juntar 2 Pokémon sin género del mismo grupo huevo. 
- Last Respects como una versión de paliza fantasma.
- Darle bunker a Tentacruel.
- Cambiar animación de Presente.
- Crear ataque Abducción (animación otra vez).
- Crear habilidad Instinto de supervivencia, sube at. y at. esp y vel. si salud debajo de 50% (relicanth)
- Habilidad Instito maternal: Recibe todos los ataques en dobles (señuelo), kangaskhan, nidoquen.
- Mirar lo que hace la expansión para mostrar tipos dinámicos en combate (Weather ball, día de pago).
- Testear Mago.
- Arreglar animación al subir de nivel (incorporar la no usada como indicador de evo).
- Cambiar animación de Chupasangre usando como referencia Colmillo Veneno.
- Crear Barrera eléctrica (baneful búnker pero paraliza): Dárselo a Electivire.
- Check move_target_all_battlers de lightning rod vs storm drain.
- Hueso quemado (objeto raro en Cubone que lo hace evolucionar a Marowak Alolan).
- Usar viejas partículas: ANIM_TAG_ASCUAS
- Crear habilidad exclusiva de Beedrill (Empalador o algo así).
- Arreglar tiendas.
- Arreglar icono de guardado que cambia con el día.
- Limpiar IsContest

-Lista de moves hechos:
*Bomba huevo.
*Amoladoras.
*Carga jabato.
*Colmena.
*Llama azul.
*Canto encantador.
*Niebla aromática.
*Ojitos tiernos.
*Bombardeo.
*Encanto (TM01).
*Día de pago.
*Chupasangre.


*limpiar minijuegos y saveblocks

*paletas: 0-12 tileset primario 0-9 (es necesario?) secundario 10-12 (chequear SWAP_PAL)
*paletas primary: 0/arboles 1/centro_pokemon 2/hierba_y_hierba_alta 3/agua 4/agua_playa

porytiles compile-primary -Wall -o /Users/ivanmartinez/Desktop/Decompilación/pokeemerald/data/tilesets/primary/principal /Users/ivanmartinez/Desktop/Decompilación/pokeemerald/desarrollo/graficos /Users/ivanmartinez/Desktop/Decompilación/pokeemerald/include/constants/metatile_behaviors.h

*Cada roedor (Furret, Linoone, Diggersby, Raticate, Bidoof) tiene un stat más dominante (PS-Raticate, At-Diggersby, Df-Bidoof, Df. Esp-Furret, Vel-Linoone)
*Porygon Elect-Normal??
*Recordatorio de que el primer color de la paleta del Pokémon no puede ser negro (se bugea el almacenamiento).
*Recordatorio de deserializar las pokeballs.
*Recordatorio de revisar learnsets (encanto, especialmente).
*Recordatorio de limpiar species_info (traducir, solo lo necesario y usar constantes).
*Habilidad exclusiva de Floatzel: flotador. En lluvia, no toca suelo. Además, x2 vel en lluvia.
*Arreglar .pal de Charmander (y de charmeleon?) No de Charizard.
*Añadir caso de crianza para Latios/Latias y Nidoran.
*¿Cómo criar a Tauros?
*Decouple poké balls de item id
*Jigglypuff evoluciona al aprender Vozarrón.
*Cloyster/Slowking/Slowbro aprenden ataques Veneno (+Ataque custom tipo Control Mental?)

paletas: (\d+) (\d+) (\d+) \d+ --> $1 $2 $3