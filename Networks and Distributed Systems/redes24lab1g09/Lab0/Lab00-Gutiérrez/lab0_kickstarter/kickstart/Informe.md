# Tarea Estrella #

## El Problema ##

El problema radica en los estándares de codificación de caracteres para los nombres de dominios de sitios web los cuales, en sistemas que no admiten Unicode o no se configuran para soportarlo, provocan errores de _encoding_ como la mala representación de un caracter en un formato inadecuado.

## Mecanismos que lo solucionan ##

### IDN ###

Un nombre de dominio internacionalizado o IDN por sus siglas en inglés, es un nombre de dominio de internet que puede contener caracteres no ASCII. Esto incluye emojis modernos, caracteres diferentes al alfabeto ingles, tildes diacíticas, etc. 

### Punycode ###

Punycode es una sintaxis de codificación que utiliza una cadena Unicode la cual puede ser traducida en una cadena de caracteres más limitada compatible con los nombres de red. Es útil, por ejemplo, para permitir que los nombres de dominio internacionales se representen en una forma compatible con ASCII ya que sistemas como DNS solo admiten este tipo de caracteres.

## Fuentes ##

- https://foroalfa.org/articulos/el-misterioso-mundo-del-encoding
- https://es.wikipedia.org/wiki/Nombre_de_dominio_internacionalizado
- https://es.wikipedia.org/wiki/Punycode