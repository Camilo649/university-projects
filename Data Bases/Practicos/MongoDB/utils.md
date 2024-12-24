# RESULTADO DE UN LOOKUP

Dada la colección `orders`:

```js
{ "_id": 1, "order_number": "A001", "customer_id": 123 }
{ "_id": 2, "order_number": "A002", "customer_id": 456 }
```

Y la colección `customers:`

```js
{ "_id": 123, "name": "John Doe", "city": "New York" }
{ "_id": 456, "name": "Jane Smith", "city": "Los Angeles" }
```


La consulta:

```js
db.orders.aggregate([
  {
    $lookup: {
      from: "customers",
      localField: "customer_id",
      foreignField: "_id",
      as: "customer_info"
    }
  }
]);
```

Devolverá:

```js
[
  {
    "_id": 1,
    "order_number": "A001",
    "customer_id": 123,
    "customer_info": [
      {
        "_id": 123,
        "name": "John Doe",
        "city": "New York"
      }
    ]
  },
  {
    "_id": 2,
    "order_number": "A002",
    "customer_id": 456,
    "customer_info": [
      {
        "_id": 456,
        "name": "Jane Smith",
        "city": "Los Angeles"
      }
    ]
  }
]
```
# FECHAS

Cuando te encuentres con algo de la pinta: `ISODate("2014-02-01T00:00:00.000Z")`

Recordá que el formato de la fecha se compone como: 

``` ruby
  YYYY-MM-DDTHH:mm:ss.SSSZ
```

- **YYYY:** Año (1980 en este caso).
- **MM:** Mes, expresado como un número entre 01 (enero) y 12 (diciembre).
- **DD:** Día del mes, expresado como un número entre 01 y 31.
- **T:** Indica el inicio de la parte de tiempo (hora).
- **HH:mm:ss.SSS:** Hora, minutos, segundos y milisegundos (en formato de 24 horas).
- **Z:** Indica que la hora está en el tiempo universal coordinado (UTC).

# EJEMPLO PARA ELIMINAR UPDATES

``` js
db.restaurants.updateMany(
    {
        cuisine: { $in: ["Bakery", "Coffee"] },
        discounts: { $exists: true }
    },
    {
        $unset: { discounts: "" }
    }
);
```
