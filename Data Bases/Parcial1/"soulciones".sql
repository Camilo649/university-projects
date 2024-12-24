-- 1. Listar las 7 propiedades con la mayor cantidad de reviews en el año 2024.

SELECT p.*, count(r.id) AS totalReviews FROM properties AS p
JOIN reviews AS r ON r.property_id = p.id
WHERE year(r.created_at) = 2024
GROUP BY p.id
ORDER BY totalReviews DESC
LIMIT 7;

-- 2. Obtener los ingresos por reservas de cada propiedad. Esta consulta debe calcular los ingresos totales generados por cada propiedad. Ayuda: hay un campo `price_per_night` en la tabla de `properties` donde los ingresos totales se computan  sumando la cantidad de noches reservadas para cada reserva multiplicado por el precio por noche.

SELECT p.*, b.*, sum((datediff(b.check_out, b.check_in) + 1) * p.price_per_night) AS totalIncome FROM properties AS p
JOIN bookings AS b ON b.property_id = p.id
GROUP BY b.id;

-- PREGUNTAR SI HAY QUE DEVOLVER TANTO LA PROPERTIE COM LA BOOKING

-- 3. Listar los principales usuarios según los pagos totales. Esta consulta calcula los pagos totales realizados por cada usuario y enumera los principales 10 usuarios según la suma de sus pagos.

SELECT u.*, sum(p.amount) AS totalPayment FROM users AS u
JOIN payments AS p ON p.user_id = u.id
GROUP BY u.id
ORDER BY totalPayment DESC
LIMIT 10;

-- 4. Crear un trigger notify_host_after_booking que notifica al anfitrión sobre una nueva reserva. Es decir, cuando se realiza una reserva, notifique al anfitrión de la propiedad mediante un mensaje.

DELIMITER $$

CREATE TRIGGER notify_host_after_booking AFTER INSERT
ON bookings FOR EACH ROW
BEGIN 
	INSERT INTO messages (sender_id, receiver_id, property_id, context, sent_at) -- No calculo el ID porque es auto incremental en la tabla message
	VALUES (NEW.user_id, properties.owner_id, properties.id, 'Se ha realizado una nueva reserva', now());
END$$ 

DELIMITER ;

-- 5. Crear un procedimiento add_new_booking  para agregar una nueva reserva. Este procedimiento agrega una nueva reserva para un usuario, según el ID de la propiedad, el ID del usuario y las fechas de entrada y salida. Verifica si la propiedad está disponible durante las fechas especificadas antes de insertar la reserva.

DELIMITER $$

CREATE PROCEDURE add_new_booking (IN PropertyID int, IN UserID int, IN Date_In date, IN Date_Out date)
BEGIN 
	DECLARE TotalPrice int;
       SET TotalPrice = (
		SELECT (datediff(Date_Out, Date_In) + 1)*price_per_night FROM properties
			WHERE id = PropertyID
		)	
    INSERT INTO bookings (property_id, user_id, check_in, check_out, total_price, status, created_at) -- No calculo el ID porque es auto incremental en la tabla bookings
	VALUES (PropertyID, UserID, Date_In, Date_Out, TotalPrice,'pending' ,now())
END$$

DELIMITER ;

-- 6. Crear el rol `admin` y asignarle permisos de creación sobre la tabla `properties` y permiso de actualización sobre la columna `status`  de la tabla `property_availability` .

CREATE ROLE admin;

GRANT INSERT ON airbnb_like_db.properties
TO admin;

GRANT UPDATE(status) ON property_availability
TO admin;


-- 7.

/* Respuesta
 * 
 * Por que la propiedad de Durabilidad de ACID hace referencia a que persistan los cambios
 * realizados por una transaccion exitosa. Si la transaccion se completo con éxtio, no habría
 * problema con actualizar datos en una tabla por más que esta ya halla sido creada, pues los
 * cambios serían persistentes lo cual no contradice la propiedad.
 * */


















