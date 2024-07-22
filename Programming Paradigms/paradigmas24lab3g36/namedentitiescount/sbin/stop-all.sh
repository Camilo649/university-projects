#!/bin/bash

# Función para limpiar los workers existentes
cleanup_workers() {
  # Obtener los PID de los workers de Spark
  WORKER_PIDS=$(jps | grep Worker | awk '{print $1}')
  
  if [ -z "$WORKER_PIDS" ]; then
    echo "No Spark workers to clean up."
  else
    # Detener cada worker usando su PID
    for pid in $WORKER_PIDS; do
      kill "$pid"
    done

    # Esperar a que los workers se detengan completamente
    sleep 5

    # Verificar que los workers se hayan detenido
    WORKERS_RUNNING=$(jps | grep Worker | wc -l)
    if [ "$WORKERS_RUNNING" -ne 0 ]; then
      echo "Failed to stop existing Spark workers. Exiting..."
      print_help
    fi
    echo "Spark workers deleted."
  fi
}

# Función para limpiar el master
cleanup_master() {
  # Obtener el PID del master
  MASTER_PID=$(jps | grep Master | awk '{print $1}')
  
  if [ -z "$MASTER_PID" ]; then
    echo "No Spark master to clean up."
  else
    # Detener cada worker usando su PID

    kill $MASTER_PID

    # Esperar a que el master se detenga completamente
    sleep 5

    # Verificar que el master se haya detenido
    MASTER_RUNNING=$(jps | grep Master | wc -l)
    if [ "$MASTER_RUNNING" -ne 0 ]; then
      echo "Failed to stop existing Spark master. Exiting..."
      print_help
    fi
    echo "Spark master deleted."
  fi
}

# Mostrar mensaje de ayuda
print_help() {
  SPARK_OPTS=(
  --master local[1]
  )

  JAR_PATH="$APP_HOME/namedentitiescount/target/NamedEntitiesCount-1.0-SNAPSHOT.jar"

  APP_OPTS=(
    -h
  )

  "${SPARK_HOME}/bin/spark-submit" \
  "${SPARK_OPTS[@]}" \
  "$JAR_PATH" \
  "${APP_OPTS[@]}" 2>/dev/null
  exit 1
}

cleanup_workers
cleanup_master