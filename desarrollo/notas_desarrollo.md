- Implementar repartir experiencia/buscapelea como opciones de menú.
- Implementar animación de subir de nivel no usada.
- Arreglar formas/evos +3 en Pokédex.
- Indicar que: * No es posible el uso de la mochila en batalla.
               * Para capturar, basta con tener Pokéballs, y para seleccionarla, mantener pulsado B a la vez que R.

        if (sIconTypeId[0] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
            sIconTypeId[0] = 0xFF;
        }
        if (sIconTypeId[1] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
            sIconTypeId[1] = 0xFF;
        }
        if (sIconTypeId[2] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
            sIconTypeId[2] = 0xFF;
        }
        if (sIconTypeId[3] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
            sIconTypeId[3] = 0xFF;
        }
